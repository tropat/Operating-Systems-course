#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "sem.h"
#include "shmem.h"

#define SIZE 4
#define CZAS rand()%20000

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
    int file = open("schowek.txt", O_WRONLY|O_CREAT, 0644);
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

    sleep(1);

    do {
        printf("(K)(Sem2)\t");
        semP(sem2);
            printf("\t(K)Beg: %d\tEnd: %d\t\tSize: %d\n", ptr->beg, ptr->end, ptr->size);
                if(ptr->beg==SIZE) {
                    ptr->beg=0;
                }
                if(ptr->end<0 && ptr->size==1) {s=(ptr->end*-1)-1;}
                if(s!=0) {
                    sprintf(bufor, "%d", ptr->buf[ptr->beg]);
                    printf("\t(K)Czytam dane z bufora:\n\t\t%d\n", ptr->buf[ptr->beg]);
                    r = write(file, bufor, s);
                    if(r==-1) {
                        perror("write error");
                        exit(1);
                    }
                    printf("\t(K)Zapisuje do schowek.txt:\n\t\t%s\n", bufor);
                } 
                (ptr->beg)++;
                (ptr->size)--;

                if(ptr->size==SIZE-1) {
        printf("(K)(Sem1)\t");
        semV(sem1);
                }

                printf("\t(K)Beg: %d\tEnd: %d\t\tSize: %d\n", ptr->beg, ptr->end, ptr->size);

        printf("(K)(Sem2)\t");        
        semV(sem2);
                if(ptr->size==0) {
        printf("(K)(Sem2)\t");
        semP(sem2);
                }
                t=CZAS;
                printf("(K)Waiting %d\n", t);
                usleep(t);  
    } while(!(ptr->end<0 && ptr->size==0));

    semClose(sem1);
    semClose(sem2);
    shmClose(ptr, des, 1024);
    free(bufor);
}