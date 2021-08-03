#include "paginacion.h"

void iniciar_tabla_paginacion(){
    list_tablas_paginacion = list_create();
}

t_bitarray* inicializar_bitmap(int cant_bits){
    void* puntero_bitmap = malloc(cant_bits/8);
    t_bitarray* bitmap = bitarray_create_with_mode(puntero_bitmap, cant_bits/8, LSB_FIRST);
    return bitmap;
} 

void* dame_todo_el_stream(t_list* pages){   //[t_page]
    int pagina_tam = get_tamanio_tamanio_pagina();
    int cant_paginas = list_size(pages); 
    int offset = 0;
    void* informacion = malloc(cant_paginas*pagina_tam);
    for(int c=0; c< cant_paginas; c++){
        t_page* page = list_get(pages, c);
        void* info_marco = get_info(page);

        memcpy(informacion + offset, info_marco, pagina_tam);
        offset += pagina_tam;
    }
    return informacion;
}

void* get_info(t_page* page){
    int pagina_tam = get_tamanio_tamanio_pagina();
    void* stream = malloc(pagina_tam);
    if(page->presencia){
        stream = leer_memoria_real(page->frame, pagina_tam);
    }else{
        int frame = get_first_frame_disponible(bitmap_memoria_real);
        stream = transferencia_de_swap_a_memoria_real(page, frame);
    }
    return stream;
}

void* transferencia_de_swap_a_memoria_real(t_page* page, int frame){
    int pagina_tam = get_tamanio_tamanio_pagina();
    void* stream = get_info_virtual(page);
    clean_indice_bitmap(bitmap_memoria_virtual, page->frame);

    page->frame = frame;
    escribir_memoria_real(stream, page->frame, pagina_tam);
    return stream;
}

void* get_info_virtual(t_page* page){
    int pagina_tam = get_tamanio_tamanio_pagina();
    void* stream = leer_memoria_virtual(page->frame, pagina_tam);
    return stream;
}

void transferencia_de_memoria_real_a_swap(t_page* page){
    int pagina_tam = get_tamanio_tamanio_pagina();
    page->presencia = false;
    set_indice_bitmap(bitmap_memoria_real, page->frame);
    int frame_memoria_virtual = get_first_frame_disponible(bitmap_memoria_virtual);

    void* informacion_pagina = leer_memoria_real(page->frame, pagina_tam);
    escribir_memoria_virtual(informacion_pagina, frame_memoria_virtual, pagina_tam);

    page->frame = frame_memoria_virtual;
}

int get_first_frame_disponible(t_bitarray* bitmap){
    return 0;
}

void dump_paginacion(){
    char *format = "%d/%m/%y %H:%M:%S";
    char *timestamp = temporal_get_string_time(format);
    
    char* contenido = string_new();
    string_append_with_format(&contenido, "Dump: %s\n", timestamp);
    
    /*int cant_tablas = list_size(list_tablas_paginacion);
    int proceso_id;
    for(int c=0; c<cant_tablas; c++){
        //t_tabla_segmentos* tabla_segmento = get_tabla_segmento_segun_indice_test(c);
        t_list* segmentos_de_tabla = tabla_segmento->segmentos;
        proceso_id = tabla_segmento->pid;

        for(int d=0; d<list_size(segmentos_de_tabla);d++){
            t_segmento* segmento = list_get(segmentos_global, d);
            string_append_with_format(&contenido, "Proceso: %d Segmento: %d Inicio: %d Tamaño: %d\n", proceso_id, segmento->id, segmento->base, segmento->desplazamiento);
        }
    }
    //TODO: pasar a hexadecimal
    
    printf("%s\n", contenido);*/
}

t_TCB get_TCB_paginacion(int patota_id, int tripulante_id){
    t_paginacion_temporal informacion_administrativa = get_paginacion_temporal(patota_id, tripulante_id); 

    void* stream = dame_todo_el_stream(informacion_administrativa.pages_filtradas);
    void* stream_tcb = malloc(21);
    memcpy(stream_tcb, stream + informacion_administrativa.offset, 21);

    t_TCB tcb = leer_info_TCB_generico(stream_tcb);
    return tcb;
}

char* get_tareas_paginacion(int patota_id){
    int pagina_tam = get_tamanio_tamanio_pagina();
    bool mismo_tabla_id(t_table_page *item){
        return item->patota_id == patota_id;
    }
    t_table_page* tabla_paginacion = list_find(list_tablas_paginacion, &mismo_tabla_id);
    int cant_paginas_tarea = tabla_paginacion->cant_caracteres_tarea/pagina_tam;
    if(tabla_paginacion->cant_caracteres_tarea%pagina_tam==0) cant_paginas_tarea++;
    t_list* paginas_filtradas = list_slice(tabla_paginacion->pages, 0, cant_paginas_tarea);

    void* stream = dame_todo_el_stream(paginas_filtradas);
    char* tareas = malloc(tabla_paginacion->cant_caracteres_tarea);
    memcpy(tareas, stream, tabla_paginacion->cant_caracteres_tarea);

    return tareas;
}

void set_TCB_paginacion(t_TCB tcb, int patota_id){
    int pagina_tam = get_tamanio_tamanio_pagina();
    int tripulante_id = tcb.tid;
    t_paginacion_temporal informacion_administrativa = get_paginacion_temporal(patota_id, tripulante_id);
    int offset = informacion_administrativa.offset;
    t_list* paginas_filtradas = informacion_administrativa.pages_filtradas;

    void* stream = get_stream_tcb(tcb);
    t_page* page;
    int offset_por_marco;
    if(list_size(paginas_filtradas)>1){
        page = list_get(paginas_filtradas, 0);
        offset_por_marco = page->frame * pagina_tam;
        int tamanio_restante = pagina_tam-offset;
        void* stream_parte = malloc(tamanio_restante);
        memcpy(stream_parte, stream + offset, tamanio_restante);
        memcpy(memoria_principal + offset_por_marco + offset, stream, tamanio_restante);

        offset += tamanio_restante;
        page = list_get(paginas_filtradas, 1);
        offset_por_marco = page->frame * pagina_tam;
        int tamanio_restante_otro = 21 - tamanio_restante;
        stream_parte = malloc(tamanio_restante_otro);

        memcpy(stream_parte, stream + offset, tamanio_restante_otro);
        memcpy(memoria_principal + offset_por_marco, stream, tamanio_restante_otro);
    }else{
        page = list_get(paginas_filtradas, 0);
        offset_por_marco = page->frame * pagina_tam;
        memcpy(memoria_principal + offset_por_marco + offset, stream, 21);
    }
}

t_paginacion_temporal get_paginacion_temporal(int patota_id, int tripulante_id){
    bool mismo_tabla_id(t_table_page *item){
        return item->patota_id == patota_id;
    }
    t_table_page* tabla_paginacion = list_find(list_tablas_paginacion, &mismo_tabla_id);
    
    int pagina_tam = get_tamanio_tamanio_pagina();
    int indice_tripulante;
    int tripulante_pivote_id;
    for(int c=0; c<list_size(tabla_paginacion->tripulante_ids); c++){
        tripulante_pivote_id = list_get(tabla_paginacion->tripulante_ids, c);
        if(tripulante_pivote_id == tripulante_id){
            indice_tripulante = c;
            break;
        }
    } 

    int tamanio_anterior = tabla_paginacion->cant_caracteres_tarea + 8 + 21 * indice_tripulante;
    int cant_paginas = tamanio_anterior/pagina_tam;
    if(tamanio_anterior%pagina_tam == 0) cant_paginas++;

    int offset = tamanio_anterior%pagina_tam;
    int inicio_pagina_indice = cant_paginas-1;
    if(tamanio_anterior%pagina_tam == 0) inicio_pagina_indice++;

    int auxiliar_offset = offset + 21;
    int fin_pagina_indice = inicio_pagina_indice;
    if(auxiliar_offset > pagina_tam) fin_pagina_indice++;

    t_list* paginas_filtradas = list_slice(tabla_paginacion->pages, inicio_pagina_indice, fin_pagina_indice);

    t_paginacion_temporal informacion_administrativa;
    informacion_administrativa.pages_filtradas = paginas_filtradas;
    informacion_administrativa.offset = offset;
    return informacion_administrativa;
}

//ALGORITMO DE REEMPLAZO
t_page* obtener_pagina_candidato_por_algoritmo_de_reemplazo(){
    char* algoritmo_reemplazo = get_algoritmo_de_remplazo();
    t_page* pagina = NULL;

    if(strcmp(algoritmo_reemplazo, "LRU") == 0){
        pagina = obtener_pagina_por_LRU();
    }else{
        pagina = obtener_pagina_por_Clock();
    }
    return pagina;
}

t_page* obtener_pagina_por_LRU(){
    t_list* paginas_global = obtener_todas_las_paginas();
    t_page* pagina = list_get(paginas_global, 0);
    int time_stamp = get_timestamp_number(pagina->timestamp);
    int time_stamp_auxiliar;
    for(int c=1; c<list_size(paginas_global); c++){
        t_page* pagina_pivote = list_get(paginas_global, c);
        time_stamp_auxiliar = get_timestamp_number(pagina_pivote->timestamp);
        if(time_stamp_auxiliar<time_stamp){
            time_stamp = time_stamp_auxiliar;
            pagina = pagina_pivote;
        }
    }
    return pagina;
}

t_page* obtener_pagina_por_Clock(){
    t_list* paginas_global = obtener_todas_las_paginas();
    t_page* pagina = NULL;

    //Obtener la primera página con bit de uso
    for(int c=0; c<list_size(paginas_global); c++){
        t_page* pagina_pivote = list_get(paginas_global, c);
        if(pagina_pivote->uso){
            pagina_pivote->uso = false;
        }
        else{
            pagina = pagina_pivote;
            break;
        }
    }

    if(pagina == NULL){
        for(int c=0; c<list_size(paginas_global); c++){
            t_page* pagina_pivote = list_get(paginas_global, c);
            if(pagina_pivote->uso){
                pagina_pivote->uso = false;
            }
            else{
                pagina = pagina_pivote;
                break;
            }
        }
    }   
    return pagina;
}

t_list* obtener_todas_las_paginas(){
    t_list* lista_paginas_global = list_create();
    int cant_tablas = list_size(list_tablas_paginacion);

    for(int c=0; c<cant_tablas; c++){
        t_table_page* tabla_pagina = get_tabla_pagina_segun_indice(c);
        t_list* paginas_de_tabla = tabla_pagina->pages;
        list_add_all(lista_paginas_global, paginas_de_tabla);
    }
    return lista_paginas_global;
}

t_table_page* get_tabla_pagina_segun_indice(int indice){
    return list_get(list_tablas_paginacion, indice);
}

//ACCESO AL BITMAP
void clean_indice_bitmap(t_bitarray* bitmap, int indice){
    bitarray_clean_bit(bitmap, indice);
}

void set_indice_bitmap(t_bitarray* bitmap, int indice){
    bitarray_set_bit(bitmap, indice);
}

//ACCESO A LA MEMORIA
void* leer_memoria_real(int marco, int desplazamiento){
    void * stream = malloc(desplazamiento);
    memcpy(stream, memoria_principal + marco * desplazamiento, desplazamiento);
    return stream;
}

void* leer_memoria_virtual(int marco, int desplazamiento){
    void * stream = malloc(desplazamiento);
    memcpy(stream, memoria_virtual + marco * desplazamiento, desplazamiento);
    return stream;
}

void escribir_memoria_real(void *stream, int base, int desplazamiento){
    memcpy(memoria_principal + base * desplazamiento, stream, desplazamiento);
    return stream;
}

void escribir_memoria_virtual(void *stream, int base, int desplazamiento){
    memcpy(memoria_virtual + base * desplazamiento, stream, desplazamiento);
    return stream;
}