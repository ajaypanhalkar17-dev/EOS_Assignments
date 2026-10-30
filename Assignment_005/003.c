#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>



int main(void)
{
    int count =0;
   while(1)
   {
      int pid = fork();
      if (pid < 0) 
      {
          printf("\n[LIMIT HIT] The operating system refused to create more processes.\n");
          break; // This terminates the loop naturally
      }
      if(pid == 0)
      {
          while(1) { 
             sleep(1000); 
         }
         _exit(0);
      }
      else
      {
        count ++;
         if (count % 500 == 0) {
              printf("Current spawned count = %d\n", count);
          }
      }
    
   } 
   printf(" total count = %d\n",count);
   
//   int s;
//   wait(&s);
  

}