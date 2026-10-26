
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void)
{
    int ret, status;

    printf("program started !!!\n");

    ret = fork();

    if(ret == -1)
    {
        perror("fork failed");
        exit(1);
    }
    else if(ret == 0)
    {
        // child process
        execlp("firefox", "firefox",
               "https://www.google.com", NULL);

        // Executes only if execlp fails
        perror("execlp failed");
        _exit(1);
    }
    else
    {
        // parent process
        waitpid(ret, &status, 0);

        if(WIFEXITED(status))
        {
            printf("Child exit status = %d\n",
                   WEXITSTATUS(status));
        }
    }

    printf("program finished !!!\n");
    return 0;
}

