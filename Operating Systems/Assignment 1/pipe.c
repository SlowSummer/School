#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {
	int fd[2];
	pid_t pid;

	//create pipe
	pipe(fd);

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) //child
	{
		close(fd[1]); //close write end of fd
		dup2(fd[0], STDIN_FILENO); //dup read to pipe
		close(fd[0]);

		execlp("./sort", "sort", NULL);
		
	}
	else //parent
	{
		close(fd[0]); //close read end of fd
		dup2(fd[1], STDOUT_FILENO); //dup write to pipe
		close(fd[1]);	

		execlp("./pre", "pre", NULL);
		
		wait(NULL); //wait for child to finish
	}


	return 0;
}