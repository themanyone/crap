HEADERS=$(wildcard *.hh)
%.h : %.hh
	crap "$<" > "$@"
all: $(HEADERS:.hh=.h)
clean:
	$(RM) -f $(HEADERS:.hh=.h)
