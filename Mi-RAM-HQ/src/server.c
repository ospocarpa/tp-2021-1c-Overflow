#include "server.h"

static void *ejecutar_operacion(int client)
{

	//aca van los mensajes que le envia discordiador
}

void server_mi_ram_iniciar(int puerto, char *ip, t_log *log)
{
	int socket_server;
	int socket_client_tripulante;
	pthread_t hilo_client_tripulante;

	logger_info("Iniciar servidor");

	socket_server = iniciar_servidor(puerto, log);
	log_info(log, "Server MI-RAM-HQ N° [%d] esperando clientes", socket_server);

	while(1)
	{
		socket_client_tripulante = esperar_cliente(socket_server, log);
		
		if (socket_client_tripulante != -1)
		{
			log_info(log, "Se conecto el tripulante [%d]", socket_client_tripulante);
			pthread_create(&hilo_client_tripulante, NULL, (void *)ejecutar_operacion, (void *)socket_client_tripulante);
			pthread_detach(hilo_client_tripulante);
		}
	}

	liberar_conexion(socket_server);
}