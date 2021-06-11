CC	:= gcc
CFLAGS	:= -Wall -O3
LDFLAGS :=
LDLIBS	:=

.PHONY: all clean

all: main.x kopiuj.x procesy.x lider.x

#ZAD 1
main.x: main.o procinfo.o
main.o: main.c procinfo.h
procinfo.o: procinfo.c procinfo.h
#ZAD 2
kopiuj.x: kopiuj.o
kopiuj.o: kopiuj.c
#ZAD 3
procesy.x: procesy.o procinfo.o
procesy.o: procesy.c procinfo.h
#ZAD 4
lider.x: lider.o procinfo.o
lider.o: lider.c procinfo.h

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o