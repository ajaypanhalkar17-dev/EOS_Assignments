#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
   int count =1;
    for(int i = 0; i<= 4 ;i++)
    {
      int pid = fork();
      if(pid == 0)
      {
        for(int j = 0; j<= 5 ;j++)
        {   printf("[%d] : count = %d\n" , getpid(), count++);
           sleep(1);
        }

        count =0;
        _exit(0);
      }

     int s;
     wait(&s); 
   
    }

   

}