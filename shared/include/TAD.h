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

	typedef enum
	{
		NEW,
		READY,
		EXEC,
		BOCK,
		EXIT	
	} status_tripulante;

	typedef enum
	{
		GENERAR_OXIGENO,
		GENERAR_COMIDA,
		CONSUMIR_COMIDA,
		GENERAR_BASURA,
		DESCARTAR_BASURA,
		OTRA_TAREA
	} type_task;

	typedef struct
	{
		uint32_t size;
		void *stream;
	} t_buffer;

	typedef struct
	{
		op_code codigo_operacion;
		t_buffer* buffer;
	} t_paquete;

	typedef struct
	{
		op_code cod_operacion;
		int tam_buffer;
		void * buffer;
	} t_package;

	typedef struct
	{
		int posx;
		int posy;
	}__attribute__((packed))
	Posicion;

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
		int long_tareas;
		char * tareas;
		int long_posicion;
		char * posiciones;
	}t_iniciar_patota;

	typedef struct 
	{
		uint32_t patota_id;
		uint32_t tripulante_id;
		Posicion posicion;
		status_tripulante status;
	}__attribute__((packed))
	t_tripulante;
	
	typedef struct{
		int cant_tripulantes;
		t_list * tripulantes; //estructura de tripulantes
	}t_listar_tripulantes;

	typedef struct{
		int id_tripulante;
	}t_expulsar_tripulante;

	typedef struct{
		uint32_t patota_id;
		uint32_t tripulante_id;
	}__attribute__((packed))
	t_short_info_tripulante;

	typedef struct{
		type_task tarea;
		int parametro;
		Posicion posicion;
		int tiempo;	
	}t_info_tarea;
	
	typedef struct{
		uint32_t patota_id;
		uint32_t tripulante_id;
		Posicion posicion;
	}__attribute__((packed))
	t_informar_posicion_tripulante;

	

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
