
#ifndef CONSOLA_H
#define CONSOLA_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <TAD.h>
#include <sd_posicion.h>
#include <tad_discordiador.h>
#include <commons/string.h>
#include <ctype.h>
#include "tripulantes.h"
#include "../include/shared_utils.h"
#include "log_utils.h"
#include "sd_iniciar_patota.h"
#include "../include/socket_client.h"
#include "config_utils.h"
extern int conexion_mi_ram;

extern t_config_discordiador *config;
void mostrar_consola();
bool leer_consola(void);
void detener();
void activar_planificacion();
void planificar();
int obtener_cantidad_argumentos(char **tokens);
void parsear_mensaje(op_code operacion, char **tokens);
int guardar_contenido_archivo(const char *, char **);

int existe_archivo(const char *); // en la shared ?

#endif
