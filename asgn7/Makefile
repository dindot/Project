CFLAGS = -Wall -Wextra -Werror -Wpedantic -lm -ggdb
CC = clang $(CFLAGS)

all: tester encode

tester: tester.c trie.c word.c io.c bv.c
	$(CC) -o tester tester.c trie.c word.c io.c bv.c
encode: encode.c trie.c word.c io.c bv.c
	$(CC) -o encode encode.c trie.c word.c io.c bv.c
trie.o: trie.c trie.h
	$(CC) -c trie.c
word.o: word.c word.h
	$(CC) -c word.c
io.o: io.c io.h
	$(CC) -c io.c
bv.o: bv.c bv.h
	$(CC) -c bv.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
