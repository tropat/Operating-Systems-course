#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

void end(void);

int main(int argc, const char* argv[]) {
    if(argc!=3) {
        printf("Niepoprawna liczba argumentow!\n");
        _exit(1);
    }

    const char* potok = "./potok";
    const char* odczyt = "magazyn.txt";
    const char* zapis = "schowek.txt";

    if(mkfifo(potok,0644)) {
        perror("mkfifo error");
        _exit(1);
    }
    int id=fork();
    if(!id) {
        if(execl(argv[1], argv[0], potok, odczyt, NULL)) {
            perror("execl error");
            exit(1);
        }
    } else if(id==-1) {
        perror("fork error");
        exit(1);
    }
    id=fork();
    if(!id) {
        if(execl(argv[2], argv[0], potok, zapis, NULL)) {
            perror("execl error");
            exit(1);
        }
    } else if(id==-1) {
        perror("fork error");
        exit(1);
    }
    int i=0;
    for(i=0;i<2;++i) {
        wait(NULL);
    }

    if(atexit(end)) {
        printf("Nie mozna ustawic funkcji wyjscia.\n");
        exit(1);
    }

}

void end(void) {
    if(unlink("./potok")) {
        perror("unlink error");
        _exit(1);
    }
}