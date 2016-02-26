GCC=gcc
CFLAGS=-Wall

all: the2038problem

the2038Problem:
	$(GCC) $(CFLAGS) the2038problem.c -o the2038problem

clean:
	rm -f the2038problem
