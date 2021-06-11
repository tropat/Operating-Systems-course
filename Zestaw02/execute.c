#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    printf("Pierwszy komunikat\n");
    execl("potomny.x",argv[0],NULL);
    printf("Drugi komunikat\n");
}