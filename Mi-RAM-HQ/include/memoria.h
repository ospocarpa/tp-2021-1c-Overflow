#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include "tad_mi_ram_hq.h"
#include "log_utils.h"

void iniciar_memoria_principal(int tam_memoria);
void liberar_memoria_principal();

#endif