#include "tests_guardar_pedido.h"

void test_serializar_guardar_pedido(){
    t_I_GUARDAR_PEDIDO* GPinput = malloc(sizeof(t_I_GUARDAR_PEDIDO));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    
    GPinput->idPedido = 1;
    GPinput->restaurante = "Restaurante";
    GPinput->restaurante_length = strlen(GPinput->restaurante);
    //Lo serializo
    paquete =  serializar_I_GUARDAR_PEDIDO(GPinput);

    //Genero una nueva variable
    t_I_GUARDAR_PEDIDO* GPinput2 = malloc(sizeof(t_I_GUARDAR_PEDIDO));
    //Deserializo en esa variable
    GPinput2 = deserializar_I_GUARDAR_PEDIDO(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(GPinput->idPedido, GPinput2->idPedido );
    CU_ASSERT_STRING_EQUAL(GPinput->restaurante, GPinput2->restaurante );
    CU_ASSERT_EQUAL(GPinput->restaurante_length, GPinput2->restaurante_length );
    //CU_ASSERT_EQUAL(2+2, 4);    

}
