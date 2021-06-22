#ifndef SD_EXPULSAR_TRIPULANTE_H
#define SD_EXPULSAR_TRIPULANTE_H

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/config.h>
#include<string.h>
#include<TAD.h>
#include<sd_posicion.h>

/* ******* DISCORDIADOR ******* */
t_package ser_cod_expulsar_tripulante(t_expulsar_tripulante data_buffer);

/* ******* MI RAM HQ ******* */
t_expulsar_tripulante des_cod_expulsar_tripulante(t_package paquete);


#endif  