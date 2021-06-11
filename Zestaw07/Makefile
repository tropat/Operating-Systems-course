CC	:= gcc
CFLAGS	:= -O -fPIC
LDFLAGS	:= -L. -pthread
LDLIBS	:= -lrt -lshmem -lsem
AR	:= ar
ARFLAGS	:= rv

.PHONY: all clean tar

all: libsem.a libshmem.so shmuse1.x shmuse2.x glowny.x konsument.x producent.x

sem.o: sem.c sem.h
shmem.o: shmem.c shmem.h
shmuse1.x: shmuse.o
shmuse2.x: shmuse.o
shmuse.o: shmuse.c shmem.h
glowny.x: glowny.o
glowny.o: glowny.c shmem.h sem.h
producent.x: producent.o
producent.o: producent.c shmem.h sem.h
konsument.x: konsument.o
konsument.o: konsument.c shmem.h sem.h

lib%.a: %.o
	$(AR) $(ARFLAGS) $@ $?

lib%.so: %.o
	$(CC) -shared -o $@ $<

%1.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -Wl,-R ./

%2.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.x: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.x *.o *.so *.a schowek.txt

tar: clean
	cd ..; tar -cvzf trojan07.tar.gz Zestaw07