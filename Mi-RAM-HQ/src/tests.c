#include "tests.h"

void validar_sd_iniciar_patota();
void validar_sd_expulsar_tripulante();
void validar_sd_listar_tripulante();
void validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram();

int run_tests(){
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite",NULL,NULL);

    CU_add_test(tests, "Valido serializacion y deserializacion iniciar patota", validar_sd_iniciar_patota);
    CU_add_test(tests, "Valido serializacion y deserializacion de expulsar tripulante", validar_sd_expulsar_tripulante);
    //CU_add_test(tests, "Valido serializacion y deserializacion listar tripulante", validar_sd_listar_tripulante);
    CU_add_test(tests, "Valido serializacion y deserializacion msj discordiador", validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram);
    
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

    //free((*(*paquete).buffer).stream);
    free(paquete->buffer);
    free(paquete);
    free(data_res.path_tareas);
    free(data_res.posiciones);
}

void validar_sd_expulsar_tripulante(){

    t_expulsar_tripulante data_input;
    t_expulsar_tripulante data_res;
    t_paquete * paquete ;

    data_input.id_tripulante = 2 ;

    paquete = serializar_expulsar_tripulante(data_input);
    data_res = deserializar_expulsar_tripulante(paquete);
    CU_ASSERT_EQUAL(data_input.id_tripulante, data_res.id_tripulante);

    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);

}
 

void validar_sd_listar_tripulante(){

    t_listar_tripulantes data_input;
    t_listar_tripulantes data_res;
    t_paquete * paquete;

    t_tripulante * t1 = malloc(sizeof(t_tripulante));
    t_tripulante * t2 = malloc(sizeof(t_tripulante));

    t1->patota_id = 1;
    t1->tripulante_id = 1;
    t1->posicion.posx = 0;
    t1->posicion.posy = 1;
    t1->status = NEW;

    t2->patota_id = 1;
    t2->tripulante_id = 2;
    t2->posicion.posx = 1;
    t2->posicion.posy = 1;
    t2->status = NEW;

    data_input.cant_tripulantes = 2;
    data_input.tripulantes = list_create();

    list_add(data_input.tripulantes, t1);
    list_add(data_input.tripulantes, t2);

    paquete = serializar_listar_tripulantes(data_input);

    data_res = deserializar_listar_tripulantes(paquete);

    t_tripulante * tripulante1 = list_get(data_res.tripulantes, 0);
    t_tripulante * tripulante2 = list_get(data_res.tripulantes, 1);

    printf("Patota id: %d", tripulante1->patota_id);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);
    CU_ASSERT_EQUAL(t1->patota_id, tripulante1->patota_id);
    CU_ASSERT_EQUAL(t1->tripulante_id, tripulante1->tripulante_id);
    CU_ASSERT_EQUAL(t1->posicion.posx, tripulante1->posicion.posx);
    CU_ASSERT_EQUAL(t1->posicion.posy, tripulante1->posicion.posy);
    CU_ASSERT_EQUAL(t1->status, tripulante1->status);
    
    free(paquete->buffer);
    free(paquete);

    free(t1);
    free(t2);

    // list_remove_and_destroy_element(data_res.tripulantes, 0, free);
    // list_remove_and_destroy_element(data_res.tripulantes, 1, free);
}
  
void validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram(){

    t_short_info_tripulante tripulante_input;
    int tripulante_id_input;
    int patota_id_input;
    int tripulante_id_res;
    int patota_id_res;
    t_paquete * paquete;

    patota_id_input = 1;
    tripulante_id_input = 2;

    paquete = ser_cod_informar_tarea_tripulante(patota_id_input, tripulante_id_input);
    des_cod_informar_tarea_tripulante(paquete, &patota_id_res, &tripulante_id_res);

    CU_ASSERT_EQUAL(patota_id_input, patota_id_res);
    CU_ASSERT_EQUAL(tripulante_id_input, tripulante_id_res);

    free(paquete->buffer);
    free(paquete);

}
