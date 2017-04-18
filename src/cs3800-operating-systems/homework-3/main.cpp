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



int main(int argc, char *argv[]) {
    int socketHandle;

    // Use Internet IPV4 family (AF_INET), SOCKSTRAM since we're doing TCP, and IP
    // See man page for this
    if((socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }
}
