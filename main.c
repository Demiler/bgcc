#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include "utils/params.h"
#include "utils/logs.h"
#include "utils/exitCodes.h"
#include "utils/defaults.h"
#include "utils/signames.h"
#include "utils/global.h"
#include "help.h"

const char *getFilenameExt(const char *fileName) {
    const char *dot = strrchr(fileName, '.');
    if(!dot || dot == fileName) return NULL;
    return dot + 1;
}

const char **fillCompilerArgs(const char *outName) {

    //+3 -- minimal amount of args: input_file -o output_file
    size_t totalArgs = params.compiler.argc + COMP_PARAMS + 3;
    if (params.compiler.ejudge)
        totalArgs += EJUDGE_FLAGS_NUM;

    const char *compilerName = "gcc";
    //+2 for NULL and compiler name
    const char **gccArgs = malloc((totalArgs + 2) * sizeof(char*));
    if (gccArgs == NULL)
        error("not enough memory", ERR_NE_MEMORY);

    gccArgs[totalArgs + 1] = NULL;
    const char **head = gccArgs;
    *(head++) = compilerName;
    *(head++) = params.fileName;
    *(head++) = defaults.gccArgs.o;
    *(head++) = outName;
    if (params.compiler.ejudge) {
        params.compiler.math = false;
        params.compiler.m32 = false;
        for (int i = 0; i < EJUDGE_FLAGS_NUM; i++)
            *(head++) = defaults.gccArgs.ejudge[i];
    }

    for (int i = 0; i < params.compiler.argc; i++)
        *(head++) = params.compiler.args[i];

    if (params.compiler.linkedLibs)
        *(head++) = defaults.gccArgs.ldl;
    if (params.compiler.debug)
        *(head++) = defaults.gccArgs.g;
    if (params.compiler.m32)
        *(head++) = defaults.gccArgs.m32;
    if (params.compiler.math)
        *(head++) = defaults.gccArgs.lm;
    return gccArgs;
}

void initProg(int argc, char *argv[]) {
    fillArgs(argc, argv);

    if (!params.fileName)
        error("no input file", ERR_NO_INPUT_FILE);
    if (access(params.fileName, F_OK))
        error("file %s not found", ERR_NO_SUCH_FILE, params.fileName);
    if (params.pipeFile && access(params.pipeFile, F_OK))
        error("file %s not found", ERR_NO_SUCH_FILE, params.pipeFile);
    if (params.testFile && access(params.testFile, F_OK))
        error("file %s not found", ERR_NO_SUCH_FILE, params.testFile);

    if (!params.dir)
        params.dir = defaults.dir;

    if (!strcmp(params.dir, defaults.dir)) {
        if (access(params.dir, F_OK) && mkdir(params.dir, 0666) == -1) {
            int err = errno;
            error("couldn't create 'build' dir. Errno: %d", ERR_MKDIR, err);
        }
    }
    else if (access(params.dir, F_OK))
        error("dir %s not found", ERR_DIR, params.dir);

    if (!params.outName) {
        int len = strlen(params.fileName);
        if (len > PATH_MAX)
            error("file name is too long", ERR_LONG_FILENAME);
        const char *dot = getFilenameExt(params.fileName);
        if (!dot)
            error("no file extension!", ERR_NO_FILE_EXT);
        int baseNameLen = dot - params.fileName - 1;
        strncpy(global.genName, params.fileName, baseNameLen);
        params.outName = global.genName;
    }

}

int needRecompile(const char *name, const char *outName) {
    if (access(outName, F_OK))
        return true;
    struct stat origin, compiled;
    if (stat(name, &origin) == -1) {
        int err = errno;
        error("stat failed for file %s. Errno: %d", ERR_STAT, outName, err);
    }
    if (stat(outName, &compiled) == -1) {
        int err = errno;
        error("stat failed for file %s. Errno: %d", ERR_STAT, name, err);
    }
    return origin.st_mtime > compiled.st_mtime;
}

void compile(const char *outName) {
    bool recompile = needRecompile(params.fileName, outName);
    if (recompile)
        msg("File being recompiled");
    else {
        msg("File isn't being recompiled");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        int err = errno;
        error("cannot create proccess. Errno: %d", ERR_FORK, err);
    }

    if (!pid) {
        const char **gccArgs = fillCompilerArgs(outName);
        execvp("gcc", (char*const*)gccArgs);
        free(gccArgs);
        int err = errno;
        error("cannot exec compiler. Errno: %d", ERR_EXEC, err);
    }
    int status;
    waitpid(pid, &status, 0);

    if (!WIFEXITED(status) || WEXITSTATUS(status))
        error("compilation failed", ERR_COMILATION_FAILED);
}

void checkProgStatus(int status) {
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status))
            warning("program returned non-zero (%d) value", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        if (sig > 31)
            warning("program got signal %d - unknown signal", sig);
        else
            warning("program got signal %d - %s", sig, signames[sig - 1]);
    }
}

void justRun(const char *program) {
    pid_t pid = fork();
    if (pid == -1) {
        int err = errno;
        error("cannot create proccess. Errno: %d", ERR_FORK, err);
    }

    if (!pid) {
        params.args[0] = (char*)program;
        execv(program, params.args);
        int err = errno;
        error("cannot exec program. Errno: %d", ERR_EXEC, err);
    }

    int status;
    waitpid(pid, &status, 0);
    checkProgStatus(status);
}

void runPipe(const char *program) {
    pid_t pid = fork();
    if (pid == -1) {
        int err = errno;
        error("cannot create proccess. Errno: %d", ERR_FORK, err);
    }

    if (!pid) {
        int pipeFile = open(params.pipeFile, O_RDONLY);
        if (pipeFile == -1) {
            int err = errno;
            error("open failed for file %s. Errno: %d", ERR_EXEC, params.pipeFile, err);
        }

        if (dup2(pipeFile, STDIN_FILENO) == -1) {
            int err = errno;
            error("dup2 failed. Errno: %d", ERR_EXEC, err);
        }
        execl(program, program, NULL);
        int err = errno;
        error("cannot exec program. Errno: %d", ERR_EXEC, err);
    }

    int status;
    waitpid(pid, &status, 0);
    checkProgStatus(status);
}

void runTest(const char *program) {
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        help(NULL);
    initProg(argc, argv);

    char fullOutName[PATH_MAX];
    snprintf(fullOutName, PATH_MAX, "%s/%s", params.dir, params.outName);

    compile(fullOutName);

    if (params.run) {
        if (params.testFile)
            global.runFunction = runTest;
        else if (params.pipeFile)
            global.runFunction = runPipe;
        else
            global.runFunction = justRun;
        global.runFunction(fullOutName);
    }

    return 0;
}
