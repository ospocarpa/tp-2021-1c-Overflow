#include "paginacion.h"

 static t_list * list_tablas_paginacion;
 static t_list * tablas_pag_libre;
 // static t_list *  tabla_hueco;

void iniciar_tabla_paginacion(){
    list_tablas_paginacion = list_create();

}


// bool get_primer_bit_disponible(bitarray bitarray)
//t_bitarray *bitarray_create(char *bitarray, size_t size)
//bitarray_set_bit(t_bitarray *self, off_t bit_index)
// void bitarray_destroy(t_bitarray *self) 
//bool bitarray_test_bit(t_bitarray *self, off_t bit_index) 

int get_primer_bit_disponible(t_bitarray* bitmap){
    int indice =0;
    int bits = bitarray_get_max_bit(bitmap);
  
    for(int c = 0; c < bits ; c++){
        if(!bitarray_test_bit(bitmap,c)){
            indice = c;
            break;
        }
    }
    bitarray_set_bit(bitmap,indice);
    return indice;

}