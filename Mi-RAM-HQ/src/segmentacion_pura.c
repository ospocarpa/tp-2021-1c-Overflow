#include "segmentacion_pura.h"

t_list * list_tablas_segmentos; // lista de tablas de segmento t_tabla_segmentos
t_list * tabla_hueco; // 
static char * alg_ubicacion = "FF";
int size_memoria = 0;

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

void set_size_memoria(int size_m){
    size_memoria = size_m;
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
    //printf("\nTamaño: %d\n", desplazamiento);
    t_hueco * hueco_a_ocupar = list_get(tabla_hueco, indice_hueco);

    //printf("Hueco a ocupar base: %d\n", hueco_a_ocupar->base);
    int base_nueva = hueco_a_ocupar->base + desplazamiento;
    int desplazamiento_nuevo =  hueco_a_ocupar->desplazamiento - desplazamiento;

    //printf("Base nueva: %d Desplazamiento nuevo: %d\n\n", base_nueva, desplazamiento_nuevo);
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

    //printf("ff: cant de huecos: %d \n ",cantidad_huecos_test());

    return base;
}

int algoritmo_mejor_ajuste(t_data_segmento * data){
    //printf("Inicio mejor ajuste, tamaño: %d\n", data->tam_data);
    int base;

    //Ver el primer hueco disponible
    int indice = 0;
    t_hueco * hueco_seleccionado = NULL;
    t_hueco * hueco_temp = NULL;

    for(int c=0; c<list_size(tabla_hueco);c++){
        hueco_temp = list_get(tabla_hueco, c);

        if(hueco_temp->desplazamiento >= data->tam_data){
            hueco_seleccionado = list_get(tabla_hueco, c);
            indice = c;
            break;
        }
    }
    int pivote_titular = hueco_seleccionado->desplazamiento - data->tam_data; //2
    
    int pivote_auxiliar;
    int indice_a_borrar = indice;
    
    for(int c=indice+1; c<list_size(tabla_hueco);c++){
        t_hueco* hueco_temp = list_get(tabla_hueco, c);
        pivote_auxiliar = hueco_temp->desplazamiento - data->tam_data; //1
        if(pivote_auxiliar>=0){
            if(pivote_auxiliar<pivote_titular){
                hueco_seleccionado = hueco_temp;
                pivote_titular = pivote_auxiliar;
                indice_a_borrar = c;
            }
        }
    }

    //hueco_seleccionado = list_get(tabla_hueco, );
    base = hueco_seleccionado->base;
    if(hueco_seleccionado->desplazamiento == data->tam_data){
        indice = indice_a_borrar;
        //eliminarlo de la lista;
        list_remove(tabla_hueco, indice);
        //hueco_detroy(hueco_temp);
    }else{
        
        hueco_seleccionado->base = hueco_seleccionado->base + data->tam_data;
        hueco_seleccionado->desplazamiento = size_memoria - hueco_seleccionado->base;
        //printf("2 hueco_seleccionado base: %d \n", hueco_seleccionado->base);
        //printf("2 hueco_seleccionado desplazamiento: %d \n", hueco_seleccionado->desplazamiento);
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
    //printf("Libre: %d Tamanio: %d\n", tam_memoria_libre, tam_info);
    return (tam_memoria_libre >= tam_info);
}

void escribir_memoria_principal(t_data_segmento * data_semento,int base){ 
    cargar_data_segmento(data_semento,base);
}

//completar
t_segmento * elegir_segmento(t_data_segmento * data_segmento){
    int base = 0;
    t_segmento * segmento = malloc(sizeof(t_segmento));
    //printf("\nAlgoritmo de reemplazo: %s\n", alg_ubicacion);
    if (strcmp(alg_ubicacion,"FF") == 0 )
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
        compactacion();
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

t_list* get_todos_los_segmentos(){  //[t_segmento]
    t_list* lista_segmentos_global = list_create();

    int cant_tablas = list_size(list_tablas_segmentos);
    for(int c=0; c<cant_tablas; c++){
        t_tabla_segmentos* tabla_segmento = get_tabla_segmento_segun_indice_test(c);
        t_list* segmentos_de_tabla = tabla_segmento->segmentos;
        list_add_all(lista_segmentos_global, segmentos_de_tabla);
    }

    return lista_segmentos_global;
}

void compactacion(){
    //printf("estoy compactando \n");
    t_list* segmentos_global = get_todos_los_segmentos();           //Representa a todos los segmentos del sistema
    bool comparador(t_segmento *segmento1, t_segmento *segmento2)
    {
        return segmento1->base < segmento2->base;
    }
    list_sort(segmentos_global, comparador);            // Se ordena los segmentos por la base
    
    //printf("Compactación\n");
    for(int c=0; c<list_size(segmentos_global); c++){
        t_segmento* segmento_aux = list_get(segmentos_global, c);
        //printf("Base: %d Desplazamiento: %d\n", segmento_aux->base, segmento_aux->desplazamiento);
    }

    int base_pivote = 0; 
    int ultimo_desplazamiento = 0;
    t_segmento *s;
    for(int c=0; c<list_size(segmentos_global); c++){
        s = list_get(segmentos_global, c);
        ultimo_desplazamiento = s->desplazamiento;
        if(base_pivote == s->base ){
            base_pivote += s->desplazamiento;
            continue;
        }else{
            mover_segmento(s, base_pivote);
            base_pivote += s->desplazamiento;
        }
    }
    //printf("Posterior Compactación\n");
    for(int c=0; c<list_size(segmentos_global); c++){
        t_segmento* segmento_aux = list_get(segmentos_global, c);
        //printf("Base: %d Desplazamiento: %d\n", segmento_aux->base, segmento_aux->desplazamiento);
    }
    //printf("compactacion: cant de huecos: %d \n ",list_size(tabla_hueco));

    list_clean(tabla_hueco);

    //printf("compactacion: cant de huecos luego del clean: %d \n ",list_size(tabla_hueco));
    
    int base_new = base_pivote;
    int desplazamiento = size_memoria - base_new;

    agregar_hueco(base_new, desplazamiento);
    //dump_huecos();
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

char* get_tareas_segmentacion(int patota_id){
    bool mismo_tabla_id(t_tabla_segmentos *item){
        return item->pid == patota_id;
    }
    t_tabla_segmentos* tabla_segmento = list_find(list_tablas_segmentos, &mismo_tabla_id);    
    t_segmento* segmento = list_get(tabla_segmento->segmentos, 0);
    char* tareas = leer_info_tareas(segmento->base, segmento->desplazamiento);
    return tareas;
}

/* -------- ACCESO A LA MEMORIA ----- */
char * leer_info_tareas(int base,int tam){
    char * tareas= malloc(tam+1);
    
    memcpy(tareas,memoria_principal+base,tam);
    tareas[tam] = '\0';
    return tareas ;
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
    void* stream = get_stream_tcb(tcb);

    int offset = base;
    memcpy(memoria_principal + offset, stream, 21);
}

void dump_huecos(){
    int cant_huecos = cantidad_huecos_test();
    printf("Dump huecos\n");
    for (size_t i = 0; i < cant_huecos; i++)
    {
        t_hueco * h = get_hueco_index_test(i);
        printf("Base: %d Desplazamiento: %d\n",h->base, h->desplazamiento);
    }
}

char* dump_segmentacion_pura(){
    char *format = "%d/%m/%y %H:%M:%S";
    char *timestamp = temporal_get_string_time(format);
    
    char* contenido = string_new();
    string_append_with_format(&contenido, "Dump: %s\n", timestamp);
    
    /* Obtener todos los segmentos */
    int cant_tablas = list_size(list_tablas_segmentos);
    int proceso_id;
    for(int c=0; c<cant_tablas; c++){
        t_tabla_segmentos* tabla_segmento = get_tabla_segmento_segun_indice_test(c);
        t_list* segmentos_de_tabla = tabla_segmento->segmentos;
        proceso_id = tabla_segmento->pid;

        for(int d=0; d<list_size(segmentos_de_tabla);d++){
            t_segmento* segmento = list_get(segmentos_de_tabla, d);
            string_append_with_format(&contenido, "Proceso: %d Segmento: %d Inicio: %d Tamaño: %d\n", proceso_id, segmento->id, segmento->base, segmento->desplazamiento);
        }
    }
    //TODO: pasar a hexadecimal
    
    printf("%s\n", contenido);
    return contenido;
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

t_hueco * get_hueco_index_test(int indice){
    return list_get(tabla_hueco, indice);
}

/* ****************************** */

void destroy_segmento(t_segmento * segmento){
    free(segmento);
}

void eliminar_segmento_tripulante(t_expulsar_tripulante tripulante){
    bool mismo_tabla_id(t_tabla_segmentos *item){
        return item->pid == tripulante.patota_id;//ver
    }

    t_tabla_segmentos* tabla_segmento = list_find(list_tablas_segmentos, (void * ) mismo_tabla_id);

    bool is_segmento_para_tripulante(t_segmento * seg){
        //printf("id tripulante: %d \n", tripulante.tripulante_id);
        return seg->id == tripulante.tripulante_id;
    }

    t_segmento * seg_eliminado = list_find(tabla_segmento->segmentos, is_segmento_para_tripulante);
    agregar_hueco(seg_eliminado->base, seg_eliminado->desplazamiento);
    

    list_remove_and_destroy_by_condition(tabla_segmento->segmentos, is_segmento_para_tripulante,destroy_segmento);

    //ordeno la lista de huecos por base
    void * ordenar_por_base_menor(t_hueco * hueco1, t_hueco * hueco2){
        return hueco1->base <= hueco2->base ? hueco1 : hueco2;
    }

    list_sort(tabla_hueco, (void *) ordenar_por_base_menor);

   // free(seg_eliminado);//ver
}