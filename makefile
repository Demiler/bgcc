all: build

build/help.o: help.c
	gcc -c -o $@ $<

build/defaults.o: utils/defaults.c
	gcc -c -o $@ $<

build/logs.o: utils/logs.c
	gcc -c -o $@ $<

build/params.o: utils/params.c
	gcc -c -o $@ $<

build/argp.o: utils/argp.c
	gcc -c -o $@ $<

build:\
	build/help.o\
	build/defaults.o\
	build/logs.o\
	build/params.o\
	build/argp.o\
	main.c
	gcc -g -o bgcc $^
