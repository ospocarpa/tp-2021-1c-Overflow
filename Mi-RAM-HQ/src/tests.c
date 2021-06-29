
#include "../include/tests.h"
void validar_sd_iniciar_patota();
void validar_sd_expulsar_tripulante();
void validar_sd_listar_tripulante();
void validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram();
void validar_sd_informar_tarea_tripulante_msj_mi_ram_a_discordiador();
void validar_sd_informar_posicion_msj_disc_mi_ram();
void validar_sd_informar_posicion_msj_mi_ram_disc();
void validar_sd_informar_estado_msj_discordiador_a_mi_ram();
void validar_sd_res_iniciar_patota();

int run_tests()
{
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite", NULL, NULL);

    CU_add_test(tests, "Valido serializacion y deserializacion iniciar patota", validar_sd_iniciar_patota);
    CU_add_test(tests, "Valido serializacion y deserializacion de expulsar tripulante", validar_sd_expulsar_tripulante);
    CU_add_test(tests, "Valido serializacion y deserializacion listar tripulante", validar_sd_listar_tripulante);
    CU_add_test(tests, "Valido informar tarea msj discordiador a mi ram", validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram);
    CU_add_test(tests, "Valido informar tarea msj mi ram a discordiador", validar_sd_informar_tarea_tripulante_msj_mi_ram_a_discordiador);
    CU_add_test(tests, "Valido informar tarea msj discordiador a mi ram", validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram);
    CU_add_test(tests, "Valido informar posicion msj mi ram a discordiador", validar_sd_informar_posicion_msj_disc_mi_ram);
    CU_add_test(tests, "Valido informar posicion msj discordiador a mi ram", validar_sd_informar_posicion_msj_mi_ram_disc);
    CU_add_test(tests, "Valido informar estado msj discordiador a mi ram", validar_sd_informar_estado_msj_discordiador_a_mi_ram);
    CU_add_test(tests, "Valido res de iniciar patota msj mi ram a discordialor", validar_sd_res_iniciar_patota);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

void validar_sd_iniciar_patota()
{
    t_iniciar_patota data_input;
    t_iniciar_patota data_res;
    t_package paquete;

    data_input.cant_tripulantes = 2;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "0|3 0|0";
    data_input.long_posicion = strlen("0|3 0|0");

    paquete = ser_cod_iniciar_patota(data_input);

    data_res = des_cod_iniciar_patota(paquete);

    printf("path tareas: %d \n", data_res.long_posicion);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);
    CU_ASSERT_EQUAL(data_input.long_tareas, data_res.long_tareas);
    CU_ASSERT_STRING_EQUAL(data_input.tareas, data_res.tareas);
    CU_ASSERT_EQUAL(data_input.long_posicion, data_res.long_posicion);
    CU_ASSERT_STRING_EQUAL(data_input.posiciones, data_res.posiciones);

    free(paquete.buffer);
    free(data_res.tareas);
    free(data_res.posiciones);
}

void validar_sd_expulsar_tripulante()
{

    t_expulsar_tripulante data_input;
    t_expulsar_tripulante data_res;
    t_package paquete ;

    data_input.id_tripulante = 2;

    paquete = ser_cod_expulsar_tripulante(data_input);
    data_res = des_cod_expulsar_tripulante(paquete);
    CU_ASSERT_EQUAL(data_input.id_tripulante, data_res.id_tripulante);

    free(paquete.buffer);
}

void validar_sd_listar_tripulante()
{

    t_listar_tripulantes data_input;
    t_listar_tripulantes data_res;
    t_package paquete;

    t_tripulante *t1 = malloc(sizeof(t_tripulante));
    t_tripulante *t2 = malloc(sizeof(t_tripulante));

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

    paquete = ser_res_listar_tripulantes(data_input);

    data_res = des_res_listar_tripulantes(paquete);

    t_tripulante *tripulante1 = list_get(data_res.tripulantes, 0);
    t_tripulante *tripulante2 = list_get(data_res.tripulantes, 1);

    printf("Patota id: %d \n", tripulante1->patota_id);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);
    CU_ASSERT_EQUAL(t1->patota_id, tripulante1->patota_id);
    CU_ASSERT_EQUAL(t1->tripulante_id, tripulante1->tripulante_id);
    CU_ASSERT_EQUAL(t1->posicion.posx, tripulante1->posicion.posx);
    CU_ASSERT_EQUAL(t1->posicion.posy, tripulante1->posicion.posy);
    CU_ASSERT_EQUAL(t1->status, tripulante1->status);

    CU_ASSERT_EQUAL(1, tripulante2->patota_id);
    CU_ASSERT_EQUAL(2, tripulante2->tripulante_id);
    CU_ASSERT_EQUAL(t2->posicion.posx, tripulante2->posicion.posx);
    CU_ASSERT_EQUAL(t2->posicion.posy, tripulante2->posicion.posy);
    CU_ASSERT_EQUAL(t2->status, tripulante2->status);

    //libero memoria

    void tripulante_destroy(t_tripulante * un_tripulante) {
        free(un_tripulante);
    }
    
    list_destroy_and_destroy_elements(data_input.tripulantes, tripulante_destroy);
    list_destroy_and_destroy_elements(data_res.tripulantes, tripulante_destroy);
    free(paquete.buffer);
    
}

void validar_sd_informar_tarea_tripulante_msj_discordiador_a_mi_ram(){

    t_short_info_tripulante tripulante;
    t_short_info_tripulante tripulante_res;
    uint32_t tripulante_id_input;
    uint32_t patota_id_input;
    uint32_t tripulante_id_res;
    uint32_t patota_id_res;
    t_package paquete;

    tripulante.patota_id = 1;
    tripulante.tripulante_id = 2;

    paquete = ser_cod_informar_tarea_tripulante(tripulante);
    tripulante_res = des_cod_informar_tarea_tripulante(paquete);

    CU_ASSERT_EQUAL(tripulante.patota_id, tripulante_res.patota_id);
    CU_ASSERT_EQUAL(tripulante.tripulante_id, tripulante_res.tripulante_id);

    free(paquete.buffer);
}

void validar_sd_informar_tarea_tripulante_msj_mi_ram_a_discordiador(){
    t_info_tarea tarea;
    Posicion pos;
    t_package paquete;
    t_info_tarea tarea_res;

    pos.posx = 1;
    pos.posy = 0;

    tarea.tarea = GENERAR_OXIGENO;
    tarea.posicion = pos;
    tarea.parametro = 3;
    tarea.tiempo = 4;

    paquete = ser_res_informar_tarea_tripulante(tarea);
    tarea_res = des_res_informacion_tarea_tripulante(paquete);

    CU_ASSERT_EQUAL(GENERAR_OXIGENO, tarea_res.tarea);
    CU_ASSERT_EQUAL(tarea.parametro, tarea_res.parametro);
    CU_ASSERT_EQUAL(tarea.posicion.posx, tarea_res.posicion.posx);
    CU_ASSERT_EQUAL(tarea.posicion.posy, tarea_res.posicion.posy);
    CU_ASSERT_EQUAL(tarea.tiempo, tarea_res.tiempo);

    free(paquete.buffer);
}

void validar_sd_informar_posicion_msj_disc_mi_ram(){
    t_short_info_tripulante tripulante;
    t_short_info_tripulante tripulante_res;
    uint32_t tripulante_id_input;
    uint32_t patota_id_input;
    uint32_t tripulante_id_res;     
    uint32_t patota_id_res;
    t_package paquete;

    tripulante.patota_id = 1;
    tripulante.tripulante_id = 2;

    paquete = ser_cod_informar_posicion_tripulante(tripulante);
    tripulante_res = des_cod_informar_posicion_tripulante(paquete);

    CU_ASSERT_EQUAL(tripulante.patota_id, tripulante_res.patota_id);
    CU_ASSERT_EQUAL(tripulante.tripulante_id, tripulante_res.tripulante_id);

    free(paquete.buffer);
}

void validar_sd_informar_posicion_msj_mi_ram_disc(){
    t_informar_posicion_tripulante data;
    Posicion pos;
    t_package paquete;
    t_informar_posicion_tripulante data_res;

    pos.posx = 1;
    pos.posy = 0;

    data.patota_id=1;
    data.tripulante_id=2;
    data.posicion = pos;

    paquete = ser_res_informar_posicion_tripulante(data);
    data_res = des_res_informar_posicion_tripulante(paquete);

    CU_ASSERT_EQUAL(data.patota_id, data_res.patota_id);
    CU_ASSERT_EQUAL(data.tripulante_id, data_res.tripulante_id);

    CU_ASSERT_EQUAL(data.posicion.posx, data_res.posicion.posx);
    CU_ASSERT_EQUAL(data.posicion.posy, data_res.posicion.posy);
    

    free(paquete.buffer);
}

void validar_sd_informar_estado_msj_discordiador_a_mi_ram(){
    t_estado_tripulante tripulante;
    t_estado_tripulante tripulante_res;
    t_package paquete;

    tripulante.status = READY;
    tripulante.patota_id = 1;
    tripulante.tripulante_id = 2;

    paquete = ser_cod_informar_estado(tripulante);
    tripulante_res = des_cod_informar_estado(paquete);

    CU_ASSERT_EQUAL(tripulante.patota_id, tripulante_res.patota_id);
    CU_ASSERT_EQUAL(tripulante.tripulante_id, tripulante_res.tripulante_id);
    CU_ASSERT_EQUAL(tripulante.status, tripulante_res.status);

    free(paquete.buffer);
}

void validar_sd_res_iniciar_patota(){
    bool validacion = true;
    bool validacion_res;
    t_package paquete;

    paquete = ser_res_iniciar_patota(validacion);
    validacion_res = des_res_iniciar_patota(paquete);

    CU_ASSERT_TRUE(validacion_res);

    free(paquete.buffer);
}