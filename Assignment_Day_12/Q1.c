
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(void)
{
    int i, ret, status, success = 1;
    pid_t pid[4];

    char *cmds[4][4] = {
        {"gcc", "-c", "circle.c", NULL},
        {"gcc", "-c", "square.c", NULL},
        {"gcc", "-c", "rectangle.c", NULL},
        {"gcc", "-c", "main.c", NULL}
    };

    printf("Compilation started !!!\n");

    // Create four children
    for(i = 0; i < 4; i++)
    {
        ret = fork();

        if(ret == -1)
        {
            perror("fork failed");
            success = 0;
            break;
        }
        else if(ret == 0)
        {
            // Child process
            execvp(cmds[i][0], cmds[i]);

            perror("execvp failed");
            _exit(127);
        }
        else
        {
            // Parent process
            pid[i] = ret;
        }
    }

    // Wait for every successfully created child
    for(int j = 0; j < i; j++)
    {
        if(waitpid(pid[j], &status, 0) == -1)
        {
            perror("waitpid failed");
            success = 0;
        }
        else if(!WIFEXITED(status) ||
                WEXITSTATUS(status) != 0)
        {
            success = 0;
        }
    }

    if(!success)
    {
        printf("Compilation failed !!!\n");
        return 1;
    }

    // Link object files
    ret = fork();

    if(ret == 0)
    {
        char *args[] = {
            "gcc", "-o", "program.out",
            "circle.o", "square.o",
            "rectangle.o", "main.o", NULL
        };

        execvp(args[0], args);
        perror("link failed");
        _exit(127);
    }
    else if(ret > 0)
    {
        waitpid(ret, &status, 0);

        if(!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        {
            printf("Linking failed !!!\n");
            return 1;
        }
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    // Execute the final program
    ret = fork();

    if(ret == 0)
    {
        execl("./program.out", "program.out", NULL);
        perror("execution failed");
        _exit(127);
    }
    else if(ret > 0)
    {
        waitpid(ret, &status, 0);
        printf("Program execution completed !!!\n");
    }
    else
    {
        perror("fork failed");
        return 1;
    }

    return 0;
}

