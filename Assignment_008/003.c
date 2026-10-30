#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <string.h>



int main(void)
{

   int arr[2];
   pipe(arr);
   int s1,s2;

    int pid1 = fork();
    if(pid1 ==-1)
    {
        printf("fork failed\n");
    }

    if(pid1 ==0)
    {
        close(arr[0]);
        dup2(arr[1],1);
        close(arr[1]);
        int err=execlp("who","who",NULL);


    }
    
    int pid2 = fork();
    if(pid2 ==0){
      
        close(arr[1]);
        dup2(arr[0],0);
        close(arr[0]);
        int err=execlp("wc","wc",NULL);


    }
    
    close(arr[1]);
    close(arr[0]);

    waitpid(pid1,&s1,0);
    waitpid(pid2,&s2,0);

}