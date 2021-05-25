#include "../include/config_utils.h"

t_config * leer_config_file(char* configName)
{
	t_config * g_config = config_create(configName);
	return g_config;
}

t_config_mongo_store* leer_config_mongo_store(t_config* config){
	t_config_mongo_store* config_mongo_store = malloc(sizeof(t_config_mongo_store));

	config_mongo_store->IP_MODULO = config_get_string_value(config,"IP_MODULO");
	config_mongo_store->PUERTO = config_get_int_value(config,"PUERTO");
	config_mongo_store->PUNTO_MONTAJE = config_get_string_value(config,"PUNTO_MONTAJE");
	config_mongo_store->TIEMPO_SINCRONIZACION = config_get_int_value(config,"TIEMPO_SINCRONIZACION");
	config_mongo_store->POSICIONES_SABOTAJE = config_get_string_value(config,"POSICIONES_SABOTAJE");
	config_mongo_store->ARCHIVO_LOG = config_get_string_value(config,"ARCHIVO_LOG");

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
