#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "msg.h"
#include "dane.h"

void myfunc() {
    char* name2 = (char*)malloc(10);
    sprintf(name2, "/%d", getpid());
    msgRm(name2);
    free(name2);
}

int main() {
    atexit(myfunc);
    signal(SIGINT, exit);

    srand(time(0));
    int t=0;

    char* name2 = (char*)malloc(10);
    sprintf(name2, "/%d", getpid());

    int des2 = msgCreate(name2);
    int des1 = msgOpen(nazwa);

    printf("%s\n", name2);
    msgInfo(des2);

    komunikat mes = {size2, (char*)malloc(size2), 1};
    komunikat w = {size1, (char*)malloc(size1), 1};

    char* dzialanie = (char*)malloc(size2-20);

    while(1) {
        printf("Dzialania: ");
        fgets(dzialanie, size2-20, stdin);
        if(feof(stdin)) break;

        sprintf(mes.ptr, "%d %s", getpid(), dzialanie);
        printf("%s\n", mes.ptr);
        
        t=CZAS;
        printf("Waiting %d\n", t);
        usleep(t);
        msgSend(des1, &mes);

        msgRecv(des2, &w);
        printf("Wynik: %s\n", w.ptr);
    }

    msgClose(des1);
    msgClose(des2);
}