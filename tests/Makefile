LIBS=$(wildcard *.craplib)
CRAP=$(wildcard *.crap)
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
all:
	$(foreach exe, $(wildcard *.crap), \
	./$(exe) || exit;)
clean:
	$(RM) $(CRAP:.crap=.c)
shared: $(LIBS:.crap=.so)
.PHONY: install uninstall
