#ifndef UTIL_MONGOSTORE_H
#define UTIL_MONGOSTORE_H

#include <global.h>
#include <pthread.h>
#include <string.h>
#include "log_utils.h"
#include "server_utils.h"
#include <stdlib.h>
#include "sd_create_file.h"
#include "sd_get_file.h"
#include "sd_update_bitacora.h"
#include "sd_operation_file_recurso.h"
#include "sd_fcsk.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int get_length_parts(char* filename);                           //Obtiene la cantidad de partes del archivos a partir del puntos
t_list* get_archivos_de_directorio(char* directorio);
/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);

#endif