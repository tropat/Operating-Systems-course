#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "procinfo.h"

void my_sighandler(int);

int main(int argc, const char* argv[]) {
    if(argc != 3) {
        printf("Niepoprawna liczba argumentow!\n");
        exit(1);
    }

    procinfo(argv[0]);

    int syg = atoi(argv[2]);

    switch((argv[1])[0]) {
        case 'd': 
            if(signal(syg,SIG_DFL) == SIG_ERR) {
                perror("signal error (d)");
                exit(1);
            }
            break;
        case 'i':
            if(signal(syg,SIG_IGN) == SIG_ERR) {
                perror("signal error (i)");
                exit(1);
            }
            break;
        case 'p':
            if(signal(syg,my_sighandler) == SIG_ERR) {
                perror("signal error (p)");
                exit(1);
            }
            break;
        default:
            printf("Niepoprawny argument!\nWpisz d, i lub p\n");
            exit(1);
    }

    pause();
}

void my_sighandler(int sig) {
    printf("%d\n",sig);
}