#define _REENTRANT
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

const int watkow = 3;
volatile int licznik = 0;

bool wybieranie[4] = {false};
int numer[4] = {0};

int max(int tab[], int n) {
    int i=0;
    int max = tab[0];
    for(i=1;i<n;++i)
        if(tab[i]>max) max = tab[i];
    return max;
}

void lock(int n) {
    wybieranie[n] = true;
    numer[n] = max(numer, watkow)+1;
    wybieranie[n] = false;
    int i=0;
    for(i=0;i<watkow;++i) {
        while(wybieranie[i]);
        while(numer[i] != 0 && ((numer[i] < numer[n]) || ((numer[i] == numer[n]) && i<n)));
    }
}

void unlock(int n) {
    numer[n] = 0;
}

void *thread (void *arg) {
    int *n = (int *)arg;
    int i=1;
    for(i=1; i<=10000; ++i) {
        lock(*n);

        licznik = licznik + 1;

        unlock(*n);
    }
}

int main(int argc, const char* argv[]) {
    pthread_t id[watkow];
    int i=1;

    int arg[watkow];

    for(i=1;i<=watkow;++i) {
        arg[i] = i;
        if(pthread_create(&id[i], NULL, thread, (void *)&arg[i])) {
            printf("Pthread error\n");
            exit(1);
        }
    }

    for(i=1;i<=watkow;++i) {
        pthread_join(id[i], NULL);
    }

    printf("Licznik: %d\n", licznik);
}