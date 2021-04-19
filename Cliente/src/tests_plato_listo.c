#include "tests_plato_listo.h"


void test_serializar_I_PLATO_LISTOato_listo(){
    t_I_PLATO_LISTO* I_PLATO_LISTO = malloc(sizeof(t_I_PLATO_LISTO));
    t_paquete* paquete = malloc(sizeof(t_paquete));

    //Cargo Valores
    I_PLATO_LISTO->pedidoID = 1;

    //nombreDeRes_length
    //nombreDeRes
    I_PLATO_LISTO->nombreDeRes="Restaurante1";
    I_PLATO_LISTO->nombreDeRes_length=strlen(I_PLATO_LISTO->nombreDeRes);

    //plato
    //plato_length
    I_PLATO_LISTO->plato="plato1";
    I_PLATO_LISTO->plato_length=strlen(I_PLATO_LISTO->plato);


    //Lo serializo
    paquete =  serializar_I_PLATO_LISTO(I_PLATO_LISTO);

    //Genero una nueva variable
    t_I_PLATO_LISTO* I_PLATO_LISTO2 = malloc(sizeof(t_I_PLATO_LISTO));
    //Deserializo en esa variable
    I_PLATO_LISTO2 = deserializar_I_PLATO_LISTO(paquete);
    //Comparo Valores
    
    CU_ASSERT_EQUAL(I_PLATO_LISTO->pedidoID, I_PLATO_LISTO2->pedidoID );
    CU_ASSERT_EQUAL(I_PLATO_LISTO->nombreDeRes_length, I_PLATO_LISTO2->nombreDeRes_length );
    CU_ASSERT_STRING_EQUAL(I_PLATO_LISTO->nombreDeRes, I_PLATO_LISTO2->nombreDeRes );
    CU_ASSERT_EQUAL(I_PLATO_LISTO->plato_length, I_PLATO_LISTO2->plato_length );
    CU_ASSERT_STRING_EQUAL(I_PLATO_LISTO->plato, I_PLATO_LISTO2->plato );
    

}


