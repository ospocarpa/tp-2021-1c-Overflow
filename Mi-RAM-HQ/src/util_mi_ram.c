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
        char* tarea = "";
        char **lista_aux = string_split(lista_tareas,"\n");
        int cant_tareas = 0;

        void a_la_lista_partes(char *item)
        {
            cant_tareas++;
        };
        string_iterate_lines(lista_aux, a_la_lista_partes);

        printf("Cant. tareas: %d. Indice tarea: %d\n", cant_tareas, n_tareas);
        if(cant_tareas >= n_tareas){
            tarea =  lista_aux[n_tareas-1];
        }
        printf("Tarea: %s\n", tarea);
        return tarea;
    }


    // la tarea 0 seria como la 1 a la hora de contar
    t_info_tarea get_tarea(char* lista_tareas,int n_tarea){
        t_info_tarea tarea_aux;
        tarea_aux.tarea = OTRA_TAREA;
        tarea_aux.parametro = OTRA_TAREA;
        tarea_aux.posicion.posx = 0;
        tarea_aux.posicion.posy = 0;
        tarea_aux.tiempo = -1;

        char* tarea = dame_tarea(lista_tareas, n_tarea);
        printf("Tarea de util miram: %s\n", tarea);
        if(strcmp(tarea, "") != 0){
            printf("Pase por aqui\n");
            char** partes = string_split(tarea,";");
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
        }
    
        return tarea_aux;
    }


// Entrada: "1|1,2|2,3|3" 
// Posicion get_posicion(char* posicion, int indice){
// }
// Salida: se devuelve la posici??n en formato struct "Posicion"

// Proceso: recibe un arreglo de posiciones en string, debe devolver la posici??n seg??n el indice
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
    //printf("Coord: %d %d\n", pos.posx, pos.posy);
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

int get_timestamp_number(char* timestamp){
    char** parts = string_split(timestamp, ":");

    char* timestamp_format = string_new();
    void concatenar_partes(char *item){
        string_append_with_format(&timestamp_format, "%s", item);
    }
    string_iterate_lines(parts, concatenar_partes);

    int timestamp_number = atoi(timestamp_format);
    return timestamp_number;
}


t_list* list_slice(t_list* lista, int inicio, int fin){
    bool puede_agregar = false;
    bool puede_terminar = false;
    t_list* lista_filtrada = list_create();
    void* item;
    for(int c=0; c<list_size(lista); c++){
        if(c==inicio) puede_agregar = true;
        item = list_get(lista, c);
        if(puede_agregar) list_add(lista_filtrada, item);
        if(c==fin) puede_terminar = true;
        if(puede_terminar) break;
    }
    return lista_filtrada;
}

bool existe_memoria_disponible_paginacion(t_bitarray* bitmap_memoria_real, t_bitarray* bitmap_memoria_virtual, int tamanio_obj){
    int cant_marcos_real = cantidad_disponible(bitmap_memoria_real);
    
    int canti_marcos_virtual  = cantidad_disponible(bitmap_memoria_virtual);
    //printf("Total: %d\n", cant_marcos_real+canti_marcos_virtual);
    if(cant_marcos_real + canti_marcos_virtual >= tamanio_obj ) return true;
    return false;
    
}



bool existe_memoria_real_disponible(t_bitarray* bitmap_memoria_real){
    //print_bit_map(bitmap_memoria_real);
    return esta_Llena_Memoria(bitmap_memoria_real);
}

int cantidad_disponible(t_bitarray* bitmap){
    int cant = 0;
    int bits = bitarray_get_max_bit(bitmap);
  
    for(int c = 0; c < bits ; c++){
        if(!bitarray_test_bit(bitmap,c)){
            cant++;
        }
    }

    return cant;
}

bool esta_Llena_Memoria(t_bitarray* bitmap){
    int indice = 0;
    int bits = bitarray_get_max_bit(bitmap);
    
    for(int c =0; c < bits ; c++){
        if (! bitarray_test_bit(bitmap,c)) return false;
    }
    return true;
}

char* get_label_presencia(bool presencia){
    if(presencia) return "Libre";
    return "Ocupado";
}

void print_bit_map(t_bitarray* bitarray){
    //bitarray_set_bit(bitarray, 3);
    //bitarray_set_bit(bitarray, 10);

    uint32_t bits = bitarray_get_max_bit(bitarray);
    printf("Bits: %d\n", bits);
    /*for(int c=0; c<bits; c++){
		bitarray_clean_bit(bitarray, c);
	}*/

    for(int c=0; c<bits; c++){
        bool bit = bitarray_test_bit(bitarray, c);
        printf("%d ", bit);
    }
    printf("\n");
}
void limpiar_bit_map(t_bitarray* bitmap){
    uint32_t bits = bitarray_get_max_bit(bitmap);
    for(int c=0; c<bits; c++){
        bitarray_clean_bit(bitmap, c);

    }
}