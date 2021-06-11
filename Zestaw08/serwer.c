#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "dane.h"
#include "msg.h"

int des1 = -1;

void myfunc() {
    msgClose(des1);
    msgRm(nazwa);
}

int main() {
    atexit(myfunc);
    signal(SIGINT, exit);

    srand(time(0));
    int t=0;

    des1 = msgCreate(nazwa);
    int des2 = -1;

    printf("%s\n", nazwa);
    msgInfo(des1);

    char operation;
    char * liczba = (char*)malloc(10);
    int l1 = 0;
    int l2 = 0;
    char* pid = (char*)malloc(10);
    int wynik=0;
    int i = 0, j=1;

    komunikat mes = {size1, (char*)malloc(size1), 1};
    komunikat w = {size2, (char*)malloc(size2), 1};

    for(;;) {  
        msgRecv(des1, &mes);

        printf("%s\n", mes.ptr);

        pid[0] = '/';
        while(mes.ptr[i]!=' ') {
            pid[j] = mes.ptr[i];
            ++i; ++j;
        } pid[j]='\0'; j=0; ++i;

        printf("%s\n", pid);

        while(mes.ptr[i]!=' ') {
            liczba[j] = mes.ptr[i];
            ++i; ++j;
        } liczba[j]='\0'; j=0;
        l1 = atoi(liczba);

        operation = mes.ptr[i+1];

        printf("\tLiczba 1: %d\nOperacja: %c\n", l1, operation);

        i+=3;
        while(mes.ptr[i]!='\0' && mes.ptr[i]!='\n') {
            liczba[j] = mes.ptr[i];
            ++i; ++j;
        } liczba[j]='\0'; j=1; i=0;
        l2 = atoi(liczba);

        printf("\tLiczba 2: %d\n", l2);

        des2 = msgOpen(pid);

        switch(operation) {
            case '+': 
                wynik = l1 + l2;
                break;
            case '-':
                wynik = l1 - l2;
                break;
            case '*':
                wynik = l1 * l2;
                break;
            case '/':
                if(l2!=0) wynik = l1 / l2;
                break;
            default:
                printf("Blad w komunikacie\n");
                break;
        }

        sprintf(w.ptr, "%d", wynik);
        w.prio = 0;
        w.ptr[strlen(w.ptr)] = '\0';

        printf("\tWynik: %s\n", w.ptr);

        t=CZAS;
        printf("Waiting %d\n", t);
        usleep(t);
        msgSend(des2, &w);

        msgClose(des2);
    }
}