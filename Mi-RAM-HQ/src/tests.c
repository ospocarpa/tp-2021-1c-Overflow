#include "tests.h"

int run_tests(){
    CU_initialize_registry();
    CU_pSuite tests = CU_add_suite("Cliente Suite",NULL,NULL);

 
    CU_add_test(tests,"Suma2+2", suma);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}


void suma(){
    CU_ASSERT_EQUAL(2+2, 4);
}


 
  

  

