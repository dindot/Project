CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = tower.o stack.o
EXECBIN = tower

all: tower
	
$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)
tower.o: tower.c stack.h
	$(CC) -c tower.c
	
stack.o: stack.c stack.h
	$(CC) -c stack.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make

