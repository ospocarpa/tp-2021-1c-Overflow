  
#include "server.h"

static void *ejecutar_operacion(int client)
{

	//aca van los mensajes que le envia discordiador
}

void server_mongo_store_iniciar(char *puerto, char *ip, t_log *log)
{
	int socket_server;
	int socket_client;
	pthread_t hilo_client;

	log_info(log, "Iniciar servidor");

	socket_server = iniciar_servidor(ip, puerto, log);
	log_info(log, "Server i-Mongo-Store N° [%d] esperando clientes", socket_server);

	while (1)
	{
		socket_client = esperar_cliente(socket_server, log);
		if (socket_client != -1)
		{
			log_info(log, "Se conecto el cliente [%d]", socket_client);
			pthread_create(&hilo_client, NULL, (void *)ejecutar_operacion, (void *)socket_client);
			pthread_detach(hilo_client);
		}
		liberar_conexion(socket_client);
	}

	liberar_conexion(socket_server);
}