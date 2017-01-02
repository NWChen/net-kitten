#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSIZE 1024

void receive(int sockfd) {
	
	char buffer[BUFSIZE];		// buffer to output
	int recvByteLen = 1;

	while(recvByteLen > 0) {
		memset(buffer, 0, BUFSIZE);
		recvByteLen = recv(sockfd, buffer, sizeof(buffer), 0);
		fprintf(stderr, "%s", buffer);	// receive may already include newline
	}	

}
