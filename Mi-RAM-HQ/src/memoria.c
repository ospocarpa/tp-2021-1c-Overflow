#include "memoria.h"

static void * memoria_principal = NULL;
static t_list * tabla_hueco;

/* Declaracion de funciones privadas */
//void agregar_hueco(int base, int desplazamiento);

/* ************************************************** */
void iniciar_memoria_principal(int tam_memoria){

    if(memoria_principal == NULL){
        memoria_principal = malloc(tam_memoria);
		logger_info("Se inicio memoria principal de tamaño: [%d]", tam_memoria);
        tabla_hueco = list_create();
		//agregar_hueco(0, tam_memoria);
    }
}

void agregar_hueco(int base, int desplazamiento){
    t_hueco * nuevo_hueco = malloc(sizeof(t_hueco));
    nuevo_hueco->base = base;
    nuevo_hueco->desplazamiento = desplazamiento;

    list_add(tabla_hueco, nuevo_hueco);
}


void cargar_informacion_PCB_a_MP(t_PCB pcb,int base){
    
    int offset = base;
    memcpy(memoria_principal + offset, &pcb.pid,sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(memoria_principal + offset, &pcb.tareas,sizeof(uint32_t));

}

void cargar_informacion_TCB_a_MP(t_TCB tcb,int base){
    
    // uint32_t tid;
    // char estado;
    // int posx;
    // int posy;
    // uint32_t prox_tarea;
    // uint32_t puntero_pcb;

    int offset = base;
    memcpy(memoria_principal + offset, &tcb.tid,sizeof(uint32_t));
    offset +=sizeof(uint32_t) ;
    memcpy(memoria_principal + offset, &tcb.estado,sizeof(char));
    offset += sizeof(char);
    memcpy(memoria_principal + offset, &tcb.posx,sizeof(int));
    offset +=sizeof(int);
    memcpy(memoria_principal + offset, &tcb.posy,sizeof(int));
    offset +=sizeof(int);
    memcpy(memoria_principal + offset, &tcb.prox_tarea,sizeof(uint32_t));
    offset +=sizeof(uint32_t);
    memcpy(memoria_principal + offset, &tcb.puntero_pcb,sizeof(uint32_t));
    

}
