//
// Created by tag43 on 2/15/21.
//


#include "../include/my_malloc.h"

void *malloc(size_t nbytes) {
    if (nbytes == 0)
        return NULL;
    //if the number cannot be stored in unsigned long int()
    if ((nbytes >> 48 >= 1) && ((int64_t) nbytes < 0)) {
        return (NULL);
    }
    nbytes = next_pow_two(nbytes);
    if (my_vm == NULL) {
         return heap_init(nbytes);
    }
    block_t *new_alloc = my_best_fit(nbytes);
    if (!new_alloc) {
        return morecore(nbytes);
    }

    return new_alloc->s.data_ptr;

}

void free(void *ptr)
{
    if (!ptr)
        return;
    add_to_free_list(((block_t *)ptr) - 1);
    return;
}

