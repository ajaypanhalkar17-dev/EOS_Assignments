// //The client process send two numbers to the server process via one ﬁfo. The server process calculate
// //the sum and return via another ﬁfo. The client process print the result.



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

// int main()
// {
    
//     char buf[64];
//     int no[2];

//     int pid1 = fork();
//     if(pid1 ==0)
//     {
//         int fd1 = open("/home/sunbeam/fifo1",O_WRONLY);
//         int fd2 = open("/home/sunbeam/fifo2",O_RDONLY);
//        printf("Enter 2 no : ");
//        fgets(buf,sizeof(buf),stdin);
       
//        write (fd1,buf,strlen(buf)+1);

//        read(fd2, buf, sizeof(buf));
//        printf("sum = %s",buf);
       
//        close(fd1);
//        close(fd2);

//        exit(0);

//     }

//     int pid2 = fork();
//     if(pid2 == 0)
//     {
//         int fd1 = open("/home/sunbeam/fifo1",O_RDONLY);
//         int fd2 = open("/home/sunbeam/fifo2",O_WRONLY);
//          read(fd1, buf, sizeof(buf));
//          sscanf(buf, "%d %d", &no[0], &no[1]);

//          int sum = no[0] + no[1];
//          sprintf(buf, "%d", sum);

//          write (fd2,buf,strlen(buf)+1);
         
//          close(fd1);
//          close(fd2);

//         exit(0);
//     }
    
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);

// }








// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <stdlib.h>

int main()
{
    char buf[64];
    int no[2];

    int pid1 = fork();
    if(pid1 == 0)
    {
        // CLIENT PROCESS
        int fd1 = open("fifo1", O_WRONLY); // Sends data out
        int fd2 = open("fifo2", O_RDONLY); // Receives data back
        
        printf("Enter 2 no : ");
        fgets(buf, sizeof(buf), stdin);
       
        write(fd1, buf, strlen(buf) + 1);

        read(fd2, buf, sizeof(buf));
        printf("sum = %s\n", buf);
       
        close(fd1);
        close(fd2);
        exit(0);
    }

    int pid2 = fork();
    if(pid2 == 0)
    {
        // SERVER PROCESS
        int fd1 = open("fifo1", O_RDONLY); // Receives data from client
        int fd2 = open("fifo2", O_WRONLY); // Sends data back to client
        
        read(fd1, buf, sizeof(buf)); // <-- Fixed: Reads from client via fd1
        sscanf(buf, "%d %d", &no[0], &no[1]);

        int sum = no[0] + no[1];
        sprintf(buf, "%d", sum);

        write(fd2, buf, strlen(buf) + 1); // <-- Fixed: Sends result via fd2
         
        close(fd1);
        close(fd2);
        exit(0);
    }
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
