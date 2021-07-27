#include "util_mi_ram.h"
    // typedef struct{
	// 	type_task tarea;
	// 	int parametro;
	// 	Posicion posicion;
	// 	int tiempo;	
	// }t_info_tarea;

    // char**  string_split(char * text, char * separator);
    //n_tarea, entre 1 a n
    //"ARREGLAR_REACTOR;7;2;5";

    char * dame_tarea (lista_tareas,n_tareas){
        char *lista_aux = string_split(lista_tareas,'\n');

        return lista_aux[n_tareas-1];

    }


    t_info_tarea get_tarea(lista_tareas, n_tarea){
        t_info_tarea tarea_aux;
        char* tarea = dame_tarea(char* lista_tareas, int n_tarea);
        //"ARREGLAR_REACTOR;7;2;5";
        // ' Generaroxigeno 12 ;4;5;6:
        
       char* partes = string_split(tarea,';');
                //borrar este spit y cambiar los campos.
       char* partes_aux = string_split(partes[0],' ');

        
        tarea_aux.tarea = partes_aux[0];
        tarea_aux.parametro = partes_aux[1];
        tarea_aux.posicion.posx = atoi(partes[1]);
        tarea_aux.posicion.posy = atoi(partes[2]);
        tarea_aux.tiempo = atoi(partes[3]);
    
    
       
        return tarea_aux;
}




	
