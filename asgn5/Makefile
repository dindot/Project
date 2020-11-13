CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = sorting.o bubble.o shell.o quick.o binary.o
EXECBIN = sorting

all: sorting
	
$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)
sorting.o: sorting.c bubble.c shell.c quick.c binary.c
	$(CC) -c sorting.c
	
bubble.o: bubble.c bubble.h
	$(CC) -c bubble.c
	
shell.o: shell.c shell.h
	$(CC) -c shell.c
	
quick.o: quick.c quick.h
	$(CC) -c quick.c
	
binary.o: binary.c binary.h
	$(CC) -c binary.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
