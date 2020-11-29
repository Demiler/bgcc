#ifndef GLOBAL_H
#define GLOBAL_H
#include <limits.h>
struct {
  char fullOutName[PATH_MAX];
  char genName[PATH_MAX];
  void (*runFunction)(const char*);
} global;
#endif
