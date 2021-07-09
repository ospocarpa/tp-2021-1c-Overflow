#include "../include/server_utils.h"

int iniciar_servidor(int PUERTO)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	char *port = string_itoa(PUERTO);

	getaddrinfo(NULL, port, &hints, &servinfo); // NULL representa la ip local

	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
			continue;

		if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(socket_servidor);
			continue;
		}
		break;
	}

	listen(socket_servidor, SOMAXCONN);
	free(port);
	freeaddrinfo(servinfo);

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	struct sockaddr_in dir_cliente;
	socklen_t tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void *)&dir_cliente, &tam_direccion);

	return socket_cliente;
}

int recibir_operacion(int socket_cliente, t_log *logger)
{
	int cod_op;
	if (recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void *recibir_buffer(int *size, int socket_cliente, t_log *logger)
{
	void *buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

t_package recibir_mensaje(int socket_cliente)
{
	t_package paquete;

	int state = 0;
	state = recv(socket_cliente, &(paquete.cod_operacion), sizeof(op_code), MSG_WAITALL);
	if(state == 0){
		paquete.cod_operacion = 0;
		return paquete;
	}
	//printf("State cod operacion: %d\n", state);
	state = recv(socket_cliente, &(paquete.tam_buffer), sizeof(int), MSG_WAITALL);
	//printf("State tam buffer: %d\n", state);
	paquete.buffer= malloc(paquete.tam_buffer);
	state = recv(socket_cliente, paquete.buffer, paquete.tam_buffer, MSG_WAITALL);
	//printf("State buffer: %d\n", state);

	//printf("Cod operacion: %d\n", paquete.cod_operacion);
	//printf("Buffer: %d\n", paquete.tam_buffer);
	
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
t_list *recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void *buffer;
	t_list *valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente, NULL);
	while (desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento += sizeof(int);
		char *valor = malloc(tamanio);
		memcpy(valor, buffer + desplazamiento, tamanio);
		desplazamiento += tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
	return NULL;
}
