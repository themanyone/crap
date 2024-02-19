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
%.so : BFLAGS+=-fPIC
%.so : LDFLAGS+=-shared
%.so : %.o
	$(CC) $(CFLAGS) $(LDFLAGS) $< -Wl,-soname,"lib$@.1" -o "lib$@.1.0.1"
	ln -sf "lib$@.1.0.1" "lib$@.1"
	ln -sf "lib$@.1.0.1" "lib$@"
all: $(LIBS:.crap=.c) $(LIBS:.crap=.o)
clean:
	$(RM) $(LIBS:.crap=.[oc]) $(wildcard lib*.so*)
shared: $(LIBS:.crap=.so)
install: all
	$(foreach lib, $(wildcard lib*.so*), \
	$(INSTALL_PROGRAM) -D $(lib) $(LIBDIR)/$(lib);)
uninstall: all
	$(foreach lib, $(wildcard lib*.so*), \
	$(RM) $(LIBDIR)/$(lib);)
