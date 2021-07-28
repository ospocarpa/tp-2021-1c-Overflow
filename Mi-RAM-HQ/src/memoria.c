#include "memoria.h"

void * memoria_principal = NULL;

/* Declaracion de funciones privadas */


/* ************************************************** */
void iniciar_memoria_principal(int tam_memoria){

    if(memoria_principal == NULL){
        memoria_principal = malloc(tam_memoria);
		//logger_info("Se inicio memoria principal de tamaño: [%d]", tam_memoria);
    }
}

void liberar_memoria_principal(){

    free(memoria_principal);
    memoria_principal = NULL;

}

void cargar_informacion_PCB_a_MP(t_PCB pcb,int base){
    
    int offset = base;
    memcpy(memoria_principal + offset, &pcb.pid,sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(memoria_principal + offset, &pcb.tareas,sizeof(uint32_t));

}

void cargar_informacion_tareas_a_MP(char *tareas,int base){
    memcpy(memoria_principal+base,tareas,strlen(tareas));
}

t_PCB leer_info_PCB(int base){

    t_PCB  pcb;
    int offset =base;
    memcpy(&pcb.pid,memoria_principal+offset,sizeof(uint32_t));
    offset += sizeof(uint32_t);
    memcpy(&pcb.tareas,memoria_principal+offset,sizeof(uint32_t));

    return pcb;

}

t_TCB leer_info_TCB(int base){

    t_TCB  tcb;
    
    int offset =base;
    memcpy(&tcb.tid, memoria_principal + offset, sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(&tcb.estado, memoria_principal + offset, sizeof(char));
    offset += sizeof(char);
    memcpy(&tcb.posx, memoria_principal + offset, sizeof(int));
    offset +=sizeof(int);
    memcpy(&tcb.posy, memoria_principal + offset, sizeof(int));
    offset +=sizeof(int);
    memcpy(&tcb.prox_tarea, memoria_principal + offset, sizeof(uint32_t));
    offset +=sizeof(uint32_t);
    memcpy(&tcb.puntero_pcb, memoria_principal + offset, sizeof(uint32_t));

    return tcb;

}

char * leer_info_tareas(int base,int tam){
    char * tareas= malloc(tam+1);
    
    memcpy(tareas,memoria_principal+base,tam);
    tareas[tam] = '\0';
    return tareas ;
}

void cargar_data_segmento(t_data_segmento * data_segmento, int base ){
    memcpy(memoria_principal, data_segmento->data, data_segmento->tam_data);
}

void set_tripulante(t_TCB tcb){
    set_tripulante_por_segmentacion(tcb);
}

t_TCB get_TCB(int patota_id, int tripulante_id){
    t_TCB tcb = get_TCB_segmentacion_pura(patota_id, tripulante_id);
    return tcb;
}