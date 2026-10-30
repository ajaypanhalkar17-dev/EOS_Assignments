#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

#define SHM_KEY    0x1234
#define SIZE    5

typedef struct cir_buf
{
  
   int arr[SIZE];
   int front ;
   int rear;
   int count;n

}cirbuf_t;

void cirbuf_init(cirbuf_t *cirbuf)
{

      cirbuf->front = cirbuf->rear = -1;
      cirbuf->count =0;

}
void cirbuf_push(int value , cirbuf_t *cirbuf)
{

     cirbuf->rear = (cirbuf->rear + 1) % SIZE;
     cirbuf->arr[cirbuf->rear] = value;
     



}

int cirbuf_pop(cirbuf_t *cirbuf)
{
    
    cirbuf->front = (cirbuf ->front + 1) % SIZE;
    int val = cirbuf->arr[cirbuf->front];
    return val;

}


int main(void)
{


    int shmid = shmget(SHM_KEY,3,IPC_CREAT | 0600);
 
    cirbuf_t *ptr;
    ptr = (cirbuf_t*)shmat(shmid,NULL,0);


    int pid = fork();

    if(pid == -1)
    {
       perror("fork failed");
    }

    if(pid == 0)
    {
        while(1)
        {
            int val = cirbuf_pop(ptr);
            printf("child prosess : [%d] buff ele at address %u value = %d", getpid(),ptr,*ptr);
            sleep(1);
        }

    }else
    {

        while(1)
        {
            int val = rand()  %100;
            cirbuf_push (val,ptr);
            printf("parent prosess : [%d] buff ele at address %u value = %d",getpid(),ptr,*ptr);
            sleep(1);
        }

    }



}