#include "../include/config_utils.h"

t_config * leer_config_file(char* configName)
{
	t_config * g_config = config_create(configName);
	return g_config;
}

t_config_mongo_store* leer_config_mongo_store(t_config* config){
	t_config_mongo_store* config_mongo_store = malloc(sizeof(t_config_mongo_store));

	config_mongo_store->IP_DISCORDIADOR = config_get_string_value(config,"IP_DISCORDIADOR");
	config_mongo_store->PUERTO_DISCORDIADOR = config_get_int_value(config,"PUERTO_DISCORDIADOR");
	config_mongo_store->IP_MODULO = config_get_string_value(config,"IP_MODULO");
	config_mongo_store->PUERTO = config_get_int_value(config,"PUERTO");
	config_mongo_store->PUNTO_MONTAJE = config_get_string_value(config,"PUNTO_MONTAJE");
	config_mongo_store->TIEMPO_SINCRONIZACION = config_get_int_value(config,"TIEMPO_SINCRONIZACION");
	config_mongo_store->ARCHIVO_LOG = config_get_string_value(config,"ARCHIVO_LOG");
	config_mongo_store->BLOCK_SIZE = config_get_int_value(config,"BLOCK_SIZE");
    config_mongo_store->BLOCKS = config_get_int_value(config,"BLOCKS");

	char* posiciones_sabotaje_string = config_get_string_value(config,"POSICIONES_SABOTAJE");
	posiciones_sabotaje_string = string_substring(posiciones_sabotaje_string, 1, string_length(posiciones_sabotaje_string)-2); 
	
	config_mongo_store->POSICIONES_SABOTAJE = list_create();
	char** partes_posiciones = string_split(posiciones_sabotaje_string, ",");
    void a_la_lista_posiciones(char *item) {
		//item = "1|1"
		char** coordenadas = string_split(item, "|");
		Posicion* posicion = malloc(sizeof(Posicion));
		posicion->posx = atoi(coordenadas[0]);
		posicion->posy = atoi(coordenadas[1]);
		list_add(config_mongo_store->POSICIONES_SABOTAJE, posicion);
    }
    string_iterate_lines(partes_posiciones, a_la_lista_posiciones);

	/*for(int c=0;c< list_size(config_mongo_store->POSICIONES_SABOTAJE); c++){
        Posicion* posicion = list_get(config_mongo_store->POSICIONES_SABOTAJE, c);
        printf("%d %d\n", posicion->posx, posicion->posy);
    }*/
	return config_mongo_store;
}

t_config_discordiador* leerConfigDiscordiador(t_config* config)
{	t_config_discordiador* config_discordiador = malloc(sizeof(t_config_discordiador));

	config_discordiador->IP_MODULO = config_get_string_value(config,"IP_MODULO");
	config_discordiador->PUERTO_MODULO = config_get_int_value(config,"PUERTO_MODULO");
	config_discordiador->IP_MI_RAM_HQ = config_get_string_value(config,"IP_MI_RAM_HQ");
	config_discordiador->PUERTO_MI_RAM_HQ = config_get_int_value(config,"PUERTO_MI_RAM_HQ");
	config_discordiador->IP_I_MONGO_STORE = config_get_string_value(config,"IP_I_MONGO_STORE");
	config_discordiador->PUERTO_I_MONGO_STORE = config_get_int_value(config,"PUERTO_I_MONGO_STORE");
	config_discordiador->GRADO_MULTITAREA = config_get_int_value(config,"GRADO_MULTITAREA");
	
	//Mapea el string a un int para el atributo algoritmo
	if(strcmp("FIFO",config_get_string_value(config, "ALGORITMO")) == 0){
		config_discordiador->ALGORITMO = FIFO;
	} else{
		config_discordiador->ALGORITMO = RR;
	}

	config_discordiador->QUANTUM = config_get_int_value(config,"QUANTUM");
	config_discordiador->DURACION_SABOTAJE = config_get_int_value(config,"DURACION_SABOTAJE");
	config_discordiador->RETARDO_CICLO_CPU = config_get_int_value(config,"RETARDO_CICLO_CPU");
	config_discordiador->ARCHIVO_LOG= config_get_string_value(config,"ARCHIVO_LOG");
	
	return config_discordiador;
}
