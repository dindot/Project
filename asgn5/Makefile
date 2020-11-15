CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = sorting.o bubble.o shell.o quick.o binary.o counters.o
EXECBIN = sorting

all: sorting
	
$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)
sorting.o: sorting.c bubble.c shell.c quick.c binary.c counters.c
	$(CC) -c sorting.c
	
bubble.o: bubble.c bubble.h counters.h
	$(CC) -c bubble.c
	
shell.o: shell.c shell.h counters.h
	$(CC) -c shell.c
	
quick.o: quick.c quick.h counters.h
	$(CC) -c quick.c
	
binary.o: binary.c binary.h counters.h
	$(CC) -c binary.c
	
counters.o: counters.c counters.h
	$(CC) -c counters.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
