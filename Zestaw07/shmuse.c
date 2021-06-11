#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "shmem.h"

int main(int argc, const char* argv[]) {
    if((argc!=2 && argv[1][0]!='c' && argv[1][0]!='w') || (argc!=3 && argv[1][0]=='c') || (argc!=3 && argv[1][0]=='w')) {
        printf("Niepoprawna liczba argumentow\n");
        exit(1);
    }

    char* ptr = NULL;
    int fd = -1;
    int r=-1, w=-1;
    int s=100;
    int file = -1;
    char *bufor = (char*)malloc(s);
    if(!bufor) {
        perror("bufor error");
        exit(1);
    }

    const char* name = "/dzielona";
    switch(argv[1][0]) {
        case 'c': 
            fd = shmCreate(name, atoi(argv[2]));
            close(fd);
            break;
        case 'd': 
            shmRm(name);
            break;
        case 'r': 
            fd = shmOpen(name);
            ptr = shmMap(fd, s);
            printf("%s\n", (const char*)ptr);
            shmClose(ptr, fd, s);
            break;
        case 'w': 
            fd = shmOpen(name);
            file = open(argv[2], O_RDONLY);
            if(file==-1) {
                perror("open error");
                exit(1);
            }
                r = read(file, bufor, s);
                if(r==-1) {
                    perror("read error");
                    exit(1);
                }
                close(file);
                printf("%s\n", bufor);
                ptr = shmMap(fd, r);
                strcpy(ptr, bufor);
            shmClose(ptr, fd, s);
            break;
        case 'i': 
            fd = shmOpen(name);
            shmInfo(fd);
            close(fd);
            break;
         default: 
            printf("Prawidlowe uzycie: ./semuse.x <c/d/r/w/i> ['c' - dodac size, 'w' - input.txt]\n");
            break;
    }
    free(bufor);
}