#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <string.h>
#include <log_utils.h>
#include <server_utils.h>

void server_mongo_store_iniciar(char *puerto, char *ip, t_log *log);

#endif