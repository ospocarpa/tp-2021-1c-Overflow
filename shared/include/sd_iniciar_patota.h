#ifndef SD_INICIAR_PATOTA_H
#define SD_INICIAR_PATOTA_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <TAD.h>
#include <commons/string.h>
#include <commons/collections/list.h>

t_paquete * serializar_iniciar_patota(t_iniciar_patota data_buffer);
t_iniciar_patota deserializar_iniciar_patota(t_paquete * paquete);
t_list * convertir_a_list_psiciones(char * posiciones_string);

#endif