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

/* ******* MI RAM HQ ******* */
t_package ser_res_listar_tripulantes(t_listar_tripulantes data_buffer);

/* ******* DISCORDIADOR ******* */
t_listar_tripulantes des_res_listar_tripulantes(t_package paquete);


#endif  