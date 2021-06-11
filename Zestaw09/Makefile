CC	:= gcc
CFLAGS	:=
LDFLAGS	:=
LDLIBS	:= -lpthread

.PHONY: all clean tar

all: wykluczanie.x

wykluczanie.x: wykluczanie.o
wykluczanie.o: wykluczanie.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o

tar: clean
	cd ..; tar -cvzf trojan09.tar.gz Zestaw09