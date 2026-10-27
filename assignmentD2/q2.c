#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

pid_t start_command(char *args[])
{
    pid_t pid = fork();

    if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp");
        _exit(127);
    }

    if (pid < 0)
        perror("fork");

    return pid;
}

int wait_success(pid_t pid)
{
    int status;

    if (pid < 0)
        return 0;

    if (waitpid(pid, &status, 0) < 0)
    {
        perror("waitpid");
        return 0;
    }

    if (WIFEXITED(status))
    {
        int code = WEXITSTATUS(status);
        printf("PID %d exit status: %d\n", pid, code);
        return code == 0;
    }

    if (WIFSIGNALED(status))
        printf("PID %d terminated by signal %d\n",
               pid, WTERMSIG(status));

    return 0;
}

int main(void)
{
    char *commands[4][4] = {
        {"gcc", "-c", "circle.c", NULL},
        {"gcc", "-c", "square.c", NULL},
        {"gcc", "-c", "rectangle.c", NULL},
        {"gcc", "-c", "main.c", NULL}
    };

    pid_t pids[4];
    int i, all_success = 1;

    for (i = 0; i < 4; i++)
        pids[i] = start_command(commands[i]);

    for (i = 0; i < 4; i++)
    {
        if (!wait_success(pids[i]))
            all_success = 0;
    }

    if (!all_success)
    {
        printf("Compilation failed. Linking skipped.\n");
        return 1;
    }

    printf("All source files compiled successfully.\n");

    char *link_cmd[] = {
        "gcc", "-o", "program.out",
        "circle.o", "square.o", "rectangle.o", "main.o",
        NULL
    };

    pid_t link_pid = start_command(link_cmd);

    if (!wait_success(link_pid))
    {
        printf("Linking failed. Execution skipped.\n");
        return 1;
    }

    printf("Linking successful.\n");

    char *run_cmd[] = {"./program.out", NULL};
    pid_t run_pid = start_command(run_cmd);

    if (!wait_success(run_pid))
    {
        printf("Program execution failed.\n");
        return 1;
    }

    printf("Build and execution completed.\n");

    return 0;
}

