//
// Created by stele on 25/03/23.
//

#include "client.h"
#include "transport/client_transport.h"

#include <jansson.h>
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define SA struct sockaddr

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("invalid number of argument\n need 2, but you have %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        return 100;
    }

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    client_communicate(sockfd);

    close(sockfd);
}
