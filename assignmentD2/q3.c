#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    char line[256];
    char *args[32];

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

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);

            execvp(args[0], args);
            perror("execvp");
            _exit(127);
        }

        int status;

        if (waitpid(pid, &status, 0) < 0)
            perror("waitpid");
    }

    return 0;
}

