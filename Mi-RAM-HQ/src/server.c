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

		/*
		int cant_tripulantes;
		char * tareas;
		int long_tareas;
		int long_posicion;
		char * posiciones;
		uint32_t patota_id;
		uint32_t id_primer_tripulante;
		*/
		init_patota = des_cod_iniciar_patota(paquete);
		mostrar_iniciar_patota(init_patota);

		//se envia un booleano de confirmacion
		bool respuesta = true;

		respuesta = iniciar_patota(init_patota);
		send(tripulante, &respuesta, sizeof(respuesta), 0);

		break;

	case EXPULSAR_TRIPULANTE:
		logger_info("EXPULSAR TRIPULANTES");
		/* interpreto el contenido del mensaje */
		ex_tripulante = des_cod_expulsar_tripulante(paquete);
		//mi funcion expulsar tripulante
		//printf("Tripulante: %d\n", ex_tripulante.id_tripulante);
		expulsar_tripulante(ex_tripulante);
		eliminar_tripulante(ex_tripulante.tripulante_id);
		break;

	case INFORMAR_TAREA_TRIPULANTE:
		logger_info("INFORMAR TAREA");
		/* interpreto el contenido del mensaje */
		tripulante_info = des_cod_informar_tarea_tripulante(paquete);
		mostrar_short_info_tripulante(tripulante_info);
		
		char* tareas = get_tareas(tripulante_info.patota_id);
		tcb = get_TCB(tripulante_info.patota_id, tripulante_info.tripulante_id);
		tarea = get_tarea(tareas, tcb.prox_tarea);
		tcb.prox_tarea++;
		set_tripulante(tcb, tripulante_info.patota_id);

		//un ejemplo de tarea(despues borrar)
		/*tarea.tarea = OTRA_TAREA;
		tarea.tiempo = 5;
		tarea.posicion.posx = 3;
		tarea.posicion.posy = 4;
		tarea.parametro = 5;*/
		//Pendiente set_tripulante

		/* serializo la respuesta al tripulante */
		paquete_res = ser_res_informar_tarea_tripulante(tarea);
		/* envio respuesta */
		sendMessage(paquete_res, tripulante);
		break;

	case INFORMAR_POSICION_TRIPULANTE:
		informe_tripulante = des_res_informar_posicion_tripulante(paquete);
		tcb = get_TCB(informe_tripulante.patota_id, informe_tripulante.tripulante_id);

		actualizar_tripulante(tcb, informe_tripulante.posicion.posx, informe_tripulante.posicion.posy);

		tcb.posx = informe_tripulante.posicion.posx;
    	tcb.posy = informe_tripulante.posicion.posy;
		set_tripulante(tcb, informe_tripulante.patota_id);
		break;

	case INFORMAR_ESTADO_TRIPULANTE:
		estado_tripulante = des_cod_informar_estado(paquete);
		tcb = get_TCB(estado_tripulante.patota_id, estado_tripulante.tripulante_id);
		tcb.estado = map_estado(estado_tripulante.status);
		set_tripulante(tcb, estado_tripulante.patota_id);
		break;

	default:
		//logger_error("No existe operacion");
		break;
	}
}

void actualizar_tripulante(t_TCB tcb, int posx, int posy){
	int valor_x = posx - tcb.posx;
	int valor_y = posy - tcb.posy;
	desplazar_tripulante(tcb.tid, valor_x, valor_y);
}

void server_mi_ram_iniciar(int puerto)
{
	//init_renderizacion_mapa();
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