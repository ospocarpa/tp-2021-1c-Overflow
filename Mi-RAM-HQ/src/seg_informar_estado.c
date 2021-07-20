#include "seg_informar_estado.h"


// primera lista list_tabla_segmentos
//t_tabla_segmentos
//void *list_find(t_list *, bool(*closure)(void*));

void filtrar_pid(uint32_t pid, t_lista * lista){
    bool _esIgual(list_tabla_sementos){
        return list_tabla_segmentos.pid == pid;
    }

    //void *list_find(t_list *, bool(*closure)(void*));
    list_find(t_lista,_esIgual);
}

void filter_pid(unit32_t pid, t_list *lista){
    //t_list* list_filter(t_list*, bool(*condition)(void*));
    bool _esIgualPid(void *list_tabla_segmentos){
        return lista_tabla_segmentos.pid == pid;
    }
    t_list

}