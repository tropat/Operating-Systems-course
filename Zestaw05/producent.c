#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    int f = open(argv[2], O_RDONLY);
    if(f==-1) {
        perror("open-1 error");
        _exit(1);
    }
    int p = open(argv[1], O_WRONLY);
    if(p==-1) {
        perror("open-2 error");
        _exit(1);
    }

    srand(time(0));

    int size = 100;
    char *buf = (char*)malloc(size);
    if(!buf) {
        perror("(prod) buf error");
        _exit(1);
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
            _exit(1);
        }

        printf("\n(Producent) Pobieram dane z pliku: %d bajtow\n", r);
        write(1,buf,r);
        w = write(p, buf, r);
        if(w==-1) {
            perror("(prod) write error");
            _exit(1);
        }
        printf("\n(Producent) Zapisuje dane do potoku: %d bajtow\n", w);
        write(1,buf,w);

        usleep(10*t);
        t = 9000 + rand()%10000;

    } while(r==ile_bajtow);

    char end[] = "//end//";
    buf = end;
    w = write(p, buf, sizeof(buf));
    if(w==-1) {
        perror("(prod) write error");
        _exit(1);
    }

    printf("\n(Producent) Koncze prace z plikiem.\n\n");

    close(f);
    close(p);

}