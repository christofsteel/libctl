CC = clang++
CFLAGS = -O2 -march=native -mtune=native  -Werror

all: main

state.o: state.cc state.h
	${CC} ${CFLAGS} state.cc -std=c++11 -c -o state.o

ctl.o: ctl.cc ctl.h
	${CC} ${CFLAGS} ctl.cc -std=c++11 -c -o ctl.o

main: main.cc ctl.o state.o
	${CC} ${CFLAGS} main.cc ctl.o state.o -std=c++11 -o main

.PHONY: clean
clean:
	rm main *.o
