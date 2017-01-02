#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "receive.h"

#define BUFSIZE 1024

void die(char *s);

int main(int argc, char *argv[]) {

        /*
         * SERVER SETUP
         */	
        int servSock;
        int clntSock;
        struct sockaddr_in servAddr;
        struct sockaddr_in clntAddr;
        unsigned short servPort;
        unsigned int clntLen;

        servPort = atoi(argv[2]);

        // create socket for incoming connections
        if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
                die("socket() failed");

        // construct local address structure
        memset(&servAddr, 0, sizeof(servAddr));
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(servPort);

        // bind to local address
        if(bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
                die("bind() failed");

        // listen for incoming connections
        if(listen(servSock, 5) < 0)
                die("listen() failed");

        // wait for a client to connect
        clntLen = sizeof(clntAddr);
        if((clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntLen)) < 0)
                die("accept() failed");
        /*
         * SERVER SETUP
         */

        /*        
         * RECEIVE AND SEND
         */
        char buffer[BUFSIZE];
        pid_t pid = fork();
        while(1) {
                if(pid == 0) {
                        receive(clntSock);
                } else if(pid > 0) {
                        memset(buffer, 0, BUFSIZE);
                        fgets(buffer, BUFSIZE-1, stdin);
                        send(clntSock, buffer, BUFSIZE, 0);
                } else
                        die("fork() failed");
        }
        /*
         * RECEIVE AND SEND
         */

        close(clntSock);
        close(servSock);
        return 0;
}
