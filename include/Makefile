HEADERS=$(wildcard *.hh)
%.h : %.hh
	crap "$<" > "$@"
all: $(HEADERS:.hh=.h)
.PHONY: clean shared
clean:
	#$(RM) $(HEADERS:.hh=.h)
install: all
	-install -D $(HEADERS:.hh=.h) -t $(INCLUDEDIR)
uninstall: all
	$(foreach header,$(HEADERS:.hh=.h), \
	$(RM) $(INCLUDEDIR)/$(header);)
