#include "server.h"

bool recepcionMensaje(t_package paquete, int cliente_fd, t_log *logger)
{
    bool exist_code = true;
    log_info(logger, "recibo algo %s (%d)", get_string_operacion(paquete.cod_operacion), paquete.cod_operacion);

    //Deserializacion
    t_package paquete_a_enviar;
    
    t_create_file create_get_file;
    t_file file;
    t_file file_a_enviar;
    t_operation_file_recurso operation_file_recurso;

    switch (paquete.cod_operacion)
    {
        case CREAR_RECURSO: 
            printf("Recurso a crear\n");
            create_get_file = des_create_file(paquete);
            mostrar_create_file(create_get_file);
            create_recurso(create_get_file);
            break;
        case CREAR_BITACORA: 
            printf("Bitácora a crear\n");
            create_get_file = des_create_file(paquete);
            mostrar_create_file(create_get_file);
            create_tripulante_bitacora(create_get_file);
            break;
        case GET_RECURSO: 
            printf("Recurso get\n");
            file = des_get_file(paquete);
            mostrar_file(file);

            file_a_enviar = get_recurso(file.nombre_file);
            mostrar_file(file_a_enviar);

            paquete_a_enviar = ser_get_file_recurso(file_a_enviar);
            sendMessage(paquete_a_enviar, cliente_fd);
            break;
        case GET_BITACORA:
            file = des_get_file(paquete);
            mostrar_file(file);

            file_a_enviar = get_bitacora_tripulante(file);
            mostrar_file(file_a_enviar);

            paquete_a_enviar = ser_get_file_bitacora(file_a_enviar);
            sendMessage(paquete_a_enviar, cliente_fd);
            break;
        case UPDATE_BITACORA: 
            printf("Bitácora actualizar\n");
            file = des_update_bitacora(paquete);
            mostrar_update_bitacora(file);

            update_bitacora(file);
            break;
        case AGREGAR_RECURSO: 
            //printf("Agregar recurso\n");
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);

            agregar_recurso(operation_file_recurso);
            break;
        case RETIRAR_RECURSO: 
            //printf("Retirar recurso\n");
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);
            
            retirar_recurso(operation_file_recurso);
            break;
        case ELIMINAR_RECURSO:
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);
            
            eliminar_recurso(operation_file_recurso);
            break;
        case INICIO_FSCK: //Inicio de fsck 
            init_protocolo_fsck();
            
            //Indica finalización del protocolo fsck
            t_aviso_fsck aviso;
            paquete_a_enviar = ser_fin_fcsk(aviso);
            sendMessage(paquete_a_enviar, cliente_fd);
            break;
        default: 
            exist_code = false;
            break;
    }

    return exist_code;
}

void ejecutar_operacion(int cliente_fd)
{
    int fallos = 1;
    while (1)
    {
        t_package paquete = recibir_mensaje(cliente_fd);
        if (
            paquete.cod_operacion == 0 
            //|| (paquete.tam_buffer==0 && (paquete.cod_operacion != FIN_FSCK || paquete.cod_operacion != INICIO_FSCK))
        ) fallos--;
        if(fallos <= 0) break;
        bool existe_codigo = recepcionMensaje(paquete, cliente_fd, logger);
        if (!existe_codigo) fallos--;
        if(fallos <= 0) break;
    }
}

void server_mongo_store_iniciar(int puerto)
{
	int socket_server;
	int socket_client_tripulante;
	pthread_t hilo_client_tripulante;

	log_info(logger, "Iniciar servidor i-Mongo-Store");
	socket_server = iniciar_servidor(puerto);

	if(socket_server < 0)
	{
		perror("Server i-Mongo-Store no creado:");
	}

	log_info(logger, "Server i-Mongo-Store N° [%d] esperando clientes", socket_server);
	while (1)
	{
		socket_client_tripulante = esperar_cliente(socket_server);

		if (socket_client_tripulante != -1)
		{
			log_info(logger, "Se conecto el tripulante [%d]", socket_client_tripulante);
			pthread_create(&hilo_client_tripulante, NULL, (void *)ejecutar_operacion, socket_client_tripulante);
			pthread_detach(hilo_client_tripulante);
		}
	}

	liberar_conexion(socket_server);
}