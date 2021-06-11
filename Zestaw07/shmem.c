#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include "shmem.h"

int shmCreate(const char* name, int size) {
    int des = shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0644);
    if(des==-1) {
        perror("shmCreate create error");
        _exit(1);
    }
    printf("Creating a sharing memory\n");
    if(ftruncate(des, size)) {
        perror("shmCreate truncate error");
        exit(1);
    }
    printf("Setting a size of a sharing memory\n");
    return des;
}

int shmOpen(const char* name) {
    int des = shm_open(name, O_RDWR, 0644);
    if(des==-1) {
        perror("shmOpen error");
        exit(1);
    }
    printf("Opening a sharing memory\n");
    return des;
}

void shmRm(const char* name) {
    if(shm_unlink(name)) {
        perror("shmRm error");
        exit(1);
    }
    printf("Removing a sharing memory\n");
}

void* shmMap(int fd, int size) {
    void* ptr = mmap(NULL, size, PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr==MAP_FAILED) {
        perror("shmMap error");
        exit(1);
    }
    printf("Mapping a sharing memory\n");
    return ptr;
}

void shmClose(void *ptr, int fd, int size) {
    if(munmap(ptr, size)) {
        perror("shmClose munmap error");
        exit(1);
    }
    if(close(fd)) {
        perror("shmClose close error");
        exit(1);
    }
    printf("Closing a sharing memory\n");
}

int shmSize(int fd) {
    struct stat* buf;
    if(fstat(fd, buf)) {
        perror("shmSize error");
        exit(1);
    }
    printf("Checking a size of a sharing memory out\n");
    return buf->st_size;
}

void shmInfo(int fd) {
    struct stat *buf = (struct stat *)malloc(1024);
    if(fstat(fd, buf)) {
        perror("shmInfo error");
        exit(1);
    }
    printf("Rozmiar: %d, Wlasciciel: %d\n", buf->st_size, buf->st_uid);
    free(buf);
}