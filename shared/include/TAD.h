#ifndef TAD_H_
#define TAD_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <semaphore.h>

  typedef enum
	{
		SALIR = 0, //SALIDA
		TAREA = 1,
		SABOTAJE = 2,
		FIN_FSCK = 3,
		INICIAR_PATOTA = 4,
		LISTAR_TRIPULANTES = 5,
		EXPULSAR_TRIPULANTE = 6,
		INFORMAR_TAREA_TRIPULANTE = 7,
		INFORMAR_POSICION_TRIPULANTE = 8,
		INICIAR_PLANIFICACION = 9,
		PAUSAR_PLANIFICACION = 10,
		OBTENER_BITACORA = 11,
    INFORMAR_ESTADO_TRIPULANTE = 12,
		CREAR_BITACORA = 13,
		CREAR_RECURSO = 14,
		GET_BITACORA = 15,
		GET_RECURSO = 16,
		UPDATE_BITACORA = 17,
		AGREGAR_RECURSO = 18,
		RETIRAR_RECURSO = 19,
		ELIMINAR_RECURSO = 20
	} op_code;

	typedef enum
	{
		NEW,
		READY,
		EXEC,
		BLOCKED,
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
		char * tareas;
		int long_tareas;
		int long_posicion;
		char * posiciones;
		uint32_t patota_id;
		uint32_t id_primer_tripulante;
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

  // Usado para crear un archivo (recurso o bitácora)
	typedef struct{
		char caracter;				//Si es de tipo recurso tendrá su valor definido. Para la bitácorda
		uint32_t long_nombre_file;
		char* nombre_file;
	} t_create_file;

  typedef struct{
		uint32_t patota_id;
		uint32_t tripulante_id;
		status_tripulante status;
	}__attribute__((packed))
	t_estado_tripulante;

  // Sabotaje
  typedef struct
  {
    int mensaje_length;
    char *mensaje;

    // bool = false ---> para ver el mensaje que se envia
    // puede servir para avisar cuando empezo y termino en todo caso
    // Pos
    // La pregunta sucede ambos sabotajes al mismo tiempo o se tiene que saber cual de los dos se ejecutan ?
    // 1 sabotaje de superbloque
    // 2 sabotaje en files
    // 3 Sabotaje en bloques
    Posicion *posicion;
  } Sabotaje;

	// Usado para obtener un archivo y modificar una bitácora. El contenido será distinto si el tipo es de bitácora o recurso
	typedef struct{
		uint32_t long_contenido;
		char* contenido;
		uint32_t long_nombre_file;
		char* nombre_file;
	} t_file;

	typedef struct{
		uint32_t cantidad;
		char caracter;
		uint32_t long_nombre_file;
		char* nombre_file;
	} t_operation_file_recurso;
	//---------------------- Comunicacion con Mongo -> Discordiador ----------------------

	// Sabotaje
	typedef struct
	{
		int mensaje_length;
		char *mensaje;

		// bool = false ---> para ver el mensaje que se envia
		// puede servir para avisar cuando empezo y termino en todo caso
		// Pos
		// La pregunta sucede ambos sabotajes al mismo tiempo o se tiene que saber cual de los dos se ejecutan ?
		// 1 sabotaje de superbloque
	// 2 sabotaje en files
		// 3 Sabotaje en bloques
		Posicion *posicion;
	} t_sabotaje;
	// Son un struct cada tipo de sabotaje??
	//
	// o los tomo todo dentro del mismo ver si tiene la misma logica

	// typedef struct{

	// }Fin_fsck;

#endif /* TAD_H_ */
