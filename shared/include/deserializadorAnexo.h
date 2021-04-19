/*
 * Description: Deserializador de los struct centrales de TADAnexo.h */

#ifndef DESERIALIZADOR_ANEXO_H
#define DESERIALIZADOR_ANEXO_H

#include "TAD.h"
#include "TADAnexo.h"
#include <stdlib.h>
#include <string.h>

	t_pedidoID* deserializar_pedido_ID(t_paquete* paquete);
	t_pedidoID_With_Restaurant* deserializar_pedido_ID_With_Restaurant(t_paquete* paquete);
	t_pedido* deserializar_pedido(t_paquete* paquete);
    
#endif /* SERIALIZADOR_ANEXO_H */