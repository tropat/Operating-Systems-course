#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int main(int argc, const char* argv[]) {

    const char* name = "/semaphore";
    semid s = NULL;

    char option;

    while(1) {
        printf("i/r/p/v/q : ");
        scanf("%s", &option);

        switch(option){
            case 'i': 
                s=semCreate(name,10);
                semInfo(s);
                break;
            case 'r':
                semRemove(name);
                break;
            case 'p':
                semP(s);
                semInfo(s);
                break;
            case 'v':
                semV(s);
                semInfo(s);
                break;
            case 'q':
                semInfo(s);
                break;
            case 'o':
                s=semOpen(name);
                break;
            default:
                printf("Blad argumentu!\n");
                exit(1);
                break;
        }
    }
}