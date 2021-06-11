#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg.h"

int msgCreate(const char *name) {
    int des = (int)mq_open(name, O_RDONLY|O_CREAT|O_EXCL, 0644, NULL);
    if(des==-1) {
        perror("mq_open error");
        exit(1);
    }
    printf("Creating a queue\n");
    return des;
}

int msgOpen(const char *name) {
    int des = (int)mq_open(name, O_WRONLY);
    if(des==-1) {
        perror("mq_open error");
        exit(1);
    }
    printf("Opening a queue\n");
    return des;
}

void msgClose(int msgid) {
    if(mq_close((mqd_t)msgid)) {
        perror("mq_close error");
        exit(1);
    }
    printf("Closing a queue\n");
}

void msgRm(const char *name) {
    if(mq_unlink(name)) {
        perror("mq_unlink error");
        exit(1);
    }
    printf("Removing a queue\n");
}

void msgSend(int msgid, komunikat *msg) {
    if(mq_send(msgid, msg->ptr, msg->len, msg->prio)) {
        perror("mq_send error");
        exit(1);
    }
    printf("Sending a message\n");
}

void msgRecv(int msgid, komunikat *msg) {
    if(mq_receive(msgid, msg->ptr, msg->len, &(msg->prio))==-1) {
        perror("mq_receive error");
        exit(1);
    }
    printf("Receiving a message\n");
}

void msgInfo(int msgid) {
    struct mq_attr attr;
    if(mq_getattr(msgid, &attr)) {
        perror("mq_getattr error");
        exit(1);
    }
    printf("Opcje: %ld\n", attr.mq_flags);
    printf("Max liczba komunikatow: %ld\n", attr.mq_maxmsg);
    printf("Max rozmiar komunikatu: %ld\n", attr.mq_msgsize);
    printf("Liczba komunikatow aktualnie w kolejce: %ld\n", attr.mq_curmsgs);
}