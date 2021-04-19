#include "tests_terminar_pedido.h"

void test_serializar_terminar_pedido(){
    //------------------------------------------------------- INPUT
    t_pedidoID_With_Restaurant* input = malloc(sizeof(t_pedidoID_With_Restaurant));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores    
    input->pedidoID = 1;
    input->nombreDeRes = "pedido test";
    input->nombreDeRes_length = strlen(input->nombreDeRes);
    //Lo serializo
    paquete =  serializar_I_TERMINAR_PEDIDO(input);

    //Genero una nueva variable
    t_pedidoID_With_Restaurant* input2 = malloc(sizeof(t_pedidoID_With_Restaurant));
    //Deserializo en esa variable
    input2 = deserializar_I_TERMINAR_PEDIDO(paquete);

    //Comparo Valores
    CU_ASSERT_EQUAL(input->pedidoID, input2->pedidoID );
    CU_ASSERT_STRING_EQUAL(input->nombreDeRes, input2->nombreDeRes );
    CU_ASSERT_EQUAL(input->nombreDeRes_length, input2->nombreDeRes_length );
}
