#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

semid semCreate(const char* name, int val) {
    semid s;
    s = sem_open(name, O_CREAT|O_EXCL, 0644, val);
    if(s==SEM_FAILED) {
        perror("sem_open error");
        _exit(1);
    }
    printf("Creating the semaphore\n");
    return s;
}
void semRemove(const char* name) {
    if(sem_unlink(name)) {
        perror("sem_unlink error");
        exit(1);
    }
    printf("Removing the semaphore\n");
}
semid semOpen(const char* name) {
    semid s = sem_open(name, O_RDWR);
    if(s==SEM_FAILED) {
        perror("sem_open error");
        _exit(1);
    }
    printf("Opening the semaphore\n");
    return s;
}
void semClose(semid sem) {
    if(sem_close(sem)) {
        perror("sem_close error");
        exit(1);
    }
    printf("Closing the semaphore\n");
}
void semP(semid sem) {
    if(sem_wait(sem)) {
        perror("sem_wait error");
        exit(1);
    }
    printf("Decrementing the semaphore\n");
}
void semV(semid sem) {
    if(sem_post(sem)) {
        perror("sem_post error");
        exit(1);
    }
    printf("Incrementing the semaphore\n");
}
void semInfo(semid sem) {
    int sval;
    if(sem_getvalue(sem, &sval)) {
        perror("sem_getvalue error");
        exit(1);
    }
    if(sval>=0) {
        printf("Value: %d\n", sval);
    } else {
        printf("Waiting processes: %d\n", -(sval));
    }
}