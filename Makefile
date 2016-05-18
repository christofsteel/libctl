CC = g++

all: main

state.o: state.cc state.h
	${CC} state.cc -std=c++11 -c -o state.o

main: main.cc ctl.h state.o
	${CC} main.cc state.o -std=c++11 -o main

.PHONY: clean
clean:
	rm main *.o
