#include "server.h"

void *recepcionMensaje(t_package paquete, int cliente_fd, t_log *logger)
{
    log_info(logger, "recibo algo %d", paquete.cod_operacion);
    //Deserializacion
    t_package new_paquete;
    //Tarea* tarea2;
    switch (paquete.cod_operacion)
    {
        case 0:
            exit;
        break;
        case TAREA: 
            //tarea2 = deserializar_I_TAREA(paquete);
            //mostrarTarea(tarea2);
            break;
        case 56: //Inicio de fsck 
            init_protocolo_fsck();
            break;
        case 4: //Preguntar archivo y devolver 
            break;
        case 5: //Preguntar bitacora y devolver 
            break;
    }

    return NULL;
}

void ejecutar_operacion(int cliente_fd)
{
    while (1)
    {
        t_package paquete = recibir_mensaje(cliente_fd);
        if (paquete.cod_operacion > 0 && paquete.cod_operacion < 100)
        {

            recepcionMensaje(paquete, cliente_fd, logger);
            if (paquete.cod_operacion == 0)
                exit;
        }
        else
        {
            break;
        }
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
			pthread_create(&hilo_client_tripulante, NULL, (void *)ejecutar_operacion, (void *)socket_client_tripulante);
			pthread_detach(hilo_client_tripulante);
		}
	}

	liberar_conexion(socket_server);
}