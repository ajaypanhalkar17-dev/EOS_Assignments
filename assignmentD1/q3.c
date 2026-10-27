#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

volatile sig_atomic_t stop = 0;

void handle_sigint(int sig)
{
    stop = 1;
}

int main()
{
    long count = 0;
    pid_t pid;

    signal(SIGINT, handle_sigint);

    while (!stop)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            break;
        }

        if (pid == 0)
        {
            while (!stop)
                pause();

            _exit(0);
        }

        count++;
    }

    printf("Successfully created children: %ld\n", count);

    while (wait(NULL) > 0)
        ;

    printf("All child processes cleaned up.\n");

    return 0;
}

