#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    if(argc != 3) {
        printf("Niepoprawna liczba argumentow!\n");
        exit(1);
    }

    int syg = atoi(argv[2]);
    int pid=-1;

    switch(pid=fork()) {
        case -1:
            perror("fork error");
            exit(1);
        case 0: 
            if(execl("./obsluga.x", argv[0], argv[1], argv[2], NULL)) {
                perror("execl error");
                exit(1);
            } 
            break;
        default: 
            sleep(1);
            if(kill(pid,0)) {
                perror("kill error");
                exit(1);
            }
            kill(pid,syg);
            break;
    }

    wait(NULL);
}