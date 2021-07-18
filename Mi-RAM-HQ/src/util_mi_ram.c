#include "util_mi_ram.h"


	// int patota_id;
	// 	char* description;
	// 	int description_length;
	// 	char* parametros;
	// 	int parametros_length;
	// 	int tiempo;
	// 	Posicion* posicion;
	// } Tarea;

    // typedef struct{
	// 	type_task tarea;
	// 	int parametro;
	// 	Posicion posicion;
	// 	int tiempo;	
	// }t_info_tarea;

    // char**  string_split(char * text, char * separator);
    //n_tarea, entre 1 a n
    //"ARREGLAR_REACTOR;7;2;5";

    char * dame_tarea (char* lista_tareas, int n_tareas){
        char *lista_aux = string_split(lista_tareas,'\n');

        return lista_aux[n_tareas-1];

    }


    t_info_tarea get_tarea(char* lista_tareas, int n_tarea){
        t_info_tarea tarea_aux;
        char* tarea = dame_tarea(char* lista_tareas, int n_tarea);//"ARREGLAR_REACTOR;7;2;5";
        partes = string_split(tarea,';');
        partes_aux = string_split(pares[0],' '); // nose si lo toma asi o tendre q usar \s

        if((strlen(partes)-1 ) > 3){
            tarea_aux.tarea = partes_aux[0];
            tarea_aux.parametro = atoi(partes_aux[1]);
            tarea_aux.posicion.pox = atoi(partes[1]);
            tarea_aux.posicion.pox = atoi(partes[2]);
            tarea_aux.timepo = atoi(partes[3]);
        }else{
            if (strlen(partes)-1 ) == 3){
                tarea_aux.tarea = partes[0];
                tarea_aux.parametro = atoi(partes_aux[1]);
                tarea_aux.posicion.pox = atoi(partes[1]);
                tarea_aux.posicion.pox = atoi(partes[2]);
            }
            else{
                // Que hago en el caso de que sea menor a 3?
            }

        }
        return tarea_aux;
}




	
