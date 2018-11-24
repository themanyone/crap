NAME=crap
DESTDIR=/usr/local
PREFIX=$(DESTDIR)
INCLUDEDIR=$(PREFIX)/include
INSTALLDIR=$(PREFIX)/bin
DOCDIR=    $(PREFIX)/share/$(NAME)
LIBDIR=    $(PREFIX)/lib64
BUILD_TARGETS=$(NAME).o
BUILD_LIBS=lib/reg.o
SUBDIRS=include lib
LDFLAGS=-Llib
CFLAGS=-Iinclude -g -Wall -pipe -O2 -std=c99
MING=/usr/bin/i686-pc-mingw32-gcc
CC=gcc

%.c : %.crap
	crap "$<" > "$@"
%.o : %.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"
% : %.o
	$(CC) "$<"  $(BUILD_LIBS) -o "$@$(EXT)" $(LDFLAGS)

.PHONY: all $(SUBDIRS)

#~ defauilt rule builds target[s] lib[s]
all: $(SUBDIRS) $(BUILD_TARGETS:.o=) $(BUILD_TARGETS) $(BUILD_LIBS)
$(SUBDIRS):
	$(MAKE) $(OPTIONS) -C $@

shared: $(BUILD_LIBS:.o=.so) $(BUILD_TARGETS)
	$(CC) $(BUILD_TARGETS) -o "$(NAME)$(EXT)" -Llib -lreg

#~ do not delete after build
.PRECIOUS: %.c %.h

#~ other targets
win: CC=$(MINGW)
win: EXT=.exe
win: all

tcc: CC=$(TCC)
tcc: all

debug: CFLAGS+=-g -pedantic -O0
debug: all

%.asm : %.o
	objdump -Sx $< > $@

s:
	SciTE Makefile *.crap&

clean: OPTIONS=clean
clean: $(SUBDIRS)
	$(RM) $(BUILD_TARGETS) $(BUILD_TARGETS:.o=) $(BUILD_TARGETS:.o=.exe) $(BUILD_LIBS) *.asm

pub:
	-strip $(BUILD_TARGETS:.o=)
	-i686-pc-mingw32-strip $(BUILD_TARGETS:.o=.exe)

install: OPTIONS=install
install:
	install -D README.md "$(DOCDIR)/README.md"
	install -D LICENSE   "$(DOCDIR)/LICENSE"
	install -D "$(NAME)" "$(INSTALLDIR)/$(NAME)"

uninstall:
	$(RM) "$(DOCDIR)/README.md"
	$(RM) "$(DOCDIR)/LICENSE"
	$(RM) "$(INSTALLDIR)/$(NAME)"
