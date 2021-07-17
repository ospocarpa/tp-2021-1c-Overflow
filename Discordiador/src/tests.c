#include "../include/tests.h"
int run_tests()
{
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite", NULL, NULL);

    CU_add_test(tests, "Verificar serializacion y deserializacion tarea", verificarTarea);
    CU_add_test(tests, "Verificar serializacion y deserializacion sabotaje", verificarSabotaje);
    CU_add_test(tests, "Verificar funcion buscar_el_mas_cercano(t_sabotaje) ", verificar_buscar_el_mas_cercano);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

void verificarTarea()
{
    Tarea *tarea = malloc(sizeof(Tarea));
    tarea->patota_id = 1;
    tarea->description = "test";
    tarea->description_length = strlen(tarea->description);
    tarea->parametros = "test 2";
    tarea->parametros_length = strlen(tarea->parametros);
    tarea->tiempo = 3;
    tarea->posicion = malloc(sizeof(Posicion));
    tarea->posicion->posx = 1;
    tarea->posicion->posy = 2;

    //mostrarTarea(tarea);

    t_paquete *paquete = serializar_I_TAREA(tarea);
    Tarea *tarea2 = deserializar_I_TAREA(paquete);
    /*printf("\n");
    mostrarTarea(tarea2);*/

    CU_ASSERT_EQUAL(tarea->patota_id, tarea2->patota_id);
    CU_ASSERT_STRING_EQUAL(tarea->description, tarea2->description);
    CU_ASSERT_STRING_EQUAL(tarea->parametros, tarea2->parametros);
    CU_ASSERT_EQUAL(tarea->tiempo, tarea2->tiempo);
    CU_ASSERT_EQUAL(tarea->posicion->posx, tarea2->posicion->posx);
    CU_ASSERT_EQUAL(tarea->posicion->posy, tarea2->posicion->posy);
}

void verificarSabotaje()
{
    t_sabotaje *sabotaje = malloc(sizeof(t_sabotaje));
    sabotaje->mensaje = "test";
    sabotaje->mensaje_length = strlen(sabotaje->mensaje);
    sabotaje->posicion = malloc(sizeof(Posicion));
    sabotaje->posicion->posx = 1;
    sabotaje->posicion->posy = 2;

    t_package paquete = serializar_I_SABOTAJE(sabotaje);
    t_sabotaje *sabotaje2 = deserializar_I_SABOTAJE(paquete);
    /*printf("\n");
    mostrarTarea(tarea2);*/

    CU_ASSERT_EQUAL(sabotaje->mensaje_length, sabotaje2->mensaje_length);
    CU_ASSERT_STRING_EQUAL(sabotaje->mensaje, sabotaje2->mensaje);
    CU_ASSERT_EQUAL(sabotaje->posicion->posx, sabotaje2->posicion->posx);
    CU_ASSERT_EQUAL(sabotaje->posicion->posy, sabotaje2->posicion->posy);
}
void verificar_buscar_el_mas_cercano()
{
    //defino un sabotaje pos 4-4
    t_sabotaje *sabotaje = malloc(sizeof(t_sabotaje));
    sabotaje->mensaje = "test";
    sabotaje->mensaje_length = strlen(sabotaje->mensaje);
    sabotaje->posicion = malloc(sizeof(Posicion));
    sabotaje->posicion->posx = 4;
    sabotaje->posicion->posy = 4;

    // iniciliazo la lista vacia

    lista_BLOCKEMERGENCIA = list_create();
    //defino 3 tripulantes :posiciones  1-1 ,2-2,3-3
    Tripulante *tripulante1 = malloc(sizeof(Tripulante));
    tripulante1->id = 1;
    tripulante1->posicion = malloc(sizeof(Posicion));
    tripulante1->posicion->posx = 1;
    tripulante1->posicion->posy = 1;
    list_add(lista_BLOCKEMERGENCIA, tripulante1);
    //
    Tripulante *tripulante2 = malloc(sizeof(Tripulante));
    tripulante2->id = 2;
    tripulante2->posicion = malloc(sizeof(Posicion));
    tripulante2->posicion->posx = 2;
    tripulante2->posicion->posy = 2;
    list_add(lista_BLOCKEMERGENCIA, tripulante2);
    //
    Tripulante *tripulante3 = malloc(sizeof(Tripulante));
    tripulante3->id = 3;
    tripulante3->posicion = malloc(sizeof(Posicion));
    tripulante3->posicion->posx = 3;
    tripulante3->posicion->posy = 3;
    list_add(lista_BLOCKEMERGENCIA, tripulante3);
    //
    Tripulante *tripulante_elegido = buscar_el_mas_cercano(sabotaje);
    CU_ASSERT_EQUAL(tripulante_elegido->id, tripulante3->id);
}

/*void suma_proceso1(){
    CU_ASSERT_EQUAL(2+2, 4);
}*/

//
