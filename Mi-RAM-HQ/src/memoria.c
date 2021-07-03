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