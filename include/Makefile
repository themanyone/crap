HEADERS=$(wildcard *.hh)
#defaults
.SUFFIXES:
.SUFFIXES: .c .o
SHELL = /bin/sh
INSTALL=install
INSTALL_PROGRAM=$(INSTALL)

%.h : %.hh
	crap "$<" > "$@"
all: $(HEADERS:.hh=.h)
.PHONY: clean install debug debugshared
shared: all
debug: all
debugshared: all
install: all
	-$(INSTALL_PROGRAM) -D $(HEADERS:.hh=.h) -t $(INCDIR)
uninstall: all
	$(foreach header,$(HEADERS:.hh=.h), \
	$(RM) $(INCDIR)/$(header);)
