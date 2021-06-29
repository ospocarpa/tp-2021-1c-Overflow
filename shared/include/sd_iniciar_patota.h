#ifndef SD_INICIAR_PATOTA_H
#define SD_INICIAR_PATOTA_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <TAD.h>
#include <commons/string.h>
#include <commons/collections/list.h>

/* ******* DISCORDIADOR ******* */
t_package ser_cod_iniciar_patota(t_iniciar_patota data_buffer);
bool des_res_iniciar_patota(t_package paquete);

/* ******* MI RAM HQ ******* */
t_iniciar_patota des_cod_iniciar_patota(t_package paquete);
t_package ser_res_iniciar_patota(bool data);
t_list * convertir_a_list_psiciones(char * posiciones_string);

#endif