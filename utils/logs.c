#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "params.h"

void error(const char *msg, int code, ...) {
    va_list args;
    va_start(args, code);
    if (params.color)
        fprintf(stderr, "\e[31mError: \e[0m");
    else
        fprintf(stderr, "Error: ");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(code);
}

void warning(const char *msg, ...) {
    va_list args;
    va_start(args, msg);
    if (params.color)
        fprintf(stderr, "\e[33mWarning: \e[0m");
    else
        fprintf(stderr, "Warning: ");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void msg(const char *msg, ...) {
    if (params.noMsgs) return;
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\n");
    va_end(args);
}

void dmsg(int level, const char *msg, ...) {
    if (params.noMsgs) return; //TODO: add verbose level

    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\n");
    va_end(args);
}
