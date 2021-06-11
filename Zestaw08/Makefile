CC	:= gcc
CFLAGS	:= -Wall
LDFLAGS	:= -L.
LDLIBS	:= -lrt -lmsg
AR	:= ar
ARFLAGS	:= rv

.PHONY: all clean tar

all: libmsg.so libmsg.a serwer.x klient.x

libmsg.a: msg.o
libmsg.so: msg.o
msg.o: msg.c
klient.x: klient.o
klient.o: klient.c
serwer.x: serwer.o
serwer.o: serwer.c

lib%.a: %.o
	$(AR) $(ARFLAGS) $@ $?

lib%.so: %.o
	$(CC) -shared -o $@ $<

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -Wl,-R ./

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o *.so *.a

tar: clean
	cd ..; tar -cvzf trojan08.tar.gz Zestaw08