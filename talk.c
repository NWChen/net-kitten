#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void die(char *s);
int handleClient(char *serverIP, unsigned short serverPort);
int handleServer(unsigned short serverPort);

int main(int argc, char **argv) {

    // input validation
    if(argc != 3) {
		fprintf(stderr, "usage: %s <hostname> <port>\n", argv[0]);
		exit(1);
	}        
	if(atoi(argv[2]) < 256 || atoi(argv[2]) > 65536)
		die("port is invalid or in use.");

	char *serverIP = argv[1];
	unsigned short serverPort = atoi(argv[2]);

	// delegate client and server
	if(handleClient(serverIP, serverPort) == 0) {
		//fprintf(stderr, "%s\n", "starting server");
		handleServer(serverPort);
	}

	return 0;	
}
