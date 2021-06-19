#include "server.h"

static void *ejecutar_operacion(int tripulante)
{
	t_package paquete;
	t_package paquete_res;
	/* INICIAR PATOTA */
	t_iniciar_patota init_patota;
	/* LISTAR TRIPULANTES */
	t_listar_tripulantes tripulantes;
	/* EXPULSAR TRIPULANTE */
	t_expulsar_tripulante ex_tripulante;
	/* INFORMAR TAREA */
	t_short_info_tripulante tripulante_info;
	t_info_tarea tarea;
	/* INFORMAR POSICION */

	paquete = recibir_mensaje(tripulante);

	switch (paquete.cod_operacion)
	{
	case INICIAR_PATOTA:
		logger_info("INICIAR PATOTA");
		/* interpreto el contenido del mensaje */
		init_patota = des_cod_iniciar_patota(paquete);
		//mi funcion iniciar patota
		break;

	case LISTAR_TRIPULANTES:
		logger_info("LISTAR TRIPULANTES");
		/* no deserializo el contenido del mensaje porque me envia la operacion */
		//tripulantes = mi funcion listar tripulantes
		/* serializo la respuesta al tripulante */
		paquete_res = ser_res_listar_tripulantes(tripulantes);
		/* envio respuesta */
		sendMessage(paquete_res, tripulante);
		break;

	case EXPULSAR_TRIPULANTE:
		logger_info("EXPULSAR TRIPULANTES");
		/* interpreto el contenido del mensaje */
		ex_tripulante = des_cod_expulsar_tripulante(paquete);
		//mi funcion expulsar tripulante
		break;

	case INFORMAR_TAREA_TRIPULANTE:
		logger_info("INFORMAR TARAE");
		/* interpreto el contenido del mensaje */
		tripulante_info = des_cod_informar_tarea_tripulante(paquete);
		//tarea = ; mi funcion que devuelve una tarea
		/* serializo la respuesta al tripulante */
		paquete_res = ser_res_informar_tarea_tripulante(tarea);
		/* envio respuesta */
		sendMessage(paquete_res, tripulante);
		break;

	case INFORMAR_POSICION_TRIPULANTE:
		/* code */
		break;
	
	default:
		logger_error("No existe operacion");
		break;
	}
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