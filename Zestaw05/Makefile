CC	:= gcc
CFLAGS	:= -Wall -pedantic
LDLIBS	:=
LDFLAGS	:=

.PHONY: all clean

all: fifo.x producent.x konsument.x

fifo.x: fifo.o
producent.x: producent.o
konsument.x: konsument.o
fifo.o: fifo.c
producent.o: producent.c
konsument.o: konsument.c

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o schowek.txt