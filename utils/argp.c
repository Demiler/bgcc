#include <stdio.h>
static char **argvptr = 0;
static int argcc = 0;

static int param = 0;
char *ungetp(void) {
    if (param == 0) return 0;
    return argvptr[param--];
}

char *getpar(void) {
    if (param >= argcc) return NULL;
    char *ret = argvptr[param++];
    return ret;
    //return argvptr[param++];
}

static int lostParam = 0;
char *getlost(void) {
    return argvptr[lostParam];
}

void init(int argc, char **argv) {
    argvptr = argv;
    argcc = argc;
    param = 1;
}

char parse(void) {
    static int lastArgc = 1;
    static char *lastCh = 0;

    while (lastArgc < argcc) {
        if (param < lastArgc + 1) {
            lostParam = param;
            param = lastArgc + 1;
            if (lostParam < argcc && argvptr[lostParam][0] != '-')
                return 0;
        }

        if (argvptr[lastArgc][0] == '-') {
            if (lastCh) lastCh++;
            else lastCh = argvptr[lastArgc] + 1;

            if (*lastCh) return *lastCh;

            lastCh = 0;
        }
        lastArgc++;
    }
    return -1;
}
