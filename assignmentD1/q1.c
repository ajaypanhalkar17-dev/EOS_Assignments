
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i, count;
    pid_t pid;

    for (i = 0; i < 5; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0)
        {
            for (count = 1; count <= 5; count++)
            {
                printf("Child PID: %d, Count: %d\n",
                       getpid(), count);
                sleep(1);
            }

            exit(0);
        }
    }

    for (i = 0; i < 5; i++)
    {
        wait(NULL);
    }

    printf("Parent: All child processes completed.\n");

    return 0;
}

            


    
