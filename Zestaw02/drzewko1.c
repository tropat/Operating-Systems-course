#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "procinfo.h"

int main(int argc, const char* argv[]) {
    procinfo(argv[0]);
    int i,id,licznik=0;
    for(i=0;i<3;i++) {
        switch(id=fork()) { // TWORZENIE PROCESU POTOMNEGO I WYPISYWANIE IDENTYFIKATOROW
            case -1: 
                perror("fork error"); 
                exit(1);
            case 0: 
                licznik = 0;
                sleep(1); 
                procinfo(argv[0]); // PROCINFO.H
                break;
            default: licznik++; break;
        }
        if(id==0) break; // PRZEWRANIE PETLI DLA PROCESU POTOMNEGO (ZADEN PROCES POTOMNY NIE BEDZIE RODZICEM)
    }
    for(i=0;i<licznik;i++) {
        wait(NULL);
    }
    //while(wait(NULL)>0||errno!=ECHILD); // CZEKA NA WSZYSTKIE PROCESY POTOMNE
}