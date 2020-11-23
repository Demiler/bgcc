all: build

build/logs.o: utils/logs.c
	gcc -o build/logs.o utils/logs.c -c

build/params.o: utils/params.c
	gcc -o build/params.o utils/params.c -c

build/argp.o: utils/argp.c
	gcc -o build/argp.o utils/argp.c -c

build/main.o: main.c
	gcc -o build/main.o main.c -c

build:\
	build/main.o\
	build/argp.o\
	build/params.o\
	build/logs.o
	gcc -g -o bgcc\
		build/main.o\
		build/argp.o\
		build/params.o\
		build/logs.o

