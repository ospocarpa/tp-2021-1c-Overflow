#include "tests_consultar_pedido.h"

void test_serializar_consultar_pedido(){
    //------------------------------------------------------- INPUT
    t_pedidoID* input = malloc(sizeof(t_pedidoID));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores    
    input->pedidoID = 1;
    //Lo serializo
    paquete =  serializar_input_Consultar_Pedido(input);

    //Genero una nueva variable
    t_pedidoID* input2 = malloc(sizeof(t_pedidoID));
    //Deserializo en esa variable
    input2 = deserializar_input_Consultar_Pedido(paquete);

    //------------------------------------------------------- OUTPUT
    t_pedido* output = malloc(sizeof(t_pedido));
    t_paquete* paquete2 = malloc(sizeof(t_paquete));

    //Cargo Valores    
    output->estado_Actual=CONFIRMADO;
    output->cantPlatos=3;

    output->platos = list_create();
    for(int c=0; c<output->cantPlatos; c++){
        t_plato* plato = malloc(sizeof(t_plato));
        plato->nombre = "Plato1";
        plato->nombre_length = strlen(plato->nombre);
        list_add(output->platos, plato);
    }

    output->cantidad_Platos = list_create();
    output->cantCantPlatos=3;

    for(int c=0; c<output->cantCantPlatos; c++){
        int plato = 5;
        list_add(output->cantidad_Platos, plato);
    }

    output->cantidad_Lista = list_create();
    output->cantCantLista=3;
    for(int c=0; c<output->cantCantLista; c++){
        int lista = 3;
        list_add(output->cantidad_Lista, lista);
    }
    output->precio_Total=30;

    //Lo serializo
    paquete2 =  serializar_output_Consultar_Pedido(output);

    //Genero una nueva variable
    t_pedido* output2 = malloc(sizeof(t_pedido));
    //Deserializo en esa variable
    output2 = deserializar_output_Consultar_Pedido(paquete2);

    //Comparo Valores input
    CU_ASSERT_EQUAL(input->pedidoID, input2->pedidoID );

    //Comparo Valores output
    CU_ASSERT_EQUAL(output->precio_Total, output2->precio_Total );
    CU_ASSERT_EQUAL(output->cantPlatos, output2->cantPlatos );
    CU_ASSERT_EQUAL(output->cantCantPlatos, output2->cantCantPlatos );
    CU_ASSERT_EQUAL(output->cantCantLista, output2->cantCantLista ); 
}
