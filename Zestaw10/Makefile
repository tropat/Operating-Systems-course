CC	:= gcc
CFLAGS	:=
LDFLAGS	:=
LDLIBS	:= -lpthread

.PHONY: all clean tar

all: piekarnia.x

piekarnia.x: piekarnia.o
piekarni.o: piekarnia.c

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o

tar: clean
	cd ..; tar -cvzf trojan10.tar.gz Zestaw10