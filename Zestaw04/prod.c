#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

void prod(int p) {
    srand(time(0));

    int f = open("magazyn.txt", O_RDONLY);
    if(f==-1) {
        perror("(prod) open error");
        exit(1);
    }

    int size = 100;
    char *buf = (char*)malloc(size);
    if(!buf) {
        perror("(prod) buf error");
        exit(1);
    }

    int r = -1;
    int w = -1;

    useconds_t t = 10000 + rand()%100000;
    int ile_bajtow = 0;

    do {
        ile_bajtow = 1+rand()%size;

        r = read(f, buf, ile_bajtow);
        if(r==-1) {
            perror("(prod) read error");
            exit(1);
        }

        printf("\n(Producent) Pobieram dane z pliku: %d bajtow\n", r);
        write(1,buf,r);

        w = write(p, buf, r);
        if(w==-1) {
            perror("(prod) write error");
            exit(1);
        }
        printf("\n(Producent) Zapisuje dane do potoku: %d bajtow\n", w);
        write(1,buf,w);

        usleep(10*t);
        t = 10000 + rand()%10000;

    } while(r==ile_bajtow);

    char end[] = "//end//";
    buf = end;
    w = write(p, buf, sizeof(buf));
    if(w==-1) {
        perror("(prod) write error");
        exit(1);
    }

    printf("\n(Producent) Koncze prace z plikiem.\n\n");

    close(f);
    close(p);
}