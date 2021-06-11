CC	:= gcc
CFLAGS	:= -Wall -pedantic
LDFLAGS	:=
LDLIBS	:=

.PHONY: all clean

all: prodkons.x

prodkons.x: prodkons.o prod.o kons.o
prodkons.o: prodkons.c prod.h kons.h
prod.o: prod.c prod.h
kons.o: kons.c kons.h

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.x schowek.txt