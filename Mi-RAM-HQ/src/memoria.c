#include "memoria.h"

static void * memoria_principal = NULL;
static t_list * tabla_hueco;

/* Declaracion de funciones privadas */
void agregar_hueco(int base, int desplazamiento);
void agregar_hueco_segun_desplazamiento(int indice_hueco, int desplazamiento);

/* ************************************************** */
void iniciar_memoria_principal(int tam_memoria){

    if(memoria_principal == NULL){
        memoria_principal = malloc(tam_memoria);
		//logger_info("Se inicio memoria principal de tamaño: [%d]", tam_memoria);
        tabla_hueco = list_create();
		agregar_hueco(0, tam_memoria);
    }
}

void liberar_memoria_principal(){

    free(memoria_principal);
    memoria_principal = NULL;

}

void agregar_hueco(int base, int desplazamiento){
    t_hueco * nuevo_hueco = malloc(sizeof(t_hueco));
    nuevo_hueco->base = base;
    nuevo_hueco->desplazamiento = desplazamiento;

    list_add(tabla_hueco, nuevo_hueco);
}

t_hueco * hueco_create(int base, int desplazamiento){
    t_hueco * new_hueco = malloc(sizeof(t_hueco));
    new_hueco->base = base;
    new_hueco->desplazamiento = desplazamiento;

    return new_hueco;
}

void hueco_detroy(t_hueco * hueco){
    free(hueco);
}
//puede aguregar o quitar hueco segun el tamaño que se va almacenar es decir el desplazamiento
void agregar_hueco_segun_desplazamiento(int indice_hueco, int desplazamiento){
    t_hueco * hueco_a_ocupar = list_get(tabla_hueco, indice_hueco);

    int base_nueva = hueco_a_ocupar->base + desplazamiento;
    int desplazamiento_nuevo =  hueco_a_ocupar->desplazamiento - desplazamiento;

    if (desplazamiento_nuevo > 0)
    {
        //remplazo en una posicion un nuevo valor del elemento hueco
        t_hueco * hueco_aux = list_replace(tabla_hueco, indice_hueco, hueco_create(base_nueva, desplazamiento_nuevo));
        
        hueco_detroy(hueco_aux);//ver
    }
    else
    {
        list_remove_and_destroy_element(tabla_hueco, indice_hueco, (void *) hueco_detroy);
    }

}

int algoritmo_primer_ajuste(desplazamiento){
    int indice = 0;
    int base;
    t_hueco * hueco = malloc(sizeof(t_hueco));

    do
    {
        hueco = list_get(tabla_hueco, indice);
        indice += 1;
    } while (hueco->desplazamiento >= desplazamiento);
    
    base = hueco->base;
    agregar_hueco_segun_desplazamiento(indice, desplazamiento);
    hueco_detroy(hueco); //ver

    return base;
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