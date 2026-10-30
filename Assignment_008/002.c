#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
    int count =0;
     int arr[2];
     char data = 'A';
        pipe(arr);
        fcntl(arr[1], F_SETFL, O_NONBLOCK);

    while( write(arr[1], &data,1)>0)
    {
       
        
       
       count++;


    }

 printf("Pipe buffer size: %d bytes\n", count);

}
