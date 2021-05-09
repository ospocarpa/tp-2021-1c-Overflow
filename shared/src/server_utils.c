#include "../include/server_utils.h"

int iniciar_servidor(int PUERTO, t_log* logger)
{
	int socket_servidor;

    // struct addrinfo hints, *servinfo, *p;

    // memset(&hints, 0, sizeof(hints));
    // hints.ai_family = AF_UNSPEC;
    // hints.ai_socktype = SOCK_STREAM;
    // hints.ai_flags = AI_PASSIVE;

	//IP = NULL;
    // getaddrinfo(IP, PUERTO, &hints, &servinfo);

    // for (p=servinfo; p != NULL; p = p->ai_next)
    // {
    //     if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
    //         continue;

    //     if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
    //         close(socket_servidor);
    //         continue;
    //     }
    //     break;
    // }

	// listen(socket_servidor, SOMAXCONN);

    // freeaddrinfo(servinfo);

    //log_trace(logger, "Listo para escuchar a mi cliente");

	struct sockaddr_in data_server;

	data_server.sin_family = AF_INET;
	data_server.sin_addr.s_addr = INADDR_ANY; //es para indicar IP, si hay alaguna especifica se puede usar asi inet_addr("127.0.0.1")
	data_server.sin_port = htons(PUERTO);

	memset(&data_server, 0, sizeof(data_server));

	socket_servidor = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_servidor == -1)
	{
		perror("[SERVER] - ERROR: No se pudo crear el socket servidor");
		return -1;
	}

	int value_true = 1;
	setsockopt(socket_servidor,SOL_SOCKET,SO_REUSEADDR,&value_true,sizeof(value_true)); // permite que el bind no falle si se cierra el servidor 

	if (bind(socket_servidor, (void *)&data_server, sizeof(data_server)) != 0)
	{
		perror("[SERVER] - ERROR: Fallo bind. Puede que el puerto no este disponible");
		return -2;
	}

	if(listen(socket_servidor, SOMAXCONN) == -1){
		perror("[SERVER] - ERROR: Servidor no escucha");
		return -3;
	}
	
    return socket_servidor;
}

int esperar_cliente(int socket_servidor, t_log* logger)
{
	struct sockaddr_in dir_cliente;
	socklen_t tam_direccion = sizeof(struct sockaddr_in);
	
	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

	//printf("Se conecto un cliente!\n");
	//log_info(logger, "Se conecto un cliente!");
	
	return socket_cliente;
}

int recibir_operacion(int socket_cliente, t_log* logger)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void* recibir_buffer(int* size, int socket_cliente, t_log* logger)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

t_paquete* recibir_mensaje(int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->buffer = malloc(sizeof(t_buffer));

	recv(socket_cliente, &(paquete->codigo_operacion), sizeof(uint32_t), MSG_WAITALL);
	recv(socket_cliente, &(paquete->from_client), sizeof(bool), MSG_WAITALL);
	recv(socket_cliente, &(paquete->buffer->size), sizeof(uint32_t), MSG_WAITALL);
	paquete->buffer->stream = malloc(paquete->buffer->size);
	recv(socket_cliente, paquete->buffer->stream, paquete->buffer->size, MSG_WAITALL);

	// Primero recibimos el codigo de operacion
	/*if(recv(socket_cliente, &(paquete->codigo_operacion), sizeof(int), MSG_WAITALL) == -1)
		paquete->codigo_operacion = -1;*/

	/*if(paquete->codigo_operacion > 0){
		// Después ya podemos recibir el buffer. Primero su tamaño seguido del contenido
		recv(socket_cliente, &(paquete->buffer->size), sizeof(uint32_t), 0);
		paquete->buffer->stream = malloc(paquete->buffer->size);
		recv(socket_cliente, paquete->buffer->stream, paquete->buffer->size, 0);
	}*/
	return paquete;
}

//podemos usar la lista de valores para poder hablar del for y de como recorrer la lista
t_list* recibir_paquete(int socket_cliente, t_log* logger)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente,logger);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
	return NULL;
}

char *test()
{
    return "Hola mundo";
}
