CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = sequence.o bv.o sieve.o
EXECBIN = sequence

all: sequence

$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN) -lm
sequence.o: sequence.c bv.c sieve.c
	$(CC) -c sequence.c
	
bv.o: bv.c bv.h
	$(CC) -c bv.c
	
sieve.o: sieve.c sieve.h
	$(CC) -c sieve.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
		
