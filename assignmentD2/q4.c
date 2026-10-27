
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigchld(int sig)
{
    int saved_errno = errno;
    int status;

    while (waitpid(-1, &status, WNOHANG) > 0)
        ;

    errno = saved_errno;
}

int main(void)
{
    char line[256];
    char *args[32];

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        printf("MyShell> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        int i = 0;
        char *token = strtok(line, " \t");

        while (token != NULL && i < 31)
        {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }

        args[i] = NULL;

        if (i == 0)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        int background = 0;

        if (strcmp(args[i - 1], "&") == 0)
        {
            background = 1;
            args[--i] = NULL;
        }

        if (i == 0)
            continue;

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGCHLD, SIG_DFL);

            execvp(args[0], args);
            perror("execvp");
            _exit(127);
        }

        if (background)
        {
            printf("Started background process: PID %d\n", pid);
        }
        else
        {
            int status;

            if (waitpid(pid, &status, 0) < 0)
                perror("waitpid");
        }
    }

    return 0;
}

