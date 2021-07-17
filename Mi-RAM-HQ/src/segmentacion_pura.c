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

t_hueco * algoritmo_mejor_ajuste(int desplazamiento){
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

    int indice = 0;
    /* 
    while (!son_huecos_iguales(list_get(tabla_hueco, indice), hueco_seleccionado)){
        indice++;
    }
    
    hueco_seleccionado = list_get(tabla_hueco, indice);

    t_hueco * hueco_aux = list_replace(tabla_hueco, indice, hueco_create(hueco_seleccionado->base, hueco_seleccionado->desplazamiento));
        
    hueco_detroy(hueco_aux);
    */

    base = hueco_seleccionado->base;

    //ver liberar lista
    return hueco_seleccionado;
}

void liberar_tabla_huecos(){
    list_destroy_and_destroy_elements(tabla_hueco, hueco_detroy);
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
        /* code */
    }

    escribir_memoria_principal(data_segmento, base);

    uint32_t id;
    //memcpy la estructura si es tcb
    
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