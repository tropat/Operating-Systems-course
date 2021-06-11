CC	:= gcc
CFLAGS	:= -Wall -O3
LDFLAGS	:=
LDLIBS	:=

.PHONY: all clean

all: drzewko1.x drzewko2.x macierzysty.x potomny.x zombi.x orphan.x execute.x

#ZAD 1
drzewko1.x: drzewko1.o procinfo.o
drzewko1.o: drzewko1.c procinfo.h

drzewko2.x: drzewko2.o procinfo.o
drzewko2.o: drzewko2.c procinfo.h

procinfo.o: procinfo.c procinfo.h

#ZAD 2
macierzysty.x: macierzysty.o procinfo.o
macierzysty.o: macierzysty.c procinfo.h

potomny.x: potomny.o procinfo.o
potomny.o: potomny.c procinfo.h

#ZAD 3
zombi.x: zombi.o
zombi.o: zombi.c

orphan.x: orphan.o
orphan.o: orphan.c

execute.x: execute.o
execute.o: execute.c

%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o