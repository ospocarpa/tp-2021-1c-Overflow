
#ifndef CONSOLA_H
#define CONSOLA_H

#include <stdio.h>
#include <stdbool.h>
#include <commons/log.h>
#include <TAD.h>
#include <sd_posicion.h>
#include <consola.h>
#include <tad_discordiador.h>
#include <commons/string.h>
#include <ctype.h>
#include "tripulantes.h"
#include "../include/shared_utils.h"
#include "log_utils.h"
#include "sd_iniciar_patota.h"

extern int cantidadTripulantes;
extern int cantidadDePatotas;
void mostrar_consola();
bool leer_consola(void);
int obtener_cantidad_argumentos(char **tokens);
void parsear_mensaje(op_code operacion, char **tokens);
int guardar_contenido_archivo(const char *, char **);

int existe_archivo(const char *); // en la shared ?

#endif
