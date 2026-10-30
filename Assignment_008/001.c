#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
   int no[2];
   int arr1[2];
   int ret1 = pipe(arr1);
   int arr2[2];
   int ret = pipe(arr2);
   char buf[10] ;
   if(ret == -1 || ret1 == -1)
   {
      perror("pipe() is failed ");
      _exit(-1);
   }


   int pid = fork ();
   if(pid == 0)
   {

        close(arr1[0]);
        printf("[%d] Enter 2 no ",getpid());
        fgets(buf,sizeof(buf),stdin);
        write(arr1[1], buf, strlen(buf) + 1);


        close(arr2[1]);
        read(arr2[0], buf, sizeof(buf));
        printf("PID = %d sum = %s\n",getpid(),buf);
   }
   else
   {
     
        close(arr1[1]);
        read(arr1[0], buf, sizeof(buf));
        sscanf(buf, "%d %d", &no[0], &no[1]);

        int sum  = no[0] + no[1];
        sprintf(buf, "%d", sum);

        close(arr2[0]);
        write(arr2[1], buf, strlen(buf) + 1);


   }

}