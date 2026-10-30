#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>



int main(void)
{
    
    char *url = "https:/google.com";

  int pid = fork();
   if(pid < 0)
   {
      printf("fork failed");
   }
   if(pid == 0)
   {
      execlp("xdg-open", "xdg-open", url, NULL);     

   }else
   {
      int s;
      wait(&s);
   }


}