#include "tests.h"

void validar_sd_iniciar_patota();
void validar_sd_expulsar_tripulante();

int run_tests(){
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite",NULL,NULL);

    CU_add_test(tests, "Valido serializacion y deserializacion iniciar patota", validar_sd_iniciar_patota);
    CU_add_test(tests, "Valido serializacion y deserializacion de expulsar tripulante", validar_sd_expulsar_tripulante);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

void validar_sd_iniciar_patota()
{
    t_iniciar_patota data_input;
    t_iniciar_patota data_res;
    t_paquete * paquete;

    data_input.cant_tripulantes = 2;
    data_input.path_tareas = "/home/utnso/tareas/tareas.txt";
    data_input.long_path_tareas = strlen("/home/utnso/tareas/tareas.txt");
    data_input.posiciones = "0|3 0|0";
    data_input.long_posicion= strlen("0|3 0|0");

    paquete = serializar_iniciar_patota(data_input);

    data_res = deserializar_iniciar_patota(paquete);

    printf("path tareas: %d \n", data_res.long_posicion);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);
    CU_ASSERT_EQUAL(data_input.long_path_tareas, data_res.long_path_tareas);
    CU_ASSERT_STRING_EQUAL(data_input.path_tareas, data_res.path_tareas);
    CU_ASSERT_EQUAL(data_input.long_posicion, data_res.long_posicion);
    CU_ASSERT_STRING_EQUAL(data_input.posiciones, data_res.posiciones);

    //free(paquete->buffer.stream);
    free(paquete->buffer);
    free(paquete);
    free(data_res.path_tareas);
    free(data_res.posiciones);
}

void validar_sd_expulsar_tripulante(){

    t_expulsar_tripulante data_input;
    t_expulsar_tripulante data_res;
    t_paquete * paquete ;

    data_input.cant_tripulantes = 2 ;

    paquete = serializar_expulsar_tripulante(data_input);
    data_res = deserializar_expulsar_tripulante(paquete);
    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);

    free(paquete->buffer);
    free(paquete);
}
 
  

  

