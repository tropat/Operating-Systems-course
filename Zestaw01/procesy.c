#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "procinfo.h"

int main(int argc, const char* argv[]) {
    procinfo(argv[0]);
    int i,licznik=0; // LICZNIK POTOMKOW
    for(i=0;i<3;i++) {
        switch(fork()) { // TWORZENIE PROCESU POTOMNEGO I WYPISYWANIE IDENTYFIKATOROW
            case -1: 
                perror("fork error"); 
                exit(1);
            case 0: 
                sleep(1); 
                procinfo(argv[0]); // PROCINFO.H
                licznik=0;
                break;
            default: licznik+=1; break;
        }
    }
    for(i=0;i<licznik;i++) {
        wait(NULL);
    }
    //while(wait(NULL)>0||errno!=ECHILD); // CZEKA NA WSZYSTKIE PROCESY POTOMNE
}