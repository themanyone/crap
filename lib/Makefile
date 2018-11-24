LIBS=$(wildcard *.crap)
CFLAGS=-I../include
%.c : %.crap
	crap "$<" > "$@"
%.o : %.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"
all: $(LIBS:.crap=.c) $(LIBS:.crap=.o)
clean:
	$(RM) -f $(LIBS:.crap=.o)
