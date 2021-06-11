#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "sem.h"
#include "shmem.h"

#define SIZE 4
#define CZAS rand()%100000

struct cykliczny {
    int size;
    int beg;
    int end;
    int buf[SIZE];
};

int main(int argc, const char* argv) {
    srand(time(0));
    int t=0;
    
    int des = shmOpen("/shm");
    struct cykliczny* ptr = shmMap(des, 1024);
    semid sem1 = semOpen("/sem1");
    semid sem2 = semOpen("/sem2");
    int file = open("magazyn.txt", O_RDONLY);
    if(file==-1) {
        perror("open file error");
        exit(1);
    }

    int r=-1;
    int s = 4;

    char* bufor = (char*)malloc(s);
    if(!bufor) {
        perror("bufor error");
        exit(1);
    }

    printf("(P)(Sem2)\t");
    semP(sem2);
        ptr->beg=0;
        ptr->end=0;
        ptr->size=0;
        printf("\tUstawiam bufor\n");

    do {
        printf("(P)(Sem1)\t");
        semP(sem1);
            printf("\t(P)Beg: %d\tEnd: %d\t\tSize: %d\n", ptr->beg, ptr->end, ptr->size);
                if(ptr->end==SIZE) {
                    ptr->end=0;
                }
                r = read(file, bufor, s);
                if(r==-1) {
                    perror("read error");
                    exit(1);
                } else if(r==0) {
                    ptr->end=-1;
                } else {
                    printf("\t(P)Czytam dane z magazyn.txt:\n\t\t%s\n", bufor);
                    (ptr->buf[ptr->end]) = atoi(bufor);
                    printf("\t(P)Zapisuje do bufora:\n\t\t%d\n", ptr->buf[ptr->end]);
                }

                (ptr->end)++;
                (ptr->size)++;

                if(ptr->size==1) {
        printf("(P)(Sem2)\t");
        semV(sem2);
                }

                if(r<s) { 
                    ptr->end=(r*-1)-1;
                    printf("\t(P)Koniec pliku magazyn.txt\n");
                }
                printf("\t(P)Beg: %d\tEnd: %d\t\tSize: %d\n", ptr->beg, ptr->end, ptr->size);
        printf("(P)(Sem1)\t");
        semV(sem1);
                if(ptr->size==SIZE) {
        printf("(P)(Sem1)\t");
        semP(sem1);
                }
                t=CZAS;
                printf("(P)Waiting %d\n", t);
                usleep(t);
    } while(r==s);

    semClose(sem1);
    semClose(sem2);
    shmClose(ptr, des, 1024);
    free(bufor);
}