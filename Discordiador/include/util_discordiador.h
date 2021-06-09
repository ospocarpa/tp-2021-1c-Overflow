#ifndef UTIL_DISCORDIADOR_H
#define UTIL_DISCORDIADOR_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <TAD.h>
#include <sd_posicion.h>
#include <consola.h>
#include <tad_discordiador.h>
#include <commons/string.h>
#include <ctype.h>
#include <consola.h>
#include <pthread.h>
#include <commons/process.h>

    Patota* map_to_patota(t_iniciar_patota);
    void mostrar_t_patota(Patota* patota);
    void mostrar_datos_patota(t_iniciar_patota*);
    char* get_status_string(status_tripulante);
    t_list* get_tripulantes_all();

#endif
