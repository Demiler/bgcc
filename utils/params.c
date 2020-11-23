#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "argp.h"
#include "params.h"
#include "logs.h"

params.fileName = NULL;
params.pipeFile = NULL;
params.testFile = NULL;

params.helpCmd = NULL;
params.dir = NULL;
params.outName = NULL;

params.watch = false;
params.run = false;
params.sanitizer = 0;

params.compile.debug = false;
params.compile.m32 = false;
params.compile.math = false;
params.compile.ejudge = false;

params.tester.hideInput = false;
params.tester.dontTrimData = false;
params.tester.dontTrimAnsw = false;
params.tester.onlyFailed = false;

params.noMsgs = false;
params.noWarnings = false;
params.noErrors = false;

params.color = false;

static void help() {
    printf(
      );
    exit(0);
}

params.fileName = NULL;

void fillArgs(int argc, char *argv[]) {
    init(argc, argv);

    char flag;
    while ((flag = parse()) != -1) {
        char *par;

        switch (flag) {
            case 0:
                if (params.fileName)
                    warning("input file overwriten!");
                params.fileName = getlost();
                break;
            case 'r':
                params.run = true;
                break;

            case 'i':
                if (params.pipeFile)
                    warning("pipe file overwriten!");
                params.pipeFile = getpar();
                if (!params.pipeFile)
                    error("no pipe file provided!", ERR_MISSING_ARGUMENT);
                break;

            case 't':
                if (params.testFile)
                    warning("pipe file overwriten!");
                params.pipeFile = getpar();
                if (!params.pipeFile)
                    error("no test file provided!", ERR_MISSING_ARGUMENT);
                break;

            case 'S':
                par = getpar();
                if (!par)
                    error("no sanitizer level provided!", ERR_MISSING_ARGUMENT);
                params.sanitizer = strtol(par, NULL, 10);
                break;

            case 'W':
                params.watch = true;
                break;

            case 'd':
                if (params.testFile)
                    warning("pipe file overwriten!");

            default:
                warning("unknown flag %c\n", flag);
        }
    }
}
