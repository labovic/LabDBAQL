//
// Created by stele on 25/03/23.
//

#ifndef CLIENT_SERVER_CLIENT_TRANSPORT_H
#define CLIENT_SERVER_CLIENT_TRANSPORT_H

#include "ast.h"
#include "../aql/aql.h"
#include <jansson.h>
#include <unistd.h>
#define MAX 1024

enum query_return_value {OK, ARRAY};

json_t* query_to_json(query* q);

void client_communicate(int sockfd);

#endif //CLIENT_SERVER_CLIENT_TRANSPORT_H
