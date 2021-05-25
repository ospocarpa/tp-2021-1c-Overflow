#include "tests.h"

static void validar_sd_iniciar_patota();

int run_tests(){
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite",NULL,NULL);

 
    CU_add_test(tests,"Suma2+2", suma);
    CU_add_test(tests, "Valido serializacion y deserializacion iniciar patota", validar_sd_iniciar_patota);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

void suma(){
    CU_ASSERT_EQUAL(2+2, 4);
}

void validar_sd_iniciar_patota()
{
    t_iniciar_patota data_input;
    t_iniciar_patota data_res;
    t_paquete * paquete = malloc(sizeof(t_paquete));

    data_input.cant_tripulantes = 2;
    data_input.path_tareas = "/home/utnso/tareas/tareas.txt";
    data_input.long_path_tareas = strlen("/home/utnso/tareas/tareas.txt");
    data_input.posiciones = "0|3 0|0";
    data_input.long_posicion= strlen("0|3 0|0");

    paquete = serializar_iniciar_patota(data_input);

    data_res = deserializar_iniciar_patota(paquete);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);

    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);
}


 
  

  

