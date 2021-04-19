#include "tests_crear_pedido.h"


void test_serializar_O_CONSULTAR_RESTAURANTEear_pedido(){
    t_pedidoID* O_CREAR_PEDIDO = malloc(sizeof(t_pedidoID));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    O_CREAR_PEDIDO->pedidoID = 1;


    //Lo serializo
    paquete =  serializar_O_CREAR_PEDIDO(O_CREAR_PEDIDO);

    //Genero una nueva variable
     t_pedidoID* O_CREAR_PEDIDO2 = malloc(sizeof(t_pedidoID));
    //Deserializo en esa variable
    O_CREAR_PEDIDO2 = deserializar_O_CREAR_PEDIDO(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(O_CREAR_PEDIDO->pedidoID, O_CREAR_PEDIDO2->pedidoID );



}