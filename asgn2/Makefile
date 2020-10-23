CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: math
	
math: math.o
	$(CC) -lm -o math math.o
math.o: math.o
	$(CC) $(CFLAGS) -lm -c math.c
clean:
	rm -rf -lm math math.o infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
