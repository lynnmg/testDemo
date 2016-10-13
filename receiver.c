#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>

struct mymsg {
    long mtype;
    char mtext[32];
};

int
main () {
    key_t key = ftok (".", 100);
    int msgid = msgget (key, 0);
    if (msgid == -1) {
        perror ("msgget");
        exit (-1);
    }

    struct mymsg msg;
    //循环获取消息队列中的消息
    while (1) {
        int res = msgrcv (msgid, &msg, 
                sizeof(msg) - sizeof(long), 0, 0);
        if (res == -1)
            exit (0);
        printf ("%s  TYPE: %3ld\n",  
                msg.mtext, msg.mtype);
    }

    return 0;
}
