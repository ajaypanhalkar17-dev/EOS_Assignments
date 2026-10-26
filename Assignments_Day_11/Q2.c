
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void)
{
    int ret, level = 0, count;
    pid_t child_pid = -1;

    printf("Process started !!! PID = %d\n", getpid());

    while(level < 3)
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
            level++;
            continue;
        }
        else
        {
            // parent process
            child_pid = ret;
            break;
        }
    }

    // Every process runs for 5 seconds
    for(count = 1; count <= 5; count++)
    {
        printf("PID = %d, PPID = %d, Count = %d\n",
               getpid(), getppid(), count);
        sleep(1);
    }

    // Each parent waits for its own child
    if(child_pid > 0)
    {
        waitpid(child_pid, NULL, 0);
    }

    printf("Process completed !!! PID = %d\n", getpid());

    return 0;
}

