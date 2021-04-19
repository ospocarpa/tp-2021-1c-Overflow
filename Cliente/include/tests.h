#ifndef TESTS_H
#define TESTS_H
#include <CUnit/Basic.h>
#include "serializador.h"
#include "desearilizador.h"
#include "seleccionar_restaurante.h"
#include "consultar_restaurantes.h"
#include "tests_consultar_restaurante.h"
#include "tests_guardar_pedido.h"
#include "tests_obtener_restaurante.h"
#include "tests_crear_pedido.h"
#include "tests_anadir_plato.h"
#include "tests_obtener_pedido.h"
#include "tests_plato_listo.h"
#include "tests_guardar_plato.h"
#include "tests_terminar_pedido.h"
#include "tests_consultar_pedido.h"
#include "tests_serializador_des_restaurante.h"

int run_tests();
void suma_proceso1();
void test_serializar_respuesta_bool();
void test_serializar_seleccionar_restaurante();

#endif