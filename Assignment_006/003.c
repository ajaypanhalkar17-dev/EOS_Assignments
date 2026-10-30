#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

void siginit_handle( int signo)
{
      printf("SIGINTI is handle");
}



int main (void)
{
    signal(SIGINT,siginit_handle);
    int pid;
    char *cmd[4][4] = {

      {"gcc" , "-c" ,"001/cir.c",NULL},
      {"gcc" , "-c" ,"001/sq.c", NULL},
      {"gcc" , "-c" ,"001/rec.c",NULL},
      {"gcc" , "-c" ,"001/main.c",NULL},


    };

    char *link_cmd[] = {"gcc","cir.o","sq.o","rec.o","main.o","-o" ,"result",NULL}; 
    char  *exute_cmd[] = {"./result",NULL};

   for(int i = 0;i<4;i++)
   {

      pid = fork();
      if(pid < 0)
      {
        printf("fork faield");
      }
      if(pid == 0)
      {
          
          execvp(cmd[i][0], cmd[i]);
          exit(1);

      }
      else
      {
          int s ;
          wait(&s);

      }

   }

   pid = fork();
   if(pid == 0)
   {
      execvp(link_cmd[0],link_cmd);
      exit(1);
   }
   else
   {
          int s ;
          wait(&s);

    }

    pid = fork();
   if(pid == 0)
   {
      execvp(exute_cmd[0],exute_cmd);
      exit(1);
   }
   else
   {
          int s ;
          wait(&s);

    }


   


}