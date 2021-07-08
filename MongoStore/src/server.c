#include "server.h"

bool recepcionMensaje(t_package paquete, int cliente_fd, t_log *logger)
{
    bool exist_code = true;
    log_info(logger, "recibo algo %d", paquete.cod_operacion);
    
    //Deserializacion
    t_package new_paquete;
    
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
        case GET_RECURSO:  //Pendiente en devolver
            printf("Recurso get\n");
            file = des_get_file(paquete);
            mostrar_file(file);

            file_a_enviar = get_recurso(file.nombre_file);
            mostrar_file(file_a_enviar);
            break;
        case GET_BITACORA: //Pendiente en devolver
            printf("Bitácora get\n");
            file = des_get_file(paquete);
            mostrar_file(file);

            file_a_enviar = get_bitacora_tripulante(file);
            mostrar_file(file_a_enviar);
            break;
        case UPDATE_BITACORA: //Ver si debe devolver algo
            printf("Bitácora actualizar\n");
            file = des_update_bitacora(paquete);
            mostrar_update_bitacora(file);

            update_bitacora(file);
            break;
        case AGREGAR_RECURSO: 
            printf("Agregar recurso\n");
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);

            agregar_recurso(operation_file_recurso);
            break;
        case RETIRAR_RECURSO: 
            printf("Retirar recurso\n");
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);
            
            retirar_recurso(operation_file_recurso);
            break;
        case ELIMINAR_RECURSO: //PENDIENTE
            printf("Eliminar recurso\n");
            operation_file_recurso = des_operation_file_recurso(paquete);
            mostrar_operation_file_recurso(operation_file_recurso);
            break;
        /*case 56: //Inicio de fsck 
            init_protocolo_fsck();
            break;*/ 
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
        if (paquete.cod_operacion == 0) fallos--;
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