#ifndef TAD_H_
#define TAD_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <semaphore.h>

	typedef enum
	{
		SALIDA = 0,
		TAREA = 1
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
	} t_paquete;

	typedef struct
	{
		int posx;
		int posy;
	} Posicion;

	typedef struct
	{
		int patota_id;
		char* description;
		int description_length;
		char* parametros;
		int parametros_length;
		int tiempo;
		Posicion* posicion;
	} Tarea;

#endif /* TAD_H_ */
