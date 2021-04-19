#ifndef TAD_H_
#define TAD_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <semaphore.h>

typedef enum
{
	CREADO,
	PENDIENTE,	//Hace refencia a la cola de listos
	BLOQUEADO,
	EJECUCION,
	CONFIRMADO, //Sindicato
	TERMINADO
} estado_pedido;

typedef enum
{
	SALIDA = 0,
	I_CONSULTAR_RESTAURANTE = 1,
	O_CONSULTAR_RESTAURANTE = 2,
	I_SELECCIONAR_RESTAURANTE = 3,
	O_SELECCIONAR_RESTAURANTE = 4,
	I_OBTENER_RESTAURANTE = 5,
	O_OBTENER_RESTAURANTE = 6,
	I_CONSULTAR_PLATOS = 7,
	O_CONSULTAR_PLATOS = 8,
	I_CREAR_PEDIDO = 9,
	O_CREAR_PEDIDO = 10,
	I_GUARDAR_PEDIDO = 11,
	O_GUARDAR_PEDIDO = 12,
	I_ANADIR_PLATO = 13,
	O_ANADIR_PLATO = 14,
	I_GUARDAR_PLATO = 15,
	O_GUARDAR_PLATO = 16,
	I_CONFIRMAR_PEDIDO = 17,
	O_CONFIRMAR_PEDIDO = 18,
	I_PLATO_LISTO = 19,
	O_PLATO_LISTO = 20,
	I_CONSULTAR_PEDIDO = 21,
	O_CONSULTAR_PEDIDO = 22,
	I_OBTENER_PEDIDO = 23,
	O_OBTENER_PEDIDO = 24,
	I_FINALIZAR_PEDIDO = 25,
	O_FINALIZAR_PEDIDO = 26,
	I_TERMINAR_PEDIDO = 27,
	O_TERMINAR_PEDIDO = 28,
	I_OBTENER_RECETA = 29,
	O_OBTENER_RECETA = 30,
	RESPUESTA_BOOL = 31,
	INPUT_HANDSHAKE = 42, //Input HandShake
	OUTPUT_HANDSHAKE = 43, //Output HandShake
	RESTAURANTE_TO_APP = 44 
} op_code;

typedef struct
{
	char *estado;
	uint32_t estado_length;
} t_respuesta_bool;

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

typedef struct
{
	uint32_t pos_x;
	uint32_t pos_y;
} t_posicion;

typedef struct
{
	char *nombre;
	uint32_t nombre_length;
	uint32_t tiempo;
} t_paso;

typedef struct
{
	char *nombre;
	uint32_t nombre_length;
	uint32_t precio;
} t_plato;

typedef enum{
	A_ACTIVO,
	A_INACTIVO,
	A_BLOQUEADO
}repartidor_actividad;

typedef struct
{
	int id;
	int x;
	int y;
	int tiempo_descanso;
	int frecuencia_descanso;
	int estimacion;
	repartidor_actividad actividad;
	sem_t recursos_a_consumir;
	sem_t permiso_a_bloquear;
	int destino;		//0 restaurante, 1 cliente
	bool bloqueado_por_frecuencia;
} t_repartidor;

typedef struct
{
	char *nombre;
	uint32_t nombre_length;
	uint32_t cantCocineros;
	t_posicion *posicion;
	uint32_t cantAfinidad;
	t_list *afinidadCocineros; // list [t_afinidad]
	uint32_t cantPlatos;
	t_list *platos; // list [t_plato]
	uint32_t cantHornos;
	uint32_t cantPedidos;
} t_restaurante;

typedef struct
{
	char *nombre;
	uint32_t nombre_length;
} t_afinidad;

typedef struct
{
	char *nombre;
	uint32_t nombre_length;
	uint32_t cantPasos;
	t_list *pasos; // list [t_paso]
} t_receta;

typedef struct
{
	char* restaurante_nombre;
	uint32_t restaurante_nombre_length;
	estado_pedido estado_Actual;
	uint32_t cantPlatos; // CONSIDERAR USAR SOLO ESTE INT PORQUE LAS 3 LISTAS DEBERIAN TENER EL MISMO LARGO y no los demas.
	t_list *platos;		 // list [t_plato] pero usando solo el nombre
	uint32_t cantCantPlatos;
	t_list *cantidad_Platos; // list [int]
	uint32_t cantCantLista;
	t_list *cantidad_Lista; // list [int]
	uint32_t precio_Total;
} t_pedido;

#endif /* TAD_H_ */
