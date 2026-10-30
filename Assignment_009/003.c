
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define SERV_IP       "127.0.0.1"
#define SERV_PORT      4000

int main (void)
{
    struct sockaddr_in ser_addr;
    struct sockaddr_in cli_addr;
    char buf[64];
    int no[2];

    ////////// Server Process /////////
    int pid1 = fork();
    if(pid1 == -1)
    {
       perror("fork() failed");
    }

    if(pid1 == 0)
    {
       int ser_id = socket(AF_INET, SOCK_STREAM, 0);

       
       int opt = 1;
       setsockopt(ser_id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

       //// Bind //
       ser_addr.sin_family = AF_INET;
       ser_addr.sin_port = htons(SERV_PORT);
       inet_aton(SERV_IP, &ser_addr.sin_addr);
       bind(ser_id, (const struct sockaddr *)&ser_addr, sizeof(ser_addr));

       /// Listen ///
       listen(ser_id, 5);

       /// Accept //
       socklen_t socklen = sizeof(cli_addr);
       
       int stream_id = accept(ser_id, (struct sockaddr *)&cli_addr, &socklen);

       
       recv(stream_id, buf, sizeof(buf), 0);
       sscanf(buf, "%d %d", &no[0], &no[1]);

       int sum = no[0] + no[1];
       sprintf(buf, "%d", sum);

       send(stream_id, buf, strlen(buf) + 1, 0);

       close(stream_id);
       close(ser_id);
       _exit(0);
    }
   
   
    //////////////////// Client Process /////////
    int pid2 = fork();
    if(pid2 == -1)
    {
       perror("fork() failed");
    }

    if(pid2 == 0)
    {
       

       int cli_id = socket(AF_INET, SOCK_STREAM, 0);

       //// Connect //
       ser_addr.sin_family = AF_INET;
       ser_addr.sin_port = htons(SERV_PORT);
       inet_aton(SERV_IP, &ser_addr.sin_addr);
       connect(cli_id, (const struct sockaddr *)&ser_addr, sizeof(ser_addr));
       
       printf("enter 2 no :");
       fflush(stdout); 
       fgets(buf, sizeof(buf), stdin);
       send(cli_id, buf, strlen(buf) + 1, 0);

       
       memset(buf, 0, sizeof(buf));

       recv(cli_id, buf, sizeof(buf), 0);
       printf("sum : %s\n", buf);

       close(cli_id);
       _exit(0);
    }

    int s1, s2;
    waitpid(pid1, &s1, 0);
    waitpid(pid2, &s2, 0);

    return 0;
}
