#ifndef PAGINACION
#define PAGINACION

#include <stdio.h>
#include <stdlib.h>
#include <commons/bitarray.h>
#include <commons/string.h> 
#include <commons/collections/list.h>

void iniciar_tabla_paginacion();
int get_primer_bit_disponible(t_bitarray* bitarray);

#endif