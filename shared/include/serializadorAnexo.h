/*
 * Description: Serializador de los struct centrales de TADAnexo.h */

#ifndef SERIALIZADOR_ANEXO_H
#define SERIALIZADOR_ANEXO_H

#include "TAD.h"
#include "TADAnexo.h"
#include <stdlib.h>
#include <string.h>

	t_paquete* serializar_pedido_ID(t_pedidoID* datos, int opcode);
	t_paquete* serializar_pedido_ID_With_Restaurant(t_pedidoID_With_Restaurant* datos, int opcode);
	t_paquete* serializar_pedido(t_pedido* datos, int opcode);
    
#endif /* SERIALIZADOR_ANEXO_H */