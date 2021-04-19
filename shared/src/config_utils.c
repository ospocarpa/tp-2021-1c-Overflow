#include "../include/config_utils.h"



t_config * leer_config_file(char* configName)
{
	//ahora, vamos a abrir el archivo de configuracion "tp0.config"
	t_config * g_config = config_create(configName);

	return g_config;
}

//TODO: AJUSTAR TIPOS DE REGISTROS
t_config_app* leerConfigApp(t_config* config)
{
	t_config_app* config_app = malloc(sizeof(t_config_app));
	config_app->IP_COMANDA= config_get_string_value(config,"IP_COMANDA");
	config_app->PUERTO_COMANDA= config_get_int_value(config,"PUERTO_COMANDA");
	config_app->IP_RESTAURANTE= config_get_string_value(config,"IP_RESTAURANTE");
	config_app->PUERTO_RESTAURANTE= config_get_int_value(config,"PUERTO_RESTAURANTE");
	config_app->PUERTO_ESCUCHA= config_get_int_value(config,"PUERTO_ESCUCHA");
	config_app->RETARDO_CICLO_CPU = config_get_int_value(config,"RETARDO_CICLO_CPU");
	config_app->GRADO_DE_MULTIPROCESAMIENTO= config_get_int_value(config,"GRADO_DE_MULTIPROCESAMIENTO");
	if(strcmp("FIFO",config_get_string_value(config, "ALGORITMO_DE_PLANIFICACION")) == 0){
		config_app->ALGORITMO_DE_PLANIFICACION = FIFO;
	} else if(strcmp("HRRN",config_get_string_value(config, "ALGORITMO_DE_PLANIFICACION")) == 0){
		config_app->ALGORITMO_DE_PLANIFICACION = HRRN;
	} else if(strcmp("SJF_SD",config_get_string_value(config, "ALGORITMO_DE_PLANIFICACION")) == 0){
		config_app->ALGORITMO_DE_PLANIFICACION = SJF_SD;
	};
	config_app->ALPHA= config_get_double_value(config,"ALPHA");
	config_app->ESTIMACION_INICIAL= config_get_int_value(config,"ESTIMACION_INICIAL");
	config_app->REPARTIDORES= config_get_string_value(config,"REPARTIDORES");
	config_app->FRECUENCIA_DE_DESCANSO= config_get_string_value(config,"FRECUENCIA_DE_DESCANSO");
	config_app->TIEMPO_DE_DESCANSO= config_get_string_value(config,"TIEMPO_DE_DESCANSO");
	config_app->ARCHIVO_LOG= config_get_string_value(config,"ARCHIVO_LOG");
	config_app->PLATOS_DEFAULT= config_get_string_value(config,"PLATOS_DEFAULT");
	config_app->POSICION_REST_DEFAULT_X= config_get_int_value(config,"POSICION_REST_DEFAULT_X");
	config_app->POSICION_REST_DEFAULT_Y= config_get_int_value(config,"POSICION_REST_DEFAULT_Y");
	return config_app;
}
t_config_cliente* leerConfigCliente(t_config* config)
{
	t_config_cliente* config_cliente = malloc(sizeof(t_config_cliente));
	config_cliente->IP= config_get_string_value(config,"IP");
	config_cliente->PUERTO= config_get_int_value(config,"PUERTO");
	config_cliente->IP_CLIENTE= config_get_string_value(config,"IP_CLIENTE");
	config_cliente->ID_CLIENTE= config_get_string_value(config,"ID_CLIENTE");
	config_cliente->ARCHIVO_LOG= config_get_string_value(config,"ARCHIVO_LOG");
	config_cliente->POSICION_X= config_get_int_value(config,"POSICION_X");
	config_cliente->POSICION_Y= config_get_int_value(config,"POSICION_Y");
	return config_cliente;
}
t_config_comanda* leerConfigComanda(t_config* config)
{
	t_config_comanda* config_comanda = malloc(sizeof(t_config_comanda));
	config_comanda->TAMANIO_SWAP= config_get_int_value(config,"TAMANIO_SWAP");
	config_comanda->TAMANIO_MEMORIA= config_get_int_value(config,"TAMANIO_MEMORIA");
	config_comanda->PUERTO_ESCUCHA= config_get_int_value(config,"PUERTO_ESCUCHA");
	config_comanda->FRECUENCIA_COMPACTACION= config_get_int_value(config,"FRECUENCIA_COMPACTACION");
	if(strcmp("LRU",config_get_string_value(config, "ALGORITMO_REEMPLAZO")) == 0){
		config_comanda->ALGORITMO_REEMPLAZO = LRU;
	} else if(strcmp("CLOCK",config_get_string_value(config, "ALGORITMO_REEMPLAZO")) == 0){
		config_comanda->ALGORITMO_REEMPLAZO = CLOCK;
	};
	config_comanda->ARCHIVO_LOG= config_get_string_value(config,"ARCHIVO_LOG");
	return config_comanda;
}
t_config_restaurante* leerConfigRestaurante(t_config* config)
{
	t_config_restaurante* config_restaurante = malloc(sizeof(t_config_restaurante));
	config_restaurante->PUERTO_ESCUCHA= config_get_int_value(config,"PUERTO_ESCUCHA");
	config_restaurante->IP_SINDICATO= config_get_string_value(config,"IP_SINDICATO");
	config_restaurante->PUERTO_SINDICATO= config_get_int_value(config,"PUERTO_SINDICATO");
	config_restaurante->IP_APP= config_get_string_value(config,"IP_APP");
	config_restaurante->PUERTO_APP= config_get_int_value(config,"PUERTO_APP");
	config_restaurante->QUANTUM= config_get_int_value(config,"QUANTUM");
	config_restaurante->ARCHIVO_LOG= config_get_string_value(config,"ARCHIVO_LOG");
	config_restaurante->RETARDO_CICLO_CPU = config_get_int_value(config,"RETARDO_CICLO_CPU");
	if(strcmp("FIFO",config_get_string_value(config, "ALGORITMO_PLANIFICACION")) == 0){
		config_restaurante->ALGORITMO_PLANIFICACION = FIFO;
	} else if(strcmp("HRRN",config_get_string_value(config, "ALGORITMO_PLANIFICACION")) == 0){
		config_restaurante->ALGORITMO_PLANIFICACION = HRRN;
	}
	config_restaurante->NOMBRE_RESTAURANTE= config_get_string_value(config,"NOMBRE_RESTAURANTE");

	return config_restaurante;
}
t_config_sindicato* leerConfigSindicato(t_config* config)
{	t_config_sindicato* config_sindicato = malloc(sizeof(t_config_sindicato));

	config_sindicato->PUERTO_ESCUCHA= config_get_int_value(config,"PUERTO_ESCUCHA");
	config_sindicato->PUNTO_MONTAJE= config_get_string_value(config,"PUNTO_MONTAJE");
	config_sindicato->BLOCK_SIZE= config_get_int_value(config,"BLOCK_SIZE");
	config_sindicato->BLOCKS= config_get_int_value(config,"BLOCKS");
	return config_sindicato;

}
