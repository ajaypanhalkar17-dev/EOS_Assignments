#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>



#define MSQ_KEY   0x1234
#define MTYPE      22

struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char msg[32];    /* message data */
};

int main(void)
{
    int n1 ,n2;
     int mesqid = msgget(MSQ_KEY,IPC_CREAT | 0600);
     if(mesqid == -1)
     {
        perror("msgget failed !!!");
     }

     int pid = fork ();
     if(pid == -1)
     {
        perror("fork() failed !!!");
     }
     if(pid == 0)
     {
          struct msgbuf msgq;
          msgq.mtype = MTYPE;
          printf("PID : %d ENTER 2 no : ",getpid());
          fflush(stdout);
          fgets(msgq.msg,sizeof(msgq.msg),stdin);
          msgsnd(mesqid, &msgq, sizeof(msgq.msg), 0);
         // sleep(1);

         msgrcv(mesqid, &msgq, sizeof(msgq.msg),MTYPE , 0);
         printf("PID : %d sum = %s\n",getpid(),msgq.msg);
        _exit(0);

     }else{

       struct msgbuf m2;
       msgrcv(mesqid, &m2, sizeof(m2.msg),MTYPE , 0);
       sscanf(m2.msg, "%d %d", &n1, &n2);
       int sum = n1+n2;
       sprintf(m2.msg, "%d", sum);
       m2.mtype = MTYPE;
       msgsnd(mesqid, &m2, sizeof(m2.msg), 0);
       
       int s;
       wait(&s);

       msgctl(mesqid, IPC_RMID, NULL);

     }


    return 0;
}