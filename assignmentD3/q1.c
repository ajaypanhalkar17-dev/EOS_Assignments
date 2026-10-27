
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message
{
    long mtype;
    int num1;
    int num2;
    int sum;
};

int main(void)
{
    int msgid;
    pid_t pid;
    struct message msg;

    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }

    if (pid == 0)
    {
        msg.mtype = 1;
        msg.num1 = 10;
        msg.num2 = 20;

        msgsnd(msgid, &msg,
               sizeof(msg) - sizeof(long), 0);

        msgrcv(msgid, &msg,
               sizeof(msg) - sizeof(long), 2, 0);

        printf("Child: Sum = %d\n", msg.sum);

        exit(0);
    }
    else
    {
        msgrcv(msgid, &msg,
               sizeof(msg) - sizeof(long), 1, 0);

        msg.sum = msg.num1 + msg.num2;
        printf("Parent: Sum calculated = %d\n", msg.sum);

        msg.mtype = 2;

        msgsnd(msgid, &msg,
               sizeof(msg) - sizeof(long), 0);

        waitpid(pid, NULL, 0);

        printf("Parent: Child completed.\n");

        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}

