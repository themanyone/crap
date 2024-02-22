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
.PHONY: clean install debug
clean:
	$(RM) $(HEADERS:.hh=.h) *~
shared: all
debug: all
install: all
	-$(INSTALL_PROGRAM) -D $(HEADERS:.hh=.h) -t $(INCDIR)
uninstall: all
	$(foreach header,$(HEADERS:.hh=.h), \
	$(RM) $(INCDIR)/$(header);)
