#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include "prod.h"
#include "kons.h"

int fun(int fd[]) {
    printf("Sizeof(fd): %ld\n",sizeof(fd));
    return pipe(fd);
}

int main(int argc, const char* argv[]) {
    int fd[20];
    

    //int potok = pipe(fd);
    int potok = fun(fd);

    if(potok) {
        perror("pipe error");
        exit(1);
    }
    
    switch(fork()) {
        case -1:
            perror("fork error");
            exit(1);
        case 0: 
            close(fd[1]);
            kons(fd[0]);
            break;
        default:
            close(fd[0]);
            prod(fd[1]);
            wait(NULL);
            break;
    }
}