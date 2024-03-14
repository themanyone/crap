LIBS=$(wildcard *.crap)
BFLAGS=-I../include -g -Wall
LDFLAGS=-L./
#defaults
.SUFFIXES:
.SUFFIXES: .c .o
SHELL = /bin/sh
INSTALL=install
INSTALL_PROGRAM=$(INSTALL)
%.c : %.crap
	crap "$<" > "$@"
%.o : %.c
	$(CC) $(BFLAGS) $(CFLAGS) -c "$<" -o "$@"
%.so : CFLAGS+=-fPIC
%.so : LDFLAGS+=-shared
%.so : %.o
	$(CC) $(BFLAGS) $(CFLAGS) $(LDFLAGS) $< -Wl,-soname,"lib$@.1" -o "lib$@.1.0.1"
	ln -sf "lib$@.1.0.1" "lib$@.1"
	ln -sf "lib$@.1.0.1" "lib$@"
all: $(LIBS:.crap=.c) $(LIBS:.crap=.o)
clean:
	$(RM) $(LIBS:.crap=.o) $(wildcard lib*.so*) *~
shared: $(LIBS:.crap=.so)
debug: BFLAGS+=-Wall -pedantic -O0
debug: CFLAGS+=-g
debug: all
debugshared: BFLAGS+=-Wall -pedantic -O0
debugshared: CFLAGS+=-g
debugshared: shared
.PHONY: debug all shared debugshared
install: all
	$(foreach lib, $(wildcard lib*.so*), \
	$(INSTALL_PROGRAM) -D $(lib) $(LIBDIR)/$(lib);)
uninstall: all
	$(foreach lib, $(wildcard lib*.so*), \
	$(RM) $(LIBDIR)/$(lib);)
