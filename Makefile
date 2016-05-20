CC = clang++

all: main

state.o: state.cc state.h
	${CC} state.cc -std=c++11 -c -o state.o

ctl.o: ctl.cc ctl.h
	${CC} ctl.cc -std=c++11 -c -o ctl.o

main: main.cc ctl.o state.o
	${CC} main.cc ctl.o state.o -std=c++11 -o main

.PHONY: clean
clean:
	rm main *.o
