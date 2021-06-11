#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CZAS rand()%600000+100000

int counter = 0;
const int watkow = 4;
pthread_mutex_t mutex;

void *func(void *argument) {
    int* n = (int*)argument;
    int licznik = -1;
    int i=0;
    for(i=1;i<=3;++i) {
            printf("\033[%d;1H", *n); //ustawienie pozycji
            printf("\033[2K"); //wymazanie wiersza
            printf("\033[33m"); //ustawienie koloru
        printf("Watek: %d iteracja:%d Przed sekcja krytyczna   \n", *n, i);
        usleep(CZAS);

        if(pthread_mutex_lock(&(mutex))) {
            printf("pthread_mutex_lock error\n");
            exit(1);
        }
            usleep(CZAS);

                printf("\033[31m");
                printf("\033[%d;50H", *n);
                printf("\033[2K");
            printf("Watek: %d iteracja:%d W sekcji krytycznej   \n", *n, i);

            licznik = counter;
            ++licznik;
            usleep(CZAS);
            counter = licznik;
            
        if(pthread_mutex_unlock(&(mutex))) {
            printf("pthread_mutex_lock error\n");
            exit(1);
        }
            printf("\033[32m");
            printf("\033[%d;1H", *n);
            printf("\033[2K");
        printf("Watek: %d iteracja:%d Po sekcji krytycznej   \n", *n, i);
        usleep(CZAS);
    }
}

int main(int argc, const char* argv[]) {
    printf("\033c");
    srand(time(0));

    pthread_t id[watkow];
    int i=1;
    int arg[watkow];

    if(pthread_mutex_init(&mutex, NULL)) {
        printf("pthread_mutex_init error\n");
        exit(1);
    }

    for(i=1;i<=watkow;++i) {
        arg[i] = i;
        if(pthread_create(&id[i], NULL, func, (void *)&arg[i])) {
            printf("Pthread error\n");
            exit(1);
        }
    }

    for(i=1;i<=watkow;++i) {
        pthread_join(id[i], NULL);
    }

    printf("\033[%d;1H", watkow+2);
    printf("Counter: %d\n", counter);

    if(pthread_mutex_destroy(&mutex)) {
        printf("pthread_mutex_destroy error\n");
        exit(1);
    }
}