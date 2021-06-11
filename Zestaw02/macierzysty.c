#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "procinfo.h"

int main(int argc, const char* argv[]) {
    procinfo(argv[0]);
    int i,id;
    for(i=0;i<3;i++) {
        switch(id=fork()) { // TWORZENIE PROCESU POTOMNEGO I WYPISYWANIE IDENTYFIKATOROW
            case -1: 
                perror("fork error"); 
                exit(1);
            case 0: 
                execv("./potomny.x",(char * const*)argv);
                perror("exect error");
                exit(1);
            default: break;
        }
    }
    while(wait(NULL)>0||errno!=ECHILD); // CZEKA NA WSZYSTKIE PROCESY POTOMNE
}