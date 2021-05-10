#include "server.h"

static void *ejecutar_operacion(int client)
{
	char * mensaje = malloc(4);
	//aca van los mensajes que envia discordiador

	//ejemplo, luego eliminar
	int res = recv(client, mensaje, 4, 0);
	mensaje[4]='\0';
	logger_info("Mensaje: %s", mensaje);

	//

	free(mensaje);
}

void server_mi_ram_iniciar(int puerto)
{
	int socket_server;
	int socket_client_tripulante;
	pthread_t hilo_client_tripulante;

	logger_info("Iniciar servidor");

	socket_server = iniciar_servidor(puerto);
	if(socket_server < 0)
	{
		perror("Server MI-RAM-HQ no creado:");
	}

	logger_info("Server MI-RAM-HQ N° [%d] esperando clientes", socket_server);

	while(1)
	{
		socket_client_tripulante = esperar_cliente(socket_server);
		
		if (socket_client_tripulante != -1)
		{
			logger_info("Se conecto el tripulante [%d]", socket_client_tripulante);
			pthread_create(&hilo_client_tripulante, NULL, (void *)ejecutar_operacion, (void *)socket_client_tripulante);
			pthread_detach(hilo_client_tripulante);
		}
	}

	liberar_conexion(socket_server);
}