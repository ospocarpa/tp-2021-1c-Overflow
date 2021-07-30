#include "segmentacion_pura.h"

static t_list * list_tablas_segmentos; // lista de tablas de segmento t_tabla_segmentos
static t_list * tabla_hueco; // 
static char * alg_ubicacion = "LL";

/* Declaracion de funciones privadas */
t_hueco * hueco_create(int base, int desplazamiento);
void agregar_hueco(int base, int desplazamiento);
void agregar_hueco_segun_desplazamiento(int indice_hueco, int desplazamiento);

/* **************************************** */

void iniciar_lista_tabla_segmento(){
    list_tablas_segmentos = list_create();
}

void iniciar_tabla_huecos(int tam_memoria){
    tabla_hueco = list_create();
	agregar_hueco(0, tam_memoria);
}

void agregar_tabla_de_segmento(t_tabla_segmentos * tabla){
    list_add(list_tablas_segmentos, tabla);
}

/* ****************** */
void set_algoritmo_ubicacion(char * algoritmo){
    alg_ubicacion = algoritmo;
}

void agregar_hueco(int base, int desplazamiento){
    t_hueco * nuevo_hueco = hueco_create(base, desplazamiento);

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

int algoritmo_primer_ajuste(t_data_segmento * data_segmento){
    
    int base;

    for (size_t i = 0; i < list_size(tabla_hueco); i++)
    {
        t_hueco * hueco = list_get(tabla_hueco, i);

        if (hueco->desplazamiento >= data_segmento->tam_data)
        {
            base = hueco->base;
            agregar_hueco_segun_desplazamiento(i, data_segmento->tam_data);
            break;
        } 
    }

return base;
}

int algoritmo_mejor_ajuste(int desplazamiento){
    int base;

    //Ver el primer hueco disponible
    int indice = 0;
    t_hueco * hueco_seleccionado = NULL;
    t_hueco * hueco_temp = NULL;

    for(int c=0; c<list_size(tabla_hueco);c++){
        hueco_temp = list_get(tabla_hueco, c);

        if(hueco_temp->desplazamiento >= desplazamiento){
            hueco_seleccionado = list_get(tabla_hueco, c);
            indice = c;
            break;
        }
    }

    int pivote_titular = hueco_seleccionado->desplazamiento - desplazamiento; //2
    
    int pivote_auxiliar;
    int indice_a_borrar = indice;
    
    for(int c=indice+1; c<list_size(tabla_hueco);c++){
        //t_hueco* hueco_temp = list_get(tabla_hueco, c);
        pivote_auxiliar = hueco_temp->desplazamiento - desplazamiento; //1
        if(pivote_auxiliar>=0){
            if(pivote_auxiliar<pivote_titular){
                hueco_seleccionado = hueco_temp;
                pivote_titular = pivote_auxiliar;
                indice_a_borrar = c;
            }
        }
    }

    base = hueco_seleccionado->base;
    if(hueco_seleccionado->desplazamiento == desplazamiento){
        indice = indice_a_borrar;
        //eliminarlo de la lista;
        list_remove_and_destroy_element(tabla_hueco, indice, (void *) hueco_detroy);
        hueco_detroy(hueco_temp);
    }else{
        
        hueco_seleccionado->base = hueco_seleccionado->base + desplazamiento; 
    }

    return base;
}

void liberar_tabla_huecos(){
    list_destroy_and_destroy_elements(tabla_hueco, hueco_detroy);
}

void tabla_segmentos_detroy(t_tabla_segmentos * tabla){
    list_destroy_and_destroy_elements(tabla->segmentos, free);
    free(tabla);
}

void liberar_lista_de_tablas_segmentos(){
    list_destroy_and_destroy_elements(list_tablas_segmentos, tabla_segmentos_detroy);
}

bool se_puede_escribir(int tam_info){
    int tam_memoria_libre = 0;

    void sumar_espacios_libres(t_hueco * hueco){
        tam_memoria_libre += hueco->desplazamiento;
    }

    list_iterate(tabla_hueco, sumar_espacios_libres);

    return (tam_memoria_libre >= tam_info);
}

void escribir_memoria_principal(t_data_segmento * data_semento,int base){ 
    cargar_data_segmento(data_semento,base);
}

//completar
t_segmento * elegir_segmento(t_data_segmento * data_segmento){
    int base = 0;
    t_segmento * segmento = malloc(sizeof(t_segmento));

    if (alg_ubicacion == "LL")
    {
       base = algoritmo_primer_ajuste(data_segmento);
    }
    else
    {
        base = algoritmo_mejor_ajuste(data_segmento);
    }

    escribir_memoria_principal(data_segmento, base);

    //genero el id del segmento
    uint32_t id;
    
    switch (data_segmento->tipo)
    {
    case TAREAS:
        id = 0;
        break;
    
    case PCB:
        id = 1;
        break;

    case TCB:
        memcpy(&id,data_segmento->data, sizeof(uint32_t));
        break;
    
    default:
        break;
    }
    
    // asigno valor al segmento
    segmento->id = id;
    segmento->base = base;
    segmento->desplazamiento = data_segmento->tam_data;
}

//validamos si hay un hueco para ese tamaño
bool hay_segmento_disponible(int tamanio){

    bool hay_hueco_para_segmento(t_hueco * hueco){
        return (hueco->desplazamiento >= tamanio);
    }

    bool satisfy = list_any_satisfy(tabla_hueco, hay_hueco_para_segmento);

    return satisfy;
}

t_segmento * escribir_segmentacion_pura(t_data_segmento * data){
    t_segmento * segmento;

    if(hay_segmento_disponible(data->tam_data)){
        segmento = elegir_segmento(data);
    }
    else
    {
        /* compactacion() */
        segmento = elegir_segmento(data);
    }
    

    return segmento;
}

t_TCB get_TCB_segmentacion_pura(int patota_id, int tripulante_id){
    bool mismo_tabla_id(t_tabla_segmentos *item){
        return item->pid == patota_id;
    }
    t_tabla_segmentos* tabla_segmento = list_find(list_tablas_segmentos, &mismo_tabla_id);
    
    bool mismo_segmento_id(t_segmento *item){
        return item->id == tripulante_id;
    }
    t_segmento* segmento = list_find(tabla_segmento->segmentos, &mismo_segmento_id);

    int base = segmento->base; 

    t_TCB tcb = leer_info_TCB(base);
    return tcb;
}

/* *********************FENCIONES PARA TESTEAR************************ */

int cantidad_de_tablas_de_segmento_test(){
    return list_size(list_tablas_segmentos);
}

int cantidad_huecos_test(){
    return list_size(tabla_hueco);
}

t_tabla_segmentos * get_tabla_segmento_segun_indice_test(int indice){
    return list_get(list_tablas_segmentos, indice);
}

void compactacion(){
    t_list* segmentos_global = list_create();           //Representa a todos los segmentos del sistema
    bool comparador(t_segmento *segmento1, t_segmento *segmento2)
    {
        return segmento1->base < segmento2->base;
    }
    list_sort(segmentos_global, comparador);            // Se ordena los segmentos por la base

    int base_pivote = 0; 
    for(int c=0; c<list_size(segmentos_global); c++){
        t_segmento *s = list_get(segmentos_global, c);
        if(base_pivote == s->base ){
            base_pivote += s->desplazamiento;
            continue;
        }else{
            mover_segmento(s, base_pivote);
        }
    }
}

void mover_segmento(t_segmento *segmento, int base_pivote){
    //Reescribir el contenido de la memoria
    int offset = segmento->base;

    void* informacion = malloc(segmento->desplazamiento);
    memcpy(informacion, memoria_principal + offset, segmento->desplazamiento);

    offset = base_pivote;
    memcpy(memoria_principal + offset, informacion, segmento->desplazamiento);

    //Actualizar el segmento de la tabla de página => implica modifcar la base
    segmento->base = base_pivote;
}

void set_tripulante_por_segmentacion(t_TCB tcb, int patota_id){
    //Capaz no sea necesario pasarle la patotaid
    bool mismo_tabla_id(t_tabla_segmentos *item){
        return item->pid == patota_id;
    }
    t_tabla_segmentos* tabla_segmento = list_find(list_tablas_segmentos, &mismo_tabla_id);
    bool mismo_segmento_id(t_segmento *item){
        return item->id == tcb.tid;
    }
    t_segmento* segmento = list_find(tabla_segmento->segmentos, &mismo_segmento_id);
    int base = segmento->base; 

    cargar_informacion_TCB_a_MP(tcb, base);
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