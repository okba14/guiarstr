CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

all: libguiarstr.a

libguiarstr.a: src/guiarstr.c include/guiarstr.h
	$(CC) $(CFLAGS) -c src/guiarstr.c -o guiarstr.o
	ar rcs libguiarstr.a guiarstr.o

test: libguiarstr.a tests/main.c
	$(CC) $(CFLAGS) tests/main.c libguiarstr.a -o test

example: libguiarstr.a examples/usage.c
	$(CC) $(CFLAGS) examples/usage.c libguiarstr.a -o example

clean:
	rm -f *.o *.a test example
