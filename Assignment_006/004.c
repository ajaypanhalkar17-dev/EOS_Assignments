#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>      
#include <sys/wait.h>
#include <signal.h>


void siginit_handle(int signo)
{
    write(1, "\nSIGINT handled. Shell pipeline running...\n", 42);
}


void sigchld_handle(int signo)
{
    int status;
    pid_t pid;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        
    }
}

int main(int argc, char *argv[])
{
    
    signal(SIGINT, siginit_handle);
    signal(SIGCHLD, sigchld_handle); // ADDED: Protects against zombies

   
    int run_in_background = 0;
    if (argc > 1 && strcmp(argv[argc - 1], "&") == 0) {
        run_in_background = 1;
        printf("[Running toolchain pipeline in background]\n");
    }

    
    if (run_in_background) {
        pid_t pipeline_pid = fork();
        if (pipeline_pid > 0) {
           
            printf("[Pipeline Master PID: %d launched async]\n", pipeline_pid);
            return 0; 
        }
        // The child process falls through to execute the compilation pipeline below
    }

   
    int pid;
    char *cmd[4][4] = {
      {"gcc" , "-c" ,"001/cir.c",  NULL},
      {"gcc" , "-c" ,"001/sq.c",   NULL},
      {"gcc" , "-c" ,"001/rec.c",  NULL},
      {"gcc" , "-c" ,"001/main.c", NULL},
    };

    char *link_cmd[] = {"gcc", "cir.o", "sq.o", "rec.o", "main.o", "-o" , "result", NULL}; 
    char *exute_cmd[] = {"./result", NULL};


    for(int i = 0; i < 4; i++)
    {
        pid = fork();
        if(pid < 0) {
            printf("fork failed\n");
        }
        if(pid == 0) {
            execvp(cmd[i][0], cmd[i]);
            exit(1); // Properly exits if execvp fails
        }
       
    }

    for(int i = 0; i < 4; i++) {
        wait(NULL);
    }

    // Step 2: Linking Stage
    pid = fork();
    if(pid == 0) {
        execvp(link_cmd[0], link_cmd);
        exit(1);
    }
    else {
        int s;
        wait(&s);
    }

    // Step 3: Execution Stage
    pid = fork();
    if(pid == 0) {
        execvp(exute_cmd[0], exute_cmd);
        exit(1);
    }
    else {
        int s;
        wait(&s);
    }

    printf("\nPipeline execution complete.\n");
    return 0;
}
