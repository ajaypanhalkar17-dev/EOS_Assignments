#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main ()
{

    int pid = fork();
    if(pid == 0)
    {

        while(1)
      {
         printf("infotech");
      }
     
    }else
    {
      while(1)
      {
        printf("sunbeam");
      }
      

    }

}

