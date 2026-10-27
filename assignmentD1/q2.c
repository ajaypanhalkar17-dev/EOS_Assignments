#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t b, c, d;
    int i;

    b = fork();

    if (b < 0)
    {
        perror("fork");
        exit(1);
    }

    if (b == 0)
    {
        c = fork();

        if (c < 0)
        {
            perror("fork");
            exit(1);
        }

        if (c == 0)
        {
            d = fork();

            if (d < 0)
            {
                perror("fork");
                exit(1);
            }

            if (d == 0)
            {
                for (i = 1; i <= 5; i++)
                {
                    printf("D: PID=%d Count=%d\n",
                           getpid(), i);
                    sleep(1);
                }
                exit(0);
            }

            for (i = 1; i <= 5; i++)
            {
                printf("C: PID=%d Count=%d\n",
                       getpid(), i);
                sleep(1);
            }

            waitpid(d, NULL, 0);
            exit(0);
        }

        for (i = 1; i <= 5; i++)
        {
            printf("B: PID=%d Count=%d\n",
                   getpid(), i);
            sleep(1);
        }

        waitpid(c, NULL, 0);
        exit(0);
    }

    for (i = 1; i <= 5; i++)
    {
        printf("A: PID=%d Count=%d\n", getpid(), i);
        sleep(1);
    }

    waitpid(b, NULL, 0);

    printf("A: All descendants completed.\n");

    return 0;
}

