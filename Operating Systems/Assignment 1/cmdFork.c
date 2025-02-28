#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int status;

    
    pid = fork();

    if (pid == 0) //child
    {
        //print parent and current ID
        printf("Parent ID: %d\n", getppid());
        printf("Child process ID: %d\n", getpid());
        
        execvp(argv[1], &argv[1]); //execut the command

    }
    else //parent
    {
        waitpid(pid, &status, 0);
    }


    return 0;
}