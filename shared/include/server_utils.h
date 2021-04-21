#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include "TAD.h"

    void* recibir_buffer(int*, int,t_log*);

    int iniciar_servidor(char*,char*,t_log*);
    int esperar_cliente(int,t_log*);
    t_list* recibir_paquete(int,t_log*);
    t_paquete* recibir_mensaje(int socket_cliente);
    int recibir_operacion(int,t_log*);

    char* test(){
        return "Hola mundo";
    }

#endif