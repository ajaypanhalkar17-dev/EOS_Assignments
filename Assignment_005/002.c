#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
   int pid_A , pid_B,pid_C,pid_D;
    

       pid_A = fork();
       if(pid_A == 0)
       {
           printf("PID_A = %d\n",getpid());
           sleep(5);
           pid_B = fork();
           if(pid_B == 0)
           {
               printf("PID_B = %d\n",getpid());
               sleep(5);
               pid_C = fork();
               if(pid_C == 0)
               {
                 printf("PID_C = %d\n",getpid());
                 sleep(5);
                 pid_D = fork();
                 if(pid_D == 0)
                 {
                    printf("PID_D = %d\n",getpid());
                    sleep(5);
           
                 }  
           
               }  
           
           }  

       }  

    

   int s;
   wait(&s);

}