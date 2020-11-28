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

struct {
  const char *dir;
  char genName[256];
  struct gccArgs gccArgs;
} defaults = {
  "build",
  "",
  {
    "-o",
    "-lm",
    "-m32",
    "-ldl",
    "-g",
    {
      "-m32",
      "-O2",
      "-std=gnu11",
      "-Wall",
      "-Werror",
      "-Wno-pointer-sign",
      "-Wformat",
      "-Wformat-overflow",
      "-Wformat-security",
      "-Wnull-dereference",
      "-Wignored-qualifiers",
      "-Wshift-negative-value",
      "-Wswitch-default",
      "-Wduplicated-branches",
      "-Wduplicated-branches",
      "-Wfloat-equal",
      "-Wshadow",
      "-Wpointer-arith",
      "-Wpointer-compare",
      "-Wtype-limits",
      "-Wwrite-strings",
      "-Wdangling-else",
      "-Wempty-body",
      "-Wlogical-op",
      "-Wstrict-prototypes",
      "-Wold-style-declaration",
      "-Wold-style-definition",
      "-Wmissing-parameter-type",
      "-Wmissing-field-initializers",
      "-Wnested-externs",
      "-Wvla-larger-than=4096",
      "-lm"
    },
  },
};
#endif
