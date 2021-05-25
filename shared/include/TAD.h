#ifndef TAD_H_
#define TAD_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <semaphore.h>

	typedef enum
	{
		SALIDA = 0,
		TAREA = 1,
		SABOTAJE = 2,
		FIN_FSCKa = 3,
		INICIAR_PATOTA = 4,
		LISTAR_TRIPULANTES = 5,
		EXPULSAR_TRIPULANTE = 6,
		INFORMAR_TAREA_TRIPULANTE = 7,
		INFORMAR_POSICION_TRIPULANTE = 8
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

	typedef struct 
	{
		int cant_tripulantes;
		int long_path_tareas;
		char * path_tareas;
		int long_posicion;
		char * posiciones;
	}t_iniciar_patota;
	

//---------------------- Comunicacion con Mongo -> Discordiador ----------------------

	// Sabotaje 
	typedef struct{
		int mensaje_length;
		char* mensaje;

	// bool = false ---> para ver el mensaje que se envia 
	// puede servir para avisar cuando empezo y termino en todo caso 
	// Pos 	
	// La pregunta sucede ambos sabotajes al mismo tiempo o se tiene que saber cual de los dos se ejecutan ? 	
	// 1 sabotaje de superbloque
	// 2 sabotaje en files 
	// 3 Sabotaje en bloques 
		Posicion*  posicion;	 
	}Sabotaje; 

// Son un struct cada tipo de sabotaje??
// 
// o los tomo todo dentro del mismo ver si tiene la misma logica 

	// typedef struct{

	// }Fin_fsck;

#endif /* TAD_H_ */
