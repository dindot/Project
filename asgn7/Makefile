CFLAGS = -Wall -Wextra -Werror -Wpedantic -lm -ggdb
CC = clang $(CFLAGS)

all: encode decode

encode: encode.c trie.c word.c io.c
	$(CC) -o encode encode.c trie.c word.c io.c
decode: decode.c trie.c word.c io.c
	$(CC) -o decode decode.c trie.c word.c io.c
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
	
