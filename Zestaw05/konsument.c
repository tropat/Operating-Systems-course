#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
     int f = open(argv[2], O_WRONLY|O_CREAT, 0644);
    if(f==-1) {
        perror("open error");
        _exit(1);
    }
    int p = open(argv[1], O_RDONLY);
    if(p==-1) {
        perror("open error");
        _exit(1);
    }

    srand(time(0));

    int size = 100;
    char *buf = (char*)malloc(size);
    if(!buf) {
        perror("(kons) buf error");
        _exit(1);
    }

    useconds_t t = 10000 + rand()%100000;
    int ile_bajtow = 0;

    int r = -1;
    int w = -1;

    int pom = 0;

    do {
        ile_bajtow = sizeof("//end//")+rand()%(size-7);

        r = read(p, buf, ile_bajtow);
        if(r==-1) {
            perror("(kons) read error");
            _exit(1);
        }

        if(strstr(buf, "//end//")!=NULL) {
                pom=sizeof("//end//");
            }

        printf("\n(Konsument) Pobieram dane z potoku: %d bajtow\n", r);
        write(1,buf,r);

        w = write(f, buf, r-pom);
        if(w==-1) {
            perror("(kons) write error");
            _exit(1);
        }
        printf("\n(Konsument) Zapisuje dane do pliku: %d bajtow\n", w);
        write(1,buf,w);

        usleep(t);
        t = 10000 + rand()%100000;

    } while(!pom);

    printf("\n(Konsument) Koncze prace z plikiem.\n\n");

    close(f);
    close(p);
    free(buf);

}