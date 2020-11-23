#ifndef LOGS_H
#define LOGS_H
extern void error(const char *msg, int code, ...);
extern void warning(const char *msg, ...);
extern void msg(const char *msg, ...);
#endif
