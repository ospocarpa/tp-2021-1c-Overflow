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

void mostrar_consola();
bool leer_consola(void);
int obtener_cantidad_argumentos(char **tokens);
void parsear_mensaje(cod_operacion operacion, char **tokens);

#endif
