CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
CC = clang $(CFLAGS)
OBJECTS = hatterspeak.o bf.o bv.o speck.o ll.o hs.o hash.o parser.o
EXECBIN = hatterspeak

all: hatterspeak

$(EXECBIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECBIN)
hatterspeak.o: hatterspeak.c bf.c bv.c speck.c hs.c hash.c parser.c
	$(CC) -c hatterspeak.c
bf.o: bf.c bf.h
	$(CC) -c bf.c
bv.o: bv.c bv.h
	$(CC) -c bv.c
speck.o: speck.c speck.h
	$(CC) -c speck.c
ll.o: ll.c ll.h
	$(CC) -c ll.c
	
hs.o: hs.c hs.h
	$(CC) -c hs.c
hash.o: hash.c hash.h
	$(CC) -c hash.c
	
parser.o: parser.c parser.h
	$(CC) -c parser.c
.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(EXECBIN) infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make
	
