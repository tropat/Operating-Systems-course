#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "sem.h"

int main(int argc, const char* argv[]) {
    if(argc!=2) {
        printf("Blad liczby argumentow!\n");
        exit(1);
    }

    srand(time(0));
    int t=0;

    semid s = semOpen("/sem");

    int f = -1;

    int size=2;
    char *bufor = (char*)malloc(size);
    if(!bufor) {
        perror("bufor error");
        exit(1);
    }

    int rw = -1; 
    int buf;

    int sval;

    int i=0;

    for(i=0;i<atoi(argv[1]);++i) {
        t = 10000 + rand()%1000000;
        usleep(t);
        sem_getvalue(s,&sval);
        printf("Przed sekcja krytyczna: %d %d %d\n", getpid(), sval, i+1);

    semP(s);
        sem_getvalue(s,&sval);
        printf("W trakcie sekcji krytycznej: %d %d %d\n", getpid(), sval, i+1);

        f = open("numer.txt", O_RDONLY);
        if(f==-1) {
            perror("open error");
            exit(1);
        }

        printf("\tOtwieram plik do odczytu\n");

        rw = read(f, bufor, 2);
        if(rw==-1) {
            perror("read error");
            exit(1);
        }

        printf("\tOdczytuje wartosc z pliku: ");
        buf = atoi(bufor);
        printf("%d\n", buf);

        close(f);
        printf("\tZamykam plik do odczytu\n");

        buf++;
        printf("\tInkrementuje wartosc z pliku\n");

        t = 10000 + rand()%1000000;
        usleep(t);

        f = open("numer.txt", O_WRONLY);
        if(f==-1) {
            perror("open error");
            exit(1);
        }

        printf("\tOtwieram plik do zapisu\n");

        sprintf(bufor, "%d", buf);

        rw = write(f, bufor, rw);
        if(rw==-1) {
            perror("read error");
            exit(1);
        }

        printf("\tZapisuje do pliku\n");

        close(f);
        printf("\tZamykam plik do zapisu\n");

    semV(s);
        sem_getvalue(s,&sval);
        printf("Po sekcji krytycznej: %d %d %d\n", getpid(), sval, i+1);
    }
    free(bufor);
    semClose(s);
}