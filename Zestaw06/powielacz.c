#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include "sem.h"

void end();
void my_sighandler();

int main(int argc, const char* argv[]) {
    if(argc!=4) {
        printf("Blad liczby argumentow!\n");
        _exit(1);
    }
    atexit(end);
    if(signal(SIGINT,my_sighandler) == SIG_ERR) {
        perror("signal error (p)");
        exit(1);
    }

    int sval;

    semid s = semCreate("/sem",1);
    sem_getvalue(s,&sval);
    semClose(s);

    int f = open("numer.txt", O_WRONLY|O_CREAT,0644);
    if(f==-1) {
        perror("open error");
        exit(1);
    }

    printf("Tworze plik tekstowy\n");

    int rw = write(f, "0", sizeof("0"));
    if(rw==-1) {
        perror("write error");
        exit(1);
    }

    printf("Zapisuje 0 do pliku tekstowego\n");

    close(f);

    printf("Adress: %p Value: %d\n\n", (void *)s, sval);
    
    int i=0;

    for(i=0;i<atoi(argv[2]);++i) {
        switch(fork()) {
            case -1:
                perror("fork error");
                exit(1);
                break;
            case 0:
                if(execl(argv[1], argv[0], argv[3], NULL)==-1) {
                    perror("execl error");
                    exit(1);
                }
                break;
            default:
                break;
        }
    }

    for(i=0;i<atoi(argv[2]);++i) {
        wait(NULL);
    }

    printf("\n");

    int size=2;
    char *bufor = (char*)malloc(size);
    if(!bufor) {
        perror("bufor error");
        exit(1);
    }

    f = open("numer.txt", O_RDONLY);
    if(f==-1) {
        perror("open error");
        exit(1);
    }

    printf("Otwieram plik do odczytu\n");

    rw = read(f, bufor, 2);
    if(rw==-1) {
        perror("read error");
        exit(1);
    }

    if(atoi(bufor)==atoi(argv[2])*atoi(argv[3])) {
        printf("Poprawne dane w pliku\n");
    } else {
        printf("Niepoprawne dane w pliku\n");
    }

    close(f);
    printf("Zamykam plik do odczytu\n");
    free(bufor);

}

void end() {
    semRemove("/sem");
}

void my_sighandler() {
    semRemove("/sem");
    _exit(1);
}