#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    switch(fork()) { 
        case -1: 
            perror("fork error"); 
            exit(1);
        case 0: break;
        default: sleep(100); break;
    }
}