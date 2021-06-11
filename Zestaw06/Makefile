CC	:= gcc
CFLAGS	:= -Wall -pedantic
LDFLAGS	:= -pthread -L.
LDLIBS	:= -lrt -lsem
AR	:= ar
ARFLAGS	:= rv

.PHONY: all clean tar

all: libsem.a semuse.x prog.x powielacz.x

sem.o: sem.c sem.h
semuse.x: semuse.o
semuse.o: semuse.c sem.h
prog.x: prog.o
prog.o: prog.c sem.h
powielacz.x: powielacz.o
powielacz.o: powielacz.c sem.h

lib%.a: %.o
	$(AR) $(ARFLAGS) $@ $?

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	$(RM) *.o *.x *.a numer.txt

tar: clean
	cd ..; tar -cvzf trojan06.tar.gz Zestaw06