#include "tests_guardar_plato.h"


void test_serializar_input_guardar_plato(){
    t_I_GUARDAR_PLATO* I_GUARDAR_PLATO = malloc(sizeof(t_I_GUARDAR_PLATO));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    I_GUARDAR_PLATO->pedidoID = 1;

    //nombreDeRes_length
    //nombreDeRes
    I_GUARDAR_PLATO->nombreDeRes="Restaurante1";
    I_GUARDAR_PLATO->nombreDeRes_length=strlen(I_GUARDAR_PLATO->nombreDeRes);

    //plato
    //plato_length
    I_GUARDAR_PLATO->plato="plato1";
    I_GUARDAR_PLATO->plato_length=strlen(I_GUARDAR_PLATO->plato);

    I_GUARDAR_PLATO->cantidad = 42;    
    //Lo serializo
    paquete =  serializar_I_GUARDAR_PLATO(I_GUARDAR_PLATO);

    //Genero una nueva variable
    t_I_GUARDAR_PLATO* I_GUARDAR_PLATO2 = malloc(sizeof(t_I_GUARDAR_PLATO));
    //Deserializo en esa variable
    I_GUARDAR_PLATO2 = deserializar_I_GUARDAR_PLATO(paquete);
    //Comparo Valores
    CU_ASSERT_EQUAL(I_GUARDAR_PLATO->pedidoID, I_GUARDAR_PLATO2->pedidoID );
    CU_ASSERT_EQUAL(I_GUARDAR_PLATO->nombreDeRes_length, I_GUARDAR_PLATO2->nombreDeRes_length );
    CU_ASSERT_STRING_EQUAL(I_GUARDAR_PLATO->nombreDeRes, I_GUARDAR_PLATO2->nombreDeRes );
    CU_ASSERT_EQUAL(I_GUARDAR_PLATO->plato_length, I_GUARDAR_PLATO2->plato_length );
    CU_ASSERT_STRING_EQUAL(I_GUARDAR_PLATO->plato, I_GUARDAR_PLATO2->plato );
    CU_ASSERT_EQUAL(I_GUARDAR_PLATO->cantidad, I_GUARDAR_PLATO2->cantidad );


}


