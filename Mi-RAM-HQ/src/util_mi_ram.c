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
    // ' Generaroxigeno 12 ;4;5;6:

    // `GENERAR_OXIGENO,
	// 	GENERAR_COMIDA,
	// 	CONSUMIR_COMIDA,
	// 	GENERAR_BASURA,
	// 	DESCARTAR_BASURA,
	// 	OTRA_TAREA

    type_task devolver_Enum(char * nombre){

        if (strcmp(nombre,"GENERAR_OXIGENO") == 0) return GENERAR_OXIGENO;
        if (strcmp(nombre,"GENERAR_COMIDA") == 0) return GENERAR_COMIDA;
        if (strcmp(nombre,"CONSUMIR_COMIDA") == 0) return CONSUMIR_COMIDA;
        if (strcmp(nombre,"GENERAR_BASURA") == 0) return GENERAR_BASURA;
        if (strcmp(nombre,"DESCARTAR_BASURA") == 0) return DESCARTAR_BASURA;
        return OTRA_TAREA;
        
    }



    char * dame_tarea (char *lista_tareas,int n_tareas){
        char **lista_aux = string_split(lista_tareas,"\n");

        return lista_aux[n_tareas-1];

    }


    // la tarea 0 seria como la 1 a la hora de contar
    t_info_tarea get_tarea(char* lista_tareas,int n_tarea){
        t_info_tarea tarea_aux;
        char* tarea = dame_tarea(lista_tareas, n_tarea);
        //printf("%s",tarea);
        
        
        char** partes = string_split(tarea,";");
                    //borrar este spit y cambiar los campos.
        char** partes_aux = string_split(partes[0]," ");

        tarea_aux.tarea = devolver_Enum(partes_aux[0]);

        // pasar a funcion si es la tarea que conozco , preguntos y return enum 
        // clave enum

        //tarea_aux.tarea = partes_aux[0];
        //cambiar variable
        if ( tarea_aux.tarea == OTRA_TAREA) tarea_aux.parametro = 0;
        else tarea_aux.parametro = atoi(partes_aux[1]);

        tarea_aux.posicion.posx = atoi(partes[1]);
        tarea_aux.posicion.posy = atoi(partes[2]);
        tarea_aux.tiempo = atoi(partes[3]);
    
    
       
        return tarea_aux;
    }


// Entrada: "1|1,2|2,3|3" 
// Posicion get_posicion(char* posicion, int indice){
// }
// Salida: se devuelve la posición en formato struct "Posicion"

// Proceso: recibe un arreglo de posiciones en string, debe devolver la posición según el indice
// typedef struct
// 	{
// 		int posx;
// 		int posy;
// 	}__attribute__((packed))
// 	Posicion;

Posicion get_posicion_STR(char *posiciones, int indice){
    //printf("%s %d\n", posiciones, indice);
    Posicion pos;
    char** partes = string_split(posiciones," ");
    
    char** pos_aux = string_split(partes[indice-1],"|");
    pos.posx = atoi(pos_aux[0]);
    pos.posy = atoi(pos_aux[1]);

    return pos;
 }

 char map_estado(status_tripulante status){
        switch (status)
        {
            case NEW:
                return 'N';
            case READY:
                return 'R';
            case EXEC:
                return 'E';
            case BLOCKED:
                return 'B';
            case BLOCKED_SABOTAJE:
                return 'B';
        }
        return ' ';
    }
