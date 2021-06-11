#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
    if(argc != 3) {
        printf("Niepoprawna liczba argumentow!\n");
        exit(1);
    }

    int pid=-1;
    int stat=-1;
    int i=0;
    int syg=atoi(argv[2]);

    switch(pid=fork()) {
        case -1:
            perror("fork error");
            exit(1);
        case 0:
            if(setpgid(0,0)) {
                perror("setpgid error");
                exit(1);
            }
            if(signal(syg,SIG_IGN) == SIG_ERR) {
                perror("signal error");
                exit(1);
            }
            
            for(i=0;i<3;i++) {
                if(!fork()) {
                    execl("./obsluga.x", argv[0], argv[1], argv[2], NULL);
                }
            }
            for(i=0;i<3;i++) {
                if(wait(&stat)>=0) {
                    printf("%d\n", stat);
                }
            }
            break;
        default:
            sleep(1);
            if(kill(-getpgid(pid),0)) {
                perror("kill error");
                exit(1);
            }
            kill(-getpgid(pid),syg);
            break;
    }
    wait(NULL);
}