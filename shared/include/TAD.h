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
	I_CONSULTAR_RESTAURANTE = 1,
	O_CONSULTAR_RESTAURANTE = 2,
	I_OBTENER_RESTAURANTE = 3
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

typedef struct
{
	uint32_t nombreDeRes_length;
	char* nombreDeRes;
} t_nombreDeRes;


#endif /* TAD_H_ */
