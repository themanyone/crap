HEADERS=$(wildcard *.hh)
%.h : %.hh
	crap "$<" > "$@"
all: $(HEADERS:.hh=.h)
.PHONY: clean
clean:
	#$(RM) -f $(HEADERS:.hh=.h)
