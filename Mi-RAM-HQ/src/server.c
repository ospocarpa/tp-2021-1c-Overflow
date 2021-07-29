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
	t_informar_posicion_tripulante informe_tripulante;
	t_TCB tcb;

	/* INFORMAR ESTADO*/
	t_estado_tripulante estado_tripulante;

	paquete = recibir_mensaje(tripulante);

	switch (paquete.cod_operacion)
	{
	case INICIAR_PATOTA:
		logger_info("INICIAR PATOTA");
		/* interpreto el contenido del mensaje */
		init_patota = des_cod_iniciar_patota(paquete);
		//printf("Posiciones: %s\n", init_patota.posiciones);
		//mi funcion iniciar patota
		

		//se envia un booleano de confirmacion
		bool respuesta = true;

		respuesta = iniciar_patota_segmentacion(init_patota);

		send(tripulante, &respuesta, sizeof(respuesta), 0);

		break;

	case EXPULSAR_TRIPULANTE:
		logger_info("EXPULSAR TRIPULANTES");
		/* interpreto el contenido del mensaje */
		ex_tripulante = des_cod_expulsar_tripulante(paquete);
		//mi funcion expulsar tripulante
		printf("Tripulante: %d\n", ex_tripulante.id_tripulante);
		break;

	case INFORMAR_TAREA_TRIPULANTE:
		logger_info("INFORMAR TAREA");
		/* interpreto el contenido del mensaje */
		tripulante_info = des_cod_informar_tarea_tripulante(paquete);
		char* tareas = string_new();
		tcb = get_TCB(tripulante_info.patota_id, tripulante_info.tripulante_id);
		//tarea = ; mi funcion que devuelve una tarea

		//un ejemplo de tarea(despues borrar)
		tarea.tarea = OTRA_TAREA;
		tarea.tiempo = 5;
		tarea.posicion.posx = 3;
		tarea.posicion.posy = 4;
		tarea.parametro = 5;

		/* serializo la respuesta al tripulante */
		paquete_res = ser_res_informar_tarea_tripulante(tarea);
		/* envio respuesta */
		sendMessage(paquete_res, tripulante);
		break;

	case INFORMAR_POSICION_TRIPULANTE:
		informe_tripulante = des_res_informar_posicion_tripulante(paquete);
		tcb = get_TCB(informe_tripulante.patota_id, informe_tripulante.tripulante_id);
		tcb.posx = informe_tripulante.posicion.posx;
    	tcb.posy = informe_tripulante.posicion.posy;
		//Pendiente set_tripulante
		break;

	case INFORMAR_ESTADO_TRIPULANTE:
		estado_tripulante = des_cod_informar_estado(paquete);
		tcb = get_TCB(estado_tripulante.patota_id, estado_tripulante.tripulante_id);
		tcb.estado = map_estado(estado_tripulante.status);
		//Pendiente set_tripulante
		break;

	default:
		//logger_error("No existe operacion");
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