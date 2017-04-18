//
//  main.cpp
//  homework-3
//
//  Created by Illya Starikov and Zachary Wileman on 12/04/2017
//  Copyright 2017. Illya Starikov. All rights reserved.
//

#include <iostream>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

const auto PORT = 9000;
const auto MAX_HOSTNAME = 512;

int main(int argc, char *argv[]) {
    struct sockaddr_in serverSocketInfo;
    struct hostent* hostNamePointer;

    int socketHandle, socketConnection;
    char systemHost[MAX_HOSTNAME + 1]; // For C-APIS


    bzero(&serverSocketInfo, sizeof(sockaddr_in));  // Clear structure memory

    // Use Internet IPV4 family (AF_INET), SOCKSTRAM since we're doing TCP, and IP
    // See man page for this
    if((socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }

    gethostname(systemHost, MAX_HOSTNAME);  // Get the name of this computer we are running on
    if((hostNamePointer = gethostbyname(systemHost)) == NULL) {
        std::cerr << "System Hostname Misconfigured\n";
        exit(EXIT_FAILURE);
    }

    // Load system information into socket data structures
    serverSocketInfo.sin_family = AF_INET;

    // Use any address available to the system.
    // A socket client will specify the server address to connect to.
    serverSocketInfo.sin_addr.s_addr = htonl(INADDR_ANY); // Translate long integer to network byte order.
    serverSocketInfo.sin_port = htons(PORT);        // Set port number

    // Bind the socket to a local socket address, act as a server
    if(bind(socketHandle, (struct sockaddr *) &serverSocketInfo, sizeof(struct sockaddr_in)) < 0) {
        close(socketHandle);
        std::cerr << "Couldn't bind to local address.\n";
        exit(EXIT_FAILURE);
    }

    listen(socketHandle, 10); // Set maximum length of the queue of pending connections for the listening socket
    // 10 is pretty much arbitrary.


}
