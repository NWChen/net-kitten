#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void die(char *s);

int main(int argc, char **argv) {

    // input validation
    if(argc != 3) {
		fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
		exit(1);
	}        
	if(atoi(argv[2]) < 256 || atoi(argv[2]) > 65536)
		die("port is invalid or in use.");

	// delegate client and server
	pid_t pid = fork();
	if(pid == 0) {
		execl("client", "./client", argv[1], argv[2], NULL);
	} else if(pid > 0) {
		if((waitpid(pid, NULL, WNOHANG)) > 0) {
			fprintf(stderr, "%s\n", "initiating server because client died ):");
			execl("server", "./server", argv[1], argv[2], NULL);
		}
	} else
		die("fork() failed");

	return 0;	
}
