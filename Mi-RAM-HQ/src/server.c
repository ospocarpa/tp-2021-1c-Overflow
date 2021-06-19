#include "server.h"

static void *ejecutar_operacion(int client)
{
	while (1)
	{
		t_paquete *paquete = recibir_mensaje(client);
		switch (paquete->codigo_operacion)
		{
		case INICIAR_PATOTA:;
			t_iniciar_patota datos_patota;
			datos_patota = deserializar_iniciar_patota(paquete);
			//completar carga de los pcb/tcb
			printf("Completar carga de los pcb/tcb\n");
			break;

		default:
			break;
		}
	}
}

void server_mi_ram_iniciar(int puerto)
{
	int socket_server;
	int socket_client_tripulante;
	pthread_t hilo_client_tripulante;

	logger_info("Iniciar servidor");

	socket_server = iniciar_servidor(puerto);
	if (socket_server < 0)
	{
		perror("Server MI-RAM-HQ no creado:");
	}

	logger_info("Server MI-RAM-HQ N° [%d] esperando clientes", socket_server);

	while (1)
	{
		socket_client_tripulante = esperar_cliente(socket_server);

		if (socket_client_tripulante != -1)
		{
			logger_info("Tengo una conexion,numero de socket[%d]", socket_client_tripulante);
			pthread_create(&hilo_client_tripulante, NULL, (void *)ejecutar_operacion, (void *)socket_client_tripulante);
			pthread_detach(hilo_client_tripulante);
		}
	}

	liberar_conexion(socket_server);
}