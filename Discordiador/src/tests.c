#include "tests.h"

int run_tests()
{
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite", NULL, NULL);

    CU_add_test(tests, "Verificar serializacion y deserializacion", verificarTarea);

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
/*void suma_proceso1(){
    CU_ASSERT_EQUAL(2+2, 4);
}*/

//
