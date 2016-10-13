#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<signal.h>

struct mymsg {
    long mtype;
    char mtext[32];
};

int msgid;

void fa (int signo) {
    msgctl (msgid, IPC_RMID, NULL);   
    printf ("消息队列已关闭\n");
    exit (0);
}

int 
main () {
    //设置SIGINT:CTRL+C时关闭消息队列并退出
    printf ("---------CTRL + C 退出---------\n");
    signal (SIGINT, fa);
    //获取消息队列号msgid
    key_t key = ftok (".", 100);
    msgid = msgget (key, IPC_CREAT | 0660);
    if (msgid == -1) {
        perror ("msgget");
        exit (-1);
    }

    int i;
    //发送消息
    struct mymsg msg;
    printf ("开始发送消息 ...\n");
    for (i = 0;i < 20;++i) {
        msg.mtype = i + 1;      
        sprintf (msg.mtext, "MSG: No. %02d", i + 1);
        msgsnd (msgid, &msg, 
            sizeof(msg) - sizeof(long), 0);
        printf ("消息%2d发送成功！\n", i + 1);
        usleep (100000);
    }
    //休眠60s
    sleep (60);
    //在没有SIGINT信号情况下删除消息队列
    msgctl (msgid, IPC_RMID, NULL);
    return 0;
}   
