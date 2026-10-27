#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        execlp("xdg-open", "xdg-open",
               "https://www.google.com", (char *)NULL);

        perror("execlp");
        exit(1);
    }

    waitpid(pid, NULL, 0);

    printf("Child process completed.\n");

    return 0;
}

