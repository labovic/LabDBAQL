//
// Created by stele on 25/03/23.
//

#include "server.h"
#include "transport/server_transport.h"

#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define SA struct sockaddr

int main(int argc, char * argv[]) {
    if(argc != 3){
        printf("invalid number of argument\n need 2, but you have %d\n", argc);
        for(int i=0; i<argc; i++){
            printf("%s\n", argv[i]);
        }
        return 100;
    }
    FILE *f = open_database(argv[2]);
    database* db = get_database(f);

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if ((bind(sockfd, (SA *) &servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    } else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    } else
        printf("Server listening..\n");
    len = sizeof(cli);

    connfd = accept(sockfd, (SA *) &cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    } else
        printf("server accept the client...\n");


    server_communicate(connfd, db, f);


    free(db->blk);
    free(db);
    fclose(f);

    // Socket must be closed at the end of usage
    close(sockfd);
}