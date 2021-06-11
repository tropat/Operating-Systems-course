#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    int id = fork();
    if(id==0) {
        sleep(100);
    } else if(id==-1) {
        perror("fork error");
        exit(1);
    }
}