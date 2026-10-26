
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void)
{
    int ret, i, count;

    printf("program started !!!\n");

    for(i = 0; i < 5; i++)
    {
        ret = fork();

        if(ret == -1)
        {
            perror("fork failed");
            exit(1);
        }
        else if(ret == 0)
        {
            // child process
            for(count = 1; count <= 5; count++)
            {
                printf("child (%d) : count = %d\n",
                       getpid(), count);
                sleep(1);
            }

            _exit(0);
        }
        else
        {
            // parent process
            printf("Child created with PID = %d\n", ret);
        }
    }

    // parent process: wait for all children
    while(wait(NULL) > 0)
    {
        // cleanup each child
    }

    printf("All children completed !!!\n");

    return 0;
}

