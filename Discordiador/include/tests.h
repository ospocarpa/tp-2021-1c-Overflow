#ifndef TESTS_H
#define TESTS_H
#include <CUnit/Basic.h>
#include <TAD.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/sd_tarea.h"
#include "../include/sd_sabotaje.h"
#include "../include/tad_discordiador.h"
//
//#include "tripulantes.h"

int run_tests();
void verificarTarea();
void verificarSabotaje();
void verificar_buscar_el_mas_cercano();

extern t_list *lista_BLOCKEMERGENCIA;

#endif