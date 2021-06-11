CC	:= gcc
CFLAGS	:= -Wall -O3
LDFLAGS	:=
LDLIBS	:=

.PHONY: all clean

all: obsluga.x wysylaj.x grupa.x

obsluga.x: obsluga.o procinfo.o
obsluga.o: obsluga.c procinfo.h
procinfo.o: procinfo.c procinfo.h

wysylaj.x: wysylaj.o
wysylaj.o: wysylaj.c

grupa.x: grupa.o
grupa.o: grupa.c

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.x