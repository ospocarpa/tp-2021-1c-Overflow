#ifndef TESTS_H
#define TESTS_H
#include <CUnit/Basic.h>
#include <TAD.h>
#include <string.h>
#include "sd_iniciar_patota.h"
#include "sd_expulsar_tripulante.h"
#include "sd_listar_tripulantes.h"
#include "sd_informar_tarea_tripulante.h"
#include "sd_informar_posicion_tripulante.h"
#include "sd_informar_estado.h"
#include "memoria.h"
#include "util_mi_ram.h"
//#include "tad_mi_ram_hq.h"
#include <commons/collections/list.h>
#include <commons/string.h>

int run_tests();

#endif