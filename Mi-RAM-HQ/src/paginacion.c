#include "paginacion.h"

 static t_list * list_tablas_paginacion;
 static t_list * tablas_pag_libre;
 // static t_list *  tabla_hueco;

void iniciar_tabla_paginacion(){
    list_tablas_paginacion = list_create();

}