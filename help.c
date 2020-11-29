#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static const char helpmsg[] =
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
static const char testmsg[] =
"pipes data into your program, reads it output and compares with\n"
"given answer. Use flags from origin help message to change tester\n"
"behavior. Test file has following structure\n"
"   1|--TEST\n"
"   2|test data\n"
"   3|--ANSWER\n"
"   4|answer for test\n"
"   5|--\n"
"\n"
"Here '--TEST' is the keyword that tells tester the following\n"
"data is test. Everything in line after this keyword is ignored.\n"
"'--ANSWER' or just '--ANS' is the keyword that tells tester the following\n"
"data is the correct program output. As for --TEST everything following\n"
"in line is ignored. The last keyword is '--' simply means that test is\n"
"over. And tester can compare the results and give some statistics.\n"
"\n"
"Here is all keywords for tester you can use:\n"
"    --TEST\n"
"        means the begging of test\n"
"\n"
"    --ANS[WER]\n"
"        gives data for comparison\n"
"\n"
"    --\n"
"        end of test\n"
"\n"
"    --ARGS: arguments\n"
"        starts your program with given arguments\n"
"\n"
"    --TIME: number following by modificator (s,m,ms)\n"
"        marks test as failed if program runs more than given time\n"
"\n"
"    --RET: return code\n"
"        marks test as failed if program return different return code\n"
"\n"
"For keywords with ':' data in line after is not ignored and used for next\n"
"test that is going to be performed. Better to declare them before '--TEST'\n"
"keyword or right after it or else they could be ignored. Keywords are not\n"
"being include into test or answer. Be careful though keyword are treated\n"
"as keyword only if line is started with '--'. For example this '^--TEST$'\n"
"will be treated as '--TEST' keyword but '^ --TEST$' will not (here ^ and $\n"
"symbols means begging of the line and it's end).\n"
;

void help(const char *cmd) {
    if (cmd == NULL) {
        printf(helpmsg);
        exit(0);
    }

    if (!strcasecmp(cmd, "t"))
        printf(testmsg);
    exit(0);
}
