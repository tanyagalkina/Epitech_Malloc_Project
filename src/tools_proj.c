#include "../include/my_malloc.h"

size_t next_pow_two(size_t size) {

    //if ((size & (size - 1)) == 0 && size >= 128)
      //  return size;

    size_t  value  =  128 ;

    while  ( value  <=  size)

    {

        value  =  value  <<  1 ;
    }

    return  value ;
}