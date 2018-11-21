NAME=crap
PREFIX=/usr/local
INCLUDEDIR=$(PREFIX)/include
INSTALLDIR=$(PREFIX)/bin
DOCDIR=    $(PREFIX)/share/$(NAME)
LIBDIR=    $(PREFIX)/lib64
BUILD_TARGETS=$(NAME).o
BUILD_HEADERS=join.h
BUILD_LIBS=reg.o
INCLUDES=-I.
LDFLAGS=-L.
CFLAGS=-g -Wall -pipe -O2 -std=c99
MING=/usr/bin/i686-pc-mingw32-gcc
CC=gcc

%.c : %.crap
	./crap "$<" > "$@"
%.h : %.hh
	./crap "$<" > "$@"
%.o : %.c %.h
	$(CC) $(CFLAGS) -c "$<" -o "$@" $(INCLUDES)
% : %.o $(BUILD_LIBS)
	$(CC) "$<" $(BUILD_LIBS) -o "$@$(EXT)" $(LDFLAGS)
#~ "make foo.so" shared library
%.so : CFLAGS+=-fPIC
%.so : LDFLAGS=-shared
%.so : %.o
	$(CC) $(LDFLAGS) $< -Wl,-soname,"lib$@.1" -o "libs/lib$@.1.0.1"
	ln -sf "lib$@.1.0.1" "libs/lib$@.1"
	ln -sf "lib$@.1.0.1" "libs/lib$@"

#~ defauilt rule builds target[s] [libs]
all: $(BUILD_HEADERS) $(BUILD_TARGETS:.o=) $(BUILD_TARGETS) $(BUILD_LIBS)

shared: $(BUILD_HEADERS) $(BUILD_LIBS:.o=.so) $(BUILD_TARGETS)
	$(CC) $(BUILD_TARGETS) -o "$(NAME)$(EXT)" -Llibs -lreg

#~ do not delete .c files after build
.PRECIOUS: %.c

#~ other targets
win: CC=$(MINGW)
win: EXT=.exe
win: all

debug: CFLAGS+=-g -pedantic -O0
debug: all

%.asm : %.o
	objdump -Sx $< > $@

s:
	SciTE Makefile *.h *.anch&

clean:
	rm -f $(BUILD_TARGETS) $(BUILD_TARGETS:.o=) $(BUILD_TARGETS:.o=.exe) $(BUILD_LIBS) *.asm libs/*

pub:
	-strip $(BUILD_TARGETS:.o=)
	-i686-pc-mingw32-strip $(BUILD_TARGETS:.o=.exe)

install:
	install -D README.md "$(DOCDIR)/README.md"
	install -D LICENSE   "$(DOCDIR)/LICENSE"
	install -D "$(NAME)" "$(INSTALLDIR)/$(NAME)"
	-install -D "libs/lib$(BUILD_LIBS:.o=.so)" "$(LIBDIR)"
	install -D "asprintf.h" "$(INCLUDEDIR)"

uninstall:
	$(RM) "$(DOCDIR)/README.md"
	$(RM) "$(DOCDIR)/LICENSE"
	$(RM) "$(INSTALLDIR)/$(NAME)"
	$(RM) "$(LIBDIR)/$(BUILD_LIBS:.o=.so)"
	$(RM) "$(LIBDIR)/$(BUILD_LIBS:.o=.so).1"
	$(RM) "$(LIBDIR)/$(BUILD_LIBS:.o=.so).1.0.1"
	$(RM) "$(INCLUDEDIR)/asprintf.h"
