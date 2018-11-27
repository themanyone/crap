LIBS=$(wildcard *.crap)
CFLAGS=-I../include
%.c : %.crap
	crap "$<" > "$@"
%.o : %.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"
%.so : CFLAGS+=-fPIC
%.so : LDFLAGS=-shared
%.so : %.o
	$(CC) $(LDFLAGS) $< -Wl,-soname,"lib$@.1" -o "lib$@.1.0.1"
	ln -sf "lib$@.1.0.1" "lib$@.1"
	ln -sf "lib$@.1.0.1" "lib$@"
all: $(LIBS:.crap=.c) $(LIBS:.crap=.o)
clean:
	$(RM) $(LIBS:.crap=.o)
	$(RM) $(wildcard lib*.so*)
shared: $(LIBS:.crap=.so)
install: all
	$(foreach lib, $(wildcard lib*.so*), \
	cp -av $(lib) $(LIBDIR);)
uninstall: all
	$(foreach lib, $(wildcard lib*.so*), \
	$(RM) $(LIBDIR)/$(lib);)
