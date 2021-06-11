#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "procinfo.h"

int main(int argc, const char* argv[]) {
    procinfo(argv[0]);
    int i,er=0;
    for(i=0;i<3;i++) {
        switch(fork()) { // TWORZENIE PROCESU POTOMNEGO I WYPISYWANIE IDENTYFIKATOROW
            case -1: 
                perror("fork error"); 
                exit(1);
            case 0: 
                sleep(1); 
                er=setpgid(0,0); // USTAWIA SWOJ PID NA MIEJSCU PGID
                procinfo(argv[0]); // PROCINFO.H
                break;
            default: break;
        }
        if(er==-1) {
            perror("getpgid error");
            exit(-1);
        }
    }
    while(wait(NULL)>0||errno!=ECHILD); // CZEKA NA WSZYSTKIE PROCESY POTOMNE
}