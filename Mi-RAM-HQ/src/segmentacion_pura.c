#include "segmentacion_pura.h"

static t_list * list_tablas_segmentos;
static t_list * tabla_hueco;
static char * alg_ubicacion = "LL";

/* Declaracion de funciones privadas */
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

/* ****************** */
void set_algoritmo_ubicacion(char * algoritmo){
    alg_ubicacion = algoritmo;
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

int algoritmo_mejor_ajuste(int desplazamiento){
    int base;

    bool hay_espacio(t_hueco * h){
        return ((h->desplazamiento - desplazamiento) >= 0);
    }

    t_list * huecos_candidatos = list_filter(tabla_hueco, hay_espacio);


    t_hueco * hueco_menor_para_desplazamiento(t_hueco * hueco1, t_hueco * hueco2){
    return (hueco1->desplazamiento - desplazamiento <= hueco2->desplazamiento - desplazamiento) ? hueco1 : hueco2;
    }

    t_list * huecos_ordenados = list_sorted( huecos_candidatos, hueco_menor_para_desplazamiento);
    
    t_hueco * hueco_seleccionado = list_get(huecos_ordenados, 0);

    base = hueco_seleccionado->base;

    //ver liberar lista
    return base;
}

void liberar_tabla_huecos(){
    list_destroy_and_destroy_elements(tabla_hueco, hueco_detroy);
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