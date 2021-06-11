#ifndef MSG_H
#define MSG_H
#include <stdio.h>
#include <sys/types.h>

struct komunikat {
    size_t len;
    char* ptr;
    unsigned int prio;
};

typedef struct komunikat komunikat;

int msgCreate(const char *name);
int msgOpen(const char *name);
void msgClose(int msgid);
void msgRm(const char *name);
void msgSend(int msgid, komunikat *msg);
void msgRecv(int msgid, komunikat *msg);
void msgInfo(int msgid);
#endif