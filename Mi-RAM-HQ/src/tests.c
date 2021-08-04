
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
void validar_cargar_informacion_TCB_a_MP();
void validar_cargar_informacion_PCB_a_MP();
void validar_cargar_informacion_tareas_a_MP();
void validar_get_tarea();
void validar_get_tarea2();
void validar_get_posicion_STR();
void validar_iniciar_patota_segmentada();
void validar_expulsar_tripulante_segmentada();
void validar_informacion_de_patota_segmentacion();
void validar_actualizacion_tripulante();
void validar_informar_tarea();
void validar_compactacion();

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
    CU_add_test(tests, "Valido carga de informacion de PCB a MP", validar_cargar_informacion_PCB_a_MP);
    CU_add_test(tests, "Valido carga de informacion de TCB a MP", validar_cargar_informacion_TCB_a_MP);
    CU_add_test(tests, "Valido carga de informacion de TAREAS a MP", validar_cargar_informacion_tareas_a_MP);
    CU_add_test(tests, "Valido get tarea", validar_get_tarea);
    CU_add_test(tests, "Valido get tarea2", validar_get_tarea2);
    CU_add_test(tests, "Valido get posicion", validar_get_posicion_STR);
    CU_add_test(tests, "Iniciar patota segmentada", validar_iniciar_patota_segmentada);
    CU_add_test(tests, "Expulsar tripulante segmentada", validar_expulsar_tripulante_segmentada);
    CU_add_test(tests, "Valido el get tarea y get de un tcb de una patota", validar_informacion_de_patota_segmentacion);
    CU_add_test(tests, "Valido la actualización de un tripulante por segmentacion", validar_actualizacion_tripulante);
    CU_add_test(tests, "Valido actualización de tripulante más solicitud de su próxima tarea", validar_informar_tarea);
    CU_add_test(tests, "Valido compactacion", validar_compactacion);

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
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    paquete = ser_cod_iniciar_patota(data_input);

    data_res = des_cod_iniciar_patota(paquete);

    CU_ASSERT_EQUAL(data_input.cant_tripulantes, data_res.cant_tripulantes);
    CU_ASSERT_EQUAL(data_input.long_tareas, data_res.long_tareas);
    CU_ASSERT_STRING_EQUAL(data_input.tareas, data_res.tareas);
    CU_ASSERT_EQUAL(data_input.long_posicion, data_res.long_posicion);
    CU_ASSERT_STRING_EQUAL(data_input.posiciones, data_res.posiciones);
    CU_ASSERT_EQUAL(data_input.patota_id, data_res.patota_id);
    CU_ASSERT_EQUAL(data_input.id_primer_tripulante, data_res.id_primer_tripulante);

    free(paquete.buffer);
    free(data_res.tareas);
    free(data_res.posiciones);
}

void validar_sd_expulsar_tripulante()
{

    t_expulsar_tripulante data_input;
    t_expulsar_tripulante data_res;
    t_package paquete ;

    data_input.patota_id = 1;
    data_input.tripulante_id = 2;

    paquete = ser_cod_expulsar_tripulante(data_input);
    data_res = des_cod_expulsar_tripulante(paquete);
    CU_ASSERT_EQUAL(data_input.tripulante_id, data_res.tripulante_id);

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

// ---------------------------- Memoria .c ----------------------------------------

void validar_cargar_informacion_TCB_a_MP(){

    t_TCB tcb;
    t_TCB tcb_res;

    tcb.tid =0;
    tcb.estado ='a';
    tcb.posx =0;
    tcb.posy =0;
    tcb.prox_tarea= 0;
    tcb.puntero_pcb=1;

    iniciar_memoria_principal(1024);
    cargar_informacion_TCB_a_MP(tcb,0);
    tcb_res = leer_info_TCB(0);
    liberar_memoria_principal();

    CU_ASSERT_EQUAL(tcb.tid, tcb_res.tid);
    CU_ASSERT_EQUAL(tcb.estado, tcb_res.estado);
    CU_ASSERT_EQUAL(tcb.posx, tcb_res.posx);
    CU_ASSERT_EQUAL(tcb.posy, tcb_res.posy);
    CU_ASSERT_EQUAL(tcb.prox_tarea, tcb_res.prox_tarea);
    CU_ASSERT_EQUAL(tcb.puntero_pcb, tcb_res.puntero_pcb);

}


void validar_cargar_informacion_PCB_a_MP(){

    t_PCB pcb;
    t_PCB pcb_res;

    pcb.pid = 0;
    pcb.tareas=1;

    iniciar_memoria_principal(1024);

    cargar_informacion_PCB_a_MP(pcb,0);
    pcb_res = leer_info_PCB(0);
    liberar_memoria_principal();

    CU_ASSERT_EQUAL(pcb.pid, pcb_res.pid);
    CU_ASSERT_EQUAL(pcb.tareas, pcb_res.tareas);

}

void validar_cargar_informacion_tareas_a_MP(){

    char * tareas = "tarea 5; 1; 2; 7";
    char * tareas_res;

    iniciar_memoria_principal(1024);

    cargar_informacion_tareas_a_MP(tareas,0);
    tareas_res = leer_info_tareas(0,strlen(tareas));
    liberar_memoria_principal();

    
    CU_ASSERT_STRING_EQUAL(tareas, tareas_res);
    
    free(tareas_res);

}

void validar_get_tarea(){

    char * lista_tareas = "ARREGLAR_REACTOR;7;2;5\nGeneraroxigeno 12;4;5;6";
    t_info_tarea tarea;
    t_info_tarea tarea_res;
    tarea.tarea = OTRA_TAREA;
    tarea.parametro = 0;
    tarea.posicion.posx = 7;
    tarea.posicion.posy = 2;
    tarea.tiempo = 5;

    tarea_res = get_tarea(lista_tareas,1);

    
    CU_ASSERT_EQUAL(tarea.tarea, tarea_res.tarea);
    CU_ASSERT_EQUAL(tarea.parametro, tarea_res.parametro);
    CU_ASSERT_EQUAL(tarea.posicion.posx, tarea_res.posicion.posx);
    CU_ASSERT_EQUAL(tarea.posicion.posy, tarea_res.posicion.posy);
    CU_ASSERT_EQUAL(tarea.tiempo, tarea_res.tiempo);
}

void validar_get_tarea2(){

    char * lista_tareas = "ARREGLAR_REACTOR;7;2;5\nGENERAR_OXIGENO 12;4;5;6";
    t_info_tarea tarea;
    t_info_tarea tarea_res;
    tarea.tarea = GENERAR_OXIGENO;
    tarea.parametro = 12;
    tarea.posicion.posx = 4;
    tarea.posicion.posy = 5;
    tarea.tiempo = 6;

    tarea_res = get_tarea(lista_tareas,2);

    
    CU_ASSERT_EQUAL(tarea.tarea, tarea_res.tarea);

    CU_ASSERT_EQUAL(tarea.parametro, tarea_res.parametro);
    CU_ASSERT_EQUAL(tarea.posicion.posx, tarea_res.posicion.posx);
    CU_ASSERT_EQUAL(tarea.posicion.posy, tarea_res.posicion.posy);
    CU_ASSERT_EQUAL(tarea.tiempo, tarea_res.tiempo);
}

void validar_get_posicion_STR(){
    char * lista_posicion ="1|1,2|2,3|3";
    Posicion pos_in;
    Posicion pos_out ;
    pos_in.posx = 1;
    pos_in.posy = 1;
    pos_out = get_posicion_STR(lista_posicion,1);
    CU_ASSERT_EQUAL(pos_in.posx,pos_out.posx);
    CU_ASSERT_EQUAL(pos_in.posy,pos_out.posy);
}

void validar_iniciar_patota_segmentada(){

    t_iniciar_patota data_input;

    data_input.cant_tripulantes = 1;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "1|2";
    data_input.long_posicion = strlen("1|2");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    iniciar_memoria_principal(128);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(128);
    set_size_memoria(128);

    bool res = iniciar_patota_segmentacion(data_input);
    bool hay_memoria_libre = se_puede_escribir(48);//no se puede escribir porque solo hay 47 bytes libres en memoria
    int cant_tablas_segmemtos = cantidad_de_tablas_de_segmento_test();
    int cant_huecos = cantidad_huecos_test();
    t_tabla_segmentos * tabla = get_tabla_segmento_segun_indice_test(0);

    CU_ASSERT_TRUE(res);
    CU_ASSERT_FALSE(hay_memoria_libre);
    CU_ASSERT_EQUAL(cant_tablas_segmemtos, 1);
    CU_ASSERT_EQUAL(cant_huecos, 1);
    CU_ASSERT_EQUAL(list_size(tabla->segmentos), 3);

    liberar_tabla_huecos();
    liberar_memoria_principal();
    

    void tabla_destroy(t_segmento * seg){
        free(seg);
    }

    //list_destroy_and_destroy_elements(tabla, tabla_destroy);
    //free(tabla);

    //liberar_lista_de_tablas_segmentos();
}

void validar_expulsar_tripulante_segmentada(){
    t_iniciar_patota data_input;

    cfg_create("cfg/mi_ram_hq.config");

    data_input.cant_tripulantes = 1;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "1|2";
    data_input.long_posicion = strlen("1|2");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    t_expulsar_tripulante data;

    data.patota_id = 1;
    data.tripulante_id = 2;

    iniciar_memoria_principal(128);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(128);
    set_size_memoria(128);

    bool res = iniciar_patota_segmentacion(data_input);
    expulsar_tripulante(data);
    /*dump_segmentacion_pura();
    printf("Huecos: %d\n", list_size(tabla_hueco));
    for(int c=0; c<list_size(tabla_hueco); c++){
        t_hueco* hueco = list_get(tabla_hueco, c); 
        printf("Inicio: %d Tamaño: %d\n", hueco->base, hueco->desplazamiento);
    }*/

    t_tabla_segmentos * tabla = get_tabla_segmento_segun_indice_test(0);

    int cant_seg = list_size(tabla->segmentos);
    CU_ASSERT_EQUAL(cant_seg, 2);

    liberar_tabla_huecos();
    liberar_memoria_principal();
    
    void tabla_destroy(t_segmento * seg){
        free(seg);
    }

    //list_destroy_and_destroy_elements(tabla, tabla_destroy);
    //free(tabla);

    //liberar_lista_de_tablas_segmentos();
}

void validar_informacion_de_patota_segmentacion(){
    t_iniciar_patota data_input;

    data_input.cant_tripulantes = 1;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "";
    data_input.long_posicion = strlen("");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    iniciar_memoria_principal(128);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(128);
    set_size_memoria(128);

    bool res = iniciar_patota_segmentacion(data_input);
    bool hay_memoria_libre = se_puede_escribir(48);//no se puede escribir porque solo hay 47 bytes libres en memoria
    
    char* tarea = get_tareas(data_input.patota_id);
    //printf("\nTarea: %s\n", tarea);
    CU_ASSERT_STRING_EQUAL(data_input.tareas, tarea);

    t_TCB tcb_encontrado = get_TCB_segmentacion_pura(data_input.patota_id, 2);
    CU_ASSERT_EQUAL(tcb_encontrado.tid, 2);
    CU_ASSERT_EQUAL(tcb_encontrado.estado, 'N');
    CU_ASSERT_EQUAL(tcb_encontrado.posx, 0);
    CU_ASSERT_EQUAL(tcb_encontrado.posy, 0);
    CU_ASSERT_EQUAL(tcb_encontrado.prox_tarea, 1);
    CU_ASSERT_EQUAL(tcb_encontrado.puntero_pcb, 9);

    //dump_segmentacion_pura();
    liberar_tabla_huecos();
    liberar_memoria_principal();
    

    void tabla_destroy(t_segmento * seg){
        free(seg);
    }
}

void validar_actualizacion_tripulante(){
    t_iniciar_patota data_input;

    data_input.cant_tripulantes = 1;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "1|2";
    data_input.long_posicion = strlen("1|2");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    iniciar_memoria_principal(128);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(128);
    set_size_memoria(128);

    bool res = iniciar_patota_segmentacion(data_input);
    bool hay_memoria_libre = se_puede_escribir(48);//no se puede escribir porque solo hay 47 bytes libres en memoria
    
    char* tarea = get_tareas(data_input.patota_id);
    t_TCB tcb_encontrado = get_TCB_segmentacion_pura(data_input.patota_id, 2);
    tcb_encontrado.estado = 'A';
    tcb_encontrado.posy = 1;
    tcb_encontrado.posx = 10;
    set_tripulante_por_segmentacion(tcb_encontrado, data_input.patota_id);
    t_TCB tcb_actualizado = get_TCB_segmentacion_pura(data_input.patota_id, 2);

    CU_ASSERT_EQUAL(tcb_actualizado.tid, 2);
    CU_ASSERT_EQUAL(tcb_encontrado.estado, 'A');
    CU_ASSERT_EQUAL(tcb_encontrado.posx, 10);
    CU_ASSERT_EQUAL(tcb_encontrado.posy, 1);
    CU_ASSERT_EQUAL(tcb_encontrado.prox_tarea, 1);
    CU_ASSERT_EQUAL(tcb_encontrado.puntero_pcb, 9);

    //dump_segmentacion_pura();
    liberar_tabla_huecos();
    liberar_memoria_principal();
    

    void tabla_destroy(t_segmento * seg){
        free(seg);
    }
}

void validar_informar_tarea(){
    t_iniciar_patota data_input;

    data_input.cant_tripulantes = 1;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;10|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "1|2";
    data_input.long_posicion = strlen("1|2");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    iniciar_memoria_principal(128);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(128);
    set_size_memoria(128);

    bool res = iniciar_patota_segmentacion(data_input);
    
    char* tareas = get_tareas(data_input.patota_id);
    t_TCB tcb = get_TCB(data_input.patota_id, 2);
    t_info_tarea tarea = get_tarea(tareas, tcb.prox_tarea);
    tcb.prox_tarea++;
    set_tripulante(tcb, data_input.patota_id);

    t_TCB tcb_encontrado = get_TCB_segmentacion_pura(data_input.patota_id, 2);
    CU_ASSERT_EQUAL(tcb_encontrado.prox_tarea, 2);

    CU_ASSERT_EQUAL(tarea.tarea, OTRA_TAREA);
    CU_ASSERT_EQUAL(tarea.parametro, 0);
    CU_ASSERT_EQUAL(tarea.posicion.posx, 1);
    CU_ASSERT_EQUAL(tarea.posicion.posy, 1);
    CU_ASSERT_EQUAL(tarea.tiempo, 10);

    liberar_tabla_huecos();
    liberar_memoria_principal();
    

    void tabla_destroy(t_segmento * seg){
        free(seg);
    }
}

void validar_compactacion(){

    t_iniciar_patota data_input, data_input2;

    data_input.cant_tripulantes = 2;
    data_input.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15|TOMAR_AGUA;1;1;2|GENERAR_OXIGENO 10;4;4;15";
    data_input.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15|TOMAR_AGUA;1;1;2|GENERAR_OXIGENO 10;4;4;15");
    data_input.posiciones = "1|2 0|0";
    data_input.long_posicion = strlen("1|2 0|0");
    data_input.patota_id = 1;
    data_input.id_primer_tripulante = 2;

    data_input2.cant_tripulantes = 1;
    data_input2.tareas = "DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15|TOMAR_AGUA;1;1;2|GENERAR_OXIGENO 10;4;4;15";
    data_input2.long_tareas = strlen("DESCARGAR_ITINERARIO;1;1;1|GENERAR_OXIGENO 10;4;4;15|TOMAR_AGUA;1;1;2|GENERAR_OXIGENO 10;4;4;15");
    data_input2.posiciones = "9|2";
    data_input2.long_posicion = strlen("9|2");
    data_input2.patota_id = 2;
    data_input2.id_primer_tripulante = 4;

    t_expulsar_tripulante data;

    data.patota_id = 1;
    data.tripulante_id = 2;

    printf("long tarea: %d \n ",data_input2.long_tareas);

    cfg_create("cfg/mi_ram_hq.config");
    iniciar_memoria_principal(256);
    iniciar_lista_tabla_segmento();
    iniciar_tabla_huecos(256);
    set_size_memoria(256);
    //char * alg = "FF";
    //set_algoritmo_ubicacion(alg);

    bool res1 = iniciar_patota_segmentacion(data_input);

    expulsar_tripulante(data);

    bool res2 = iniciar_patota_segmentacion(data_input2);

    bool hay_memoria_libre = se_puede_escribir(8);//no se puede escribir porque solo hay 47 bytes libres en memoria
    int cant_tablas_segmemtos = cantidad_de_tablas_de_segmento_test();
    int cant_huecos = cantidad_huecos_test();
    t_tabla_segmentos * tabla = get_tabla_segmento_segun_indice_test(0);

    printf("cant de huecos: %d \n ",cant_huecos);

    for (size_t i = 0; i < cant_huecos; i++)
    {
        t_hueco * h = get_hueco_index_test(i);
        printf("base: %d \n",h->base);
        printf("desplazamiento: %d \n",h->desplazamiento);
    }

    CU_ASSERT_TRUE(res1);
    CU_ASSERT_TRUE(hay_memoria_libre);
    CU_ASSERT_EQUAL(cant_tablas_segmemtos, 2);
    CU_ASSERT_EQUAL(cant_huecos, 1);
    CU_ASSERT_EQUAL(list_size(tabla->segmentos), 3);

    liberar_tabla_huecos();
    liberar_memoria_principal();
    

    /* void tabla_destroy(t_segmento * seg){
        free(seg);
    }
    */

}