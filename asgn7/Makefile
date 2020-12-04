CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)
OBJECTS = tester.o trie.o word.o
EXECBIN = tester

all: tester

$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -ggdb -o $(EXECBIN)
tester.o: tester.c trie.c word.c
	$(CC) -c tester.c
trie.o: trie.c trie.h
	$(CC) -c trie.c
word.o: word.c word.h
	$(CC) -c word.c
	
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
