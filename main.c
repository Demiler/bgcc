#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "utils/params.h"
#include "utils/logs.h"
#include "utils/exitCodes.h"
#include "utils/defaults.h"

const char *getFilenameExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}

int main(int argc, char *argv[]) {
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
        if (len > 256)
            error("file name is too long", ERR_LONG_FILENAME);
        char dot = getFilenameExt(params.fileName);
        if (!dot)
            error("no file extension!", ERR_NO_FILE_EXT);
        int baseNameLen = dot - params.fileName - 1;
        strncpy(defaults.genName, params.fileName, baseNameLen); 
        params.outName = defaults.genName;
    }

    pid_t pid = fork();
    if (pid == -1) {
        int err = errno;
        error("cannot create proccess. Errno: %d", ERR_FORK, err);
    }

    if (!pid) {
        char fullName[PATH_MAX];
        strncpy(fullName, PATH_MAX, "%s/%s", params.dir, params.outName);
        char *gccArgs[256];
        gccArgs[0] = fullName;
        gccArgs[1] = defaults.gccArgs[0];
    }


    return 0;
}
