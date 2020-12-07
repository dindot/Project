CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = tester.o trie.o word.o io.o
EXECBIN = tester

all: tester

$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -lm -ggdb -o $(EXECBIN)
tester.o: tester.c trie.c word.c io.c
	$(CC) -c tester.c
trie.o: trie.c trie.h
	$(CC) -c trie.c
word.o: word.c word.h
	$(CC) -c word.c
io.o: io.c io.h
	$(CC) -c io.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
