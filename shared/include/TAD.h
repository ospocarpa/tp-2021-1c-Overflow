#ifndef TAD_H_
#define TAD_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <semaphore.h>

typedef enum
{
	SALIDA = 0
} op_code;

typedef struct
{
	uint32_t size;
	void *stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer *buffer;
	bool from_client;
} t_paquete;



#endif /* TAD_H_ */
