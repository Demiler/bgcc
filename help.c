#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

const char helpmsg[] =
"Simple wrap around gcc compiler for C files.\n"
"Compiles your C files and can run them, pipe data into them,\n"
"test them, watch them changing and auto apply some flags.\n"
"\n"
"Usage: bgcc \e[4mfile\e[0m [-rpgwsjmahe] [-d \e[4mdir\e[0m] [-o \e[4mfile\e[0m] [-i \e[4mfile\e[0m]\n"
"  -r\tRun if compile\n"
"  -i\tPipe data from file\n"
"  -t\tRun test from file\n"
"   -I\tHide test input\n"
"   -D\tDont trim test data\n"
"   -A\tDont trim test answer\n"
"   -T\tShow test file structure\n"
"   -F\tShow only failed tests\n"
"  -S n\tCompile with sanitizer level n\n"
"  -L\tPrint sanitizers levels\n"
"  -W\tWatch file\n"
"  -d\tOutput dir (build by default)\n"
"  -o\tSet output file\n"
"  -p\tOutput files in current dir\n"
"  -g\tCompile with debug\n"
"  -w\tIgnore script warnings\n"
"  -s\tNo additional script messages\n"
"  -j\tUse ejudge flags\n"
"  -m\tUse math lib\n"
"  -a\tUse 32 arch\n"
"  -l\tUse linked libraries\n"
"  -h\tDisplay this message\n"
"  -e\tScript error codes\n"
"  --\tPass args to your program\n";

void help(const char *cmd) {
    if (cmd == NULL)
        printf(helpmsg);
    exit(0);
}
