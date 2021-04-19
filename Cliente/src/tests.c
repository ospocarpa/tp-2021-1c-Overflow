#include "tests.h"
int run_tests(){
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite",NULL,NULL);

 
    CU_add_test(tests,"Probar Suma", suma_proceso1);
    CU_add_test(tests,"Probar Serializar y deserializar Respuesta Booleana", test_serializar_respuesta_bool);
    CU_add_test(tests,"Probar Serializar y deserializar Seleccionar Restaurante", test_serializar_seleccionar_restaurante);
    CU_add_test(tests,"Probar Serializar y deserializar Consultar Restaurantes", test_serializar_consultar_restaurantes);
    CU_add_test(tests,"Probar Serializar y deserializar Guardar Pedido", test_serializar_guardar_pedido);
    CU_add_test(tests,"Probar Serializar y deserializar Crear Pedido", test_serializar_O_CONSULTAR_RESTAURANTEear_pedido);
    CU_add_test(tests,"Probar Serializar y deserializar Pedido", test_serializar_output_pedido);
    CU_add_test(tests,"Probar Serializar y deserializar Consultar pedido", test_serializar_consultar_pedido);
    CU_add_test(tests,"Probar Serializar y deserializar Terminar pedido", test_serializar_terminar_pedido);
    CU_add_test(tests,"Probar Serializar y deserializar Estructura Restaurante", test_serializar_t_restaurantes);
    CU_add_test(tests,"Probar Serializar y deserializar Input de Obtener Restaurante", test_serializar_input_obtener_restaurantes);
    CU_add_test(tests,"Probar Serializar y deserializar Añadir Plato", test_serializar_I_ANADIR_PLATO);
    CU_add_test(tests,"Probar Serializar y deserializar Obtener Pedido", test_serializar_input_obtener_pedido);   
    CU_add_test(tests,"Probar Serializar y deserializar Plato Listo", test_serializar_I_PLATO_LISTOato_listo);
    CU_add_test(tests,"Probar Serializar y deserializar Guardar Plato", test_serializar_input_guardar_plato);



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
void suma_proceso1(){
    CU_ASSERT_EQUAL(2+2, 4);
}


void test_serializar_respuesta_bool(){
    t_respuesta_bool* respuesta = malloc(sizeof(t_respuesta_bool));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    respuesta->estado = "Fail";
    respuesta->estado_length = strlen(respuesta->estado);
    
    //Lo serializo
    paquete = serializar_respuesta_bool(respuesta);

    //Genero una nueva variable
    t_respuesta_bool* respuesta2 = malloc(sizeof(t_respuesta_bool));
    //Deserializo en esa variable
    respuesta2 = deserializar_respuesta_bool(paquete);
    //Comparo Valores
    CU_ASSERT_STRING_EQUAL(respuesta->estado, respuesta2->estado );
    CU_ASSERT_EQUAL(respuesta->estado_length, respuesta2->estado_length );

    //Cargo Valores
    respuesta->estado = "OK";
    respuesta->estado_length = strlen(respuesta->estado);
    //Lo serializo
    paquete = serializar_respuesta_bool(respuesta);
    //Deserializo en esa variable
    respuesta2 = deserializar_respuesta_bool(paquete);
    //Comparo Valores
    CU_ASSERT_STRING_EQUAL(respuesta->estado, respuesta2->estado );
    CU_ASSERT_EQUAL(respuesta->estado_length, respuesta2->estado_length );


}
void test_serializar_seleccionar_restaurante(){
    t_I_SELECCIONAR_RESTAURANTE* srinput = malloc(sizeof(t_I_SELECCIONAR_RESTAURANTE));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    srinput->cliente = "Cliente";
    srinput->cliente_length = strlen(srinput->cliente);
    srinput->restaurante = "Restaurante";
    srinput->restaurante_length = strlen(srinput->restaurante);
    //Lo serializo
    paquete =  serializar_I_SELECCIONAR_RESTAURANTE(srinput);

    //Genero una nueva variable
    t_I_SELECCIONAR_RESTAURANTE* srinput2 = malloc(sizeof(t_I_SELECCIONAR_RESTAURANTE));
    //Deserializo en esa variable
    srinput2 = deserializar_I_SELECCIONAR_RESTAURANTE(paquete);
    //Comparo Valores
    CU_ASSERT_STRING_EQUAL(srinput->cliente, srinput2->cliente );
    CU_ASSERT_EQUAL(srinput->cliente_length, srinput2->cliente_length );
    CU_ASSERT_STRING_EQUAL(srinput->restaurante, srinput2->restaurante );
    CU_ASSERT_EQUAL(srinput->restaurante_length, srinput2->restaurante_length );
    //CU_ASSERT_EQUAL(2+2, 4);
}


