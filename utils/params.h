#ifndef PARAMS_H
#define PARAMS_H
#include <stdbool.h>

#define MAX_ARGS 50

struct compilerOps {
  bool linkedLibs;
  bool debug;
  bool m32;
  bool math;
  bool ejudge;
  char *args[MAX_ARGS];
};

struct testerOps {
  bool hideInput;
  bool dontTrimData;
  bool dontTrimAnsw;
  bool onlyFailed;
};

struct {
  const char *fileName;
  const char *pipeFile;
  const char *testFile;

  const char *dir;
  char *outName;

  bool watch;
  bool run;
  int sanitizer;

  struct compilerOps compiler;
  struct testerOps tester;

  bool noMsgs;
  bool noWarnings;

  char *args[MAX_ARGS];
  bool color;
} params;

extern void fillArgs(int argc, char *argv[]);
#endif
