#ifndef DEFAULTS_H
#define DEFAULTS_H
#define EJUDGE_FLAGS_NUM 32

struct gccArgs {
  const char *o;
  const char *lm;
  const char *m32;
  const char *ldl;
  const char *g;
  const char *ejudge[EJUDGE_FLAGS_NUM];
};

struct defaults {
  const char *dir;
  const char *curDir;
  struct gccArgs gccArgs;
};

extern struct defaults defaults;
#endif
