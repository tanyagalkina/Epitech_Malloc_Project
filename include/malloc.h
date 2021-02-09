//
// Created by tag43 on 2/9/21.
//

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stddef.h>
#include <stdio.h>

typedef struct free_block {
    size_t size;
    struct free_block* next;
} free_block_t;

void *malloc( size_t size );
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size) ;
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif //MALLOC_MALLOC_H
