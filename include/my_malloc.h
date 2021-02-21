/*
** EPITECH PROJECT, 2020
** malloc
** File description:
** #
*/

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

extern void *my_vm;

typedef long Align;

union block {
    struct {
        union block *next;
        union block *previous;
        void *data_ptr;
        size_t size;
    } s;
    Align x;
};

typedef union block block_t;

#define BLK_SZ sizeof(block_t)

typedef struct global_header {
    void *vm_start;
    block_t *list_of_all;
    block_t *free_list;
    void *curr_break;
    void *end_of_allocated;
    unsigned int blocks_alloc;
    unsigned int blocks_free;
}global_t;

void print_malloc_header();

size_t next_pow_two(size_t size);

void add_to_free_list(block_t *new_free_block);
void *heap_init(size_t nbytes);
void *morecore(size_t nbytes);
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size) ;
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void *my_malloc( unsigned nunits);
void *my_best_fit(size_t nbytes);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size) ;
void *my_reallocarray(void *ptr, size_t nmemb, size_t size);

#endif //MALLOC_MALLOC_H