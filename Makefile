# Target binary
TARGET=crap
# Compiler
CC=gcc
.SUFFIXES:
.SUFFIXES: .c .o
SHELL = /bin/sh
INSTALL=install
INSTALL_PROGRAM=$(INSTALL)
# Directories
INCLUDEDIR=include
LIBSDIR=lib
SUBDIRS=$(INCLUDEDIR) $(LIBSDIR)
# Compiler flags
export BFLAGS=-Iinclude -Wall -pipe -O2 -std=c99
# Linker flags
LDFLAGS=-Llib
DESTDIR=/usr/local
PREFIX=$(DESTDIR)
export INCDIR=$(PREFIX)/include
BINDIR=$(PREFIX)/bin
DOCDIR=$(PREFIX)/share/$(TARGET)
export LIBDIR=$(PREFIX)/lib64

# Source files
SRCS=crap.c $(LIBSDIR)/reg.c
# $(LIBSDIR)/sjoin.c
# Object files
OBJS=$(SRCS:.c=.o)

# Static make target
all: $(SUBDIRS) $(TARGET)

# Shared make target
shared: LDFLAGS+=-lreg -Wl,-rpath=$(LIBSDIR)
shared: BFLAGS+=-fPIC -shared
shared: $(SUBDIRS) crap.o
	$(CC) $(CFLAGS) crap.o $(LDFLAGS) -o crap

ifeq ($(wildcard crap),$(TARGET))
# Craptastic rules
%.c : %.crap
	crap "$<" > "$@"
else
%.c : %.crap
	@echo "Note: 'crap' program not available yet. Using existing '.c' files."
	@touch "$@"
endif

# Compile rules
%.o: %.c
	$(CC) $(BFLAGS) $(CFLAGS) -c $< -o $@

# Link rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Phony targets
.PHONY: debug all shared tests $(SUBDIRS)

# Clean rule
clean: $(SUBDIRS)
	$(RM) $(OBJS) $(TARGET) *~

debug: BFLAGS+=-Wall -pedantic -O0
debug: CFLAGS=-g
debug: include lib all

debugshared: BFLAGS+=-Wall -pedantic -O0
debugshared: CFLAGS=-g
debugshared: include lib shared

tcc: CC=$(TCC)
tcc: all

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

tests:
	$(MAKE) -C $@

install: $(SUBDIRS)
	$(INSTALL_PROGRAM) -D README.md "$(DOCDIR)/README.md"
	$(INSTALL_PROGRAM) -D LICENSE   "$(DOCDIR)/LICENSE"
	$(INSTALL_PROGRAM) -D "$(TARGET)" "$(BINDIR)/$(TARGET)"
	$(INSTALL_PROGRAM) -D crapper "$(BINDIR)/crapper"

uninstall: $(SUBDIRS)

	$(RM) "$(DOCDIR)/README.md"
	$(RM) "$(DOCDIR)/LICENSE"
	$(RM) "$(BINDIR)/$(TARGET)"
	$(RM) "$(BINDIR)/crapper"
