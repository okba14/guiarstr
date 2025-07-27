CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
PREFIX ?= /usr/local
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib
PKGCONFIGDIR = $(LIBDIR)/pkgconfig

# Targets
all: libguiarstr.a guiarstr_tests example

libguiarstr.a: src/guiarstr.c include/guiarstr.h
	$(CC) $(CFLAGS) -c src/guiarstr.c -o guiarstr.o
	ar rcs libguiarstr.a guiarstr.o

guiarstr_tests: libguiarstr.a tests/main.c
	$(CC) $(CFLAGS) tests/main.c libguiarstr.a -o guiarstr_tests

example: libguiarstr.a examples/usage.c
	$(CC) $(CFLAGS) examples/usage.c libguiarstr.a -o example

# Run tests
test: guiarstr_tests
	./guiarstr_tests

# Install/uninstall
install: libguiarstr.a guiarstr.pc
	install -d $(DESTDIR)$(INCLUDEDIR)
	install -m 644 include/guiarstr.h $(DESTDIR)$(INCLUDEDIR)/

	install -d $(DESTDIR)$(LIBDIR)
	install -m 644 libguiarstr.a $(DESTDIR)$(LIBDIR)/

	install -d $(DESTDIR)$(PKGCONFIGDIR)
	install -m 644 guiarstr.pc $(DESTDIR)$(PKGCONFIGDIR)/

uninstall:
	rm -f $(DESTDIR)$(INCLUDEDIR)/guiarstr.h
	rm -f $(DESTDIR)$(LIBDIR)/libguiarstr.a
	rm -f $(DESTDIR)$(PKGCONFIGDIR)/guiarstr.pc

# Cleanup
clean:
	rm -f *.o *.a guiarstr_tests example
