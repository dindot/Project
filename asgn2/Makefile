CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -lm

all: math
	
math: math.o
	$(CC) -o math math.o -lm
math.o: math.o
	$(CC) $(CFLAGS) -c math.c
clean:
	rm -rf math math.o infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
