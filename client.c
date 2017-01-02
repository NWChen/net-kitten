#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "receive.h"

#define BUFSIZE 1024

void die(char *s);

int main(int argc, char *argv[]) {

        /*
         * === SOCKET SETUP ===
         */
        int sock;                               // Socket descriptor
        struct sockaddr_in serverAddr;          // Server address
        unsigned short serverPort;              // Server port
        char *serverIP;                         // Server IP
        //char message[BUFSIZE];                  // String to send to server
        char buffer[BUFSIZE];                   // Buffer to receive response

        serverIP = argv[1];
        serverPort = atoi(argv[2]);

        // create TCP socket
        if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
                die("socket() failed");

        // construct server address structure
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family      = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(serverIP); 
        serverAddr.sin_port        = htons(serverPort);

        // establish connection to server
        if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
                die("connect() failed");
        /*
         * === SOCKET SETUP ===
         */

        /*
         * === RECEIVE AND SEND ===
         */
        pid_t pid = fork();
        while(1) {
                if(pid == 0) { 							// child process
                        receive(sock);
                } else if(pid > 0) {					// parent process
                        memset(buffer, 0, BUFSIZE);
                        fgets(buffer, BUFSIZE-1, stdin);	// null terminator should be automatically appended by fgets()
                        send(sock, buffer, BUFSIZE, 0);
                } else
                        die("fork() failed");
        }
        /*
         * === RECEIVE AND SEND ===
         */

        // parent terminates - watch out for orphaned child?
        close(sock);
        return 0;
}