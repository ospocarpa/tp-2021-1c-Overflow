#include "tests_obtener_pedido.h"


void test_serializar_input_obtener_pedido(){
    t_pedidoID_With_Restaurant* I_OBTENER_PEDIDO = malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    I_OBTENER_PEDIDO->pedidoID = 1;

    //nombreDeRes_length
    //nombreDeRes
    I_OBTENER_PEDIDO->nombreDeRes="Restaurante1";
    I_OBTENER_PEDIDO->nombreDeRes_length=strlen(I_OBTENER_PEDIDO->nombreDeRes);
    //Lo serializo
    paquete =  serializar_I_OBTENER_PEDIDO(I_OBTENER_PEDIDO);

    //Genero una nueva variable
    t_pedidoID_With_Restaurant* I_OBTENER_PEDIDO2 = malloc(sizeof(t_pedidoID_With_Restaurant));
    //Deserializo en esa variable
    I_OBTENER_PEDIDO2 = deserializar_I_OBTENER_PEDIDO(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(I_OBTENER_PEDIDO->pedidoID, I_OBTENER_PEDIDO2->pedidoID );
    CU_ASSERT_EQUAL(I_OBTENER_PEDIDO->nombreDeRes_length, I_OBTENER_PEDIDO2->nombreDeRes_length );
    CU_ASSERT_STRING_EQUAL(I_OBTENER_PEDIDO->nombreDeRes, I_OBTENER_PEDIDO2->nombreDeRes);
}


void test_serializar_output_pedido(){
    t_pedido* pedido = malloc(sizeof(t_pedido));
    t_paquete* paquete = malloc(sizeof(t_paquete));


    /*
    estado_pedido estado_Actual;
    uint32_t cantPlatos;
    t_list* platos;					// list [t_plato] pero usando solo el nombre
    uint32_t cantCantPlatos;
    t_list* cantidad_Platos; 		// list [int]
    uint32_t cantCantLista;
    t_list* cantidad_Lista;			// list [int]
    uint32_t precio_Total;

    */
   pedido->estado_Actual=CONFIRMADO;
   pedido->cantPlatos=3;

    pedido->platos = list_create();
    for(int c=0; c<pedido->cantPlatos; c++){
        t_plato* plato = malloc(sizeof(t_plato));
        plato->nombre = "Plato1";
        plato->nombre_length = strlen(plato->nombre);
        list_add(pedido->platos, plato);
    }

    pedido->cantidad_Platos = list_create();
    pedido->cantCantPlatos=3;

    for(int c=0; c<pedido->cantCantPlatos; c++){
        int plato = 5;
        list_add(pedido->cantidad_Platos, plato);
    }

    pedido->cantidad_Lista = list_create();
    pedido->cantCantLista=3;
    for(int c=0; c<pedido->cantCantLista; c++){
        int lista = 3;
        list_add(pedido->cantidad_Lista, lista);
    }

    pedido->precio_Total=30;

    paquete =  serializar_output_pedido(pedido);



//Genero una nueva variable
    t_pedido* pedido2 = malloc(sizeof(t_pedido));
    //Deserializo en esa variable
    pedido2 = deserializar_output_pedido(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(pedido->precio_Total, pedido2->precio_Total );
    CU_ASSERT_EQUAL(pedido->cantPlatos, pedido2->cantPlatos );
    CU_ASSERT_EQUAL(pedido->cantCantPlatos, pedido2->cantCantPlatos );
    CU_ASSERT_EQUAL(pedido->cantCantLista, pedido2->cantCantLista );


    for(int c=0; c<pedido->cantPlatos; c++){
        t_plato* plato1 = list_get(pedido->platos, c);
        t_plato* plato2 = list_get(pedido2->platos, c);
        CU_ASSERT_STRING_EQUAL(plato1->nombre, plato2->nombre );
        CU_ASSERT_EQUAL(plato1->nombre_length, plato2->nombre_length );
    }
  

    for(int c=0; c<pedido->cantCantPlatos; c++){
        int plato1 = list_get(pedido->cantidad_Platos, c);
        int plato2 = list_get(pedido->cantidad_Platos, c);
        CU_ASSERT_EQUAL(plato1, plato2 );
    }
    for(int c=0; c<pedido->cantCantLista; c++){
        int lista1 = list_get(pedido->cantidad_Lista, c);
        int lista2 = list_get(pedido->cantidad_Lista, c);
        CU_ASSERT_EQUAL(lista1, lista2 );
    }
    
/*
	typedef struct {
		estado_pedido estado_Actual;
		uint32_t cantPlatos;
		t_list* platos;					// list [t_plato] pero usando solo el nombre
		uint32_t cantCantPlatos;
		t_list* cantidad_Platos; 		// list [int]
		uint32_t cantCantLista;
		t_list* cantidad_Lista;			// list [int]
		uint32_t precio_Total;
	} t_pedido;
*/


    //CU_ASSERT_EQUAL(pedido2->nombreDeRes_length, pedido2->nombreDeRes_length );
    //CU_ASSERT_STRING_EQUAL(pedido2->nombreDeRes, pedido2->nombreDeRes );

//t_pedido* deserializar_output_pedido(t_paquete* paquete);
//CU_ASSERT_EQUAL(2+2, 4);
}


