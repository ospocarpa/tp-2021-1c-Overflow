#ifndef SD_Posicion_H
#define SD_Posicion_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>

    Posicion* deserializar_I_Posicion(t_paquete* paquete);
    t_paquete* serializar_I_Posicion(Posicion* input);

#endif