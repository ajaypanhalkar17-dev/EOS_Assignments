
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);

    while(1)
    {
        printf("Shell is running...\n");
        sleep(1);
    }

    return 0;
}

