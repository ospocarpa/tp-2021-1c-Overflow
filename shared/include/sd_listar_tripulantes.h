#ifndef SD_LISTAR_TRIPULANTES_H
#define SD_LISTAR_TRIPULANTES_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>


t_paquete* serializar_listar_tripulantes(t_listar_tripulantes data_buffer);
t_listar_tripulantes deserializar_listar_tripulantes(t_paquete* paquete);


#endif  