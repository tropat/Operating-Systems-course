#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "sem.h"
#include "shmem.h"

void end() {
    shmRm("/shm");
    semRemove("/sem1");
    semRemove("/sem2");
    _exit(1);
}

void my_sighandler() {
    end();
}

int main(int argc, const char* argv[]) {
    semid sem1 = semCreate("/sem1",1);
    semid sem2 = semCreate("/sem2",1);
    int fd = shmCreate("/shm",1024);

    atexit(end);
    if(signal(SIGINT,my_sighandler) == SIG_ERR) {
        perror("signal error (p)");
        exit(1);
    }

    semClose(sem1);
    semClose(sem2);
    if(close(fd)==-1) {
        perror("close error");
        exit(1);
    }

    int i=0, id=-1;
    id=fork();
    if(id==-1) {
        perror("fork error");
        exit(1);
    } else if(id==0) {
        if(execl("./producent.x", argv[0], NULL)==-1) {
            perror("execl error");
            exit(1);
        }
    }

    id=fork();
    if(id==-1) {
            perror("fork error");
        exit(1);
    } else if(id==0) {
        if(execl("./konsument.x", argv[0], NULL)==-1) {
            perror("execl error");
            exit(1);
        }
    }

    for(i=0;i<2;++i) {
        wait(NULL);
    }
}