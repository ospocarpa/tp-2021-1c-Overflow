#ifndef TADAnexo_H_
#define TADAnexo_H_
#include <netdb.h>
#include <commons/collections/list.h>
#include <commons/log.h>
#include <TAD.h>

typedef struct
{
	uint32_t pedidoID;
} t_pedidoID;

typedef struct
{
	uint32_t pedidoID;
	uint32_t nombreDeRes_length;
	char *nombreDeRes;
} t_pedidoID_With_Restaurant;

typedef struct
{
	uint32_t pedidoID;
	uint32_t nombreDeRes_length;
	char *nombreDeRes;
	uint32_t plato_length;
	char *plato;
} t_I_PLATO_LISTO;

typedef struct
{
	uint32_t pedidoID;
	uint32_t nombreDeRes_length;
	char *nombreDeRes;
	uint32_t plato_length;
	char *plato;
	uint32_t cantidad;
} t_I_GUARDAR_PLATO;

typedef struct
{
	uint32_t pedidoID;
	t_plato *plato;
} t_I_ANADIR_PLATO;

#endif /* TADAnexo_H_ */
