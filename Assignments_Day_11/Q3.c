
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

#define MAX_CHILDREN 100

int main(void)
{
    int ret, count = 0;

    printf("Parent PID = %d\n", getpid());

    while(count < MAX_CHILDREN)
    {
        ret = fork();

        if(ret == -1)
        {
            perror("fork failed");
            break;
        }
        else if(ret == 0)
        {
            // child process
            _exit(0);
        }
        else
        {
            // parent process
            count++;
        }
    }

    printf("Children created = %d\n", count);

    // Clean up all created children
    while(wait(NULL) > 0)
    {
    }

    printf("All children cleaned up !!!\n");

    return 0;
}

