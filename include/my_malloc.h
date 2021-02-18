//
// Created by tag43 on 2/9/21.
//

#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <math.h>

extern void *my_vm;

# ifndef __X86_64__
#	define ALIGNMENT		(16)

# else
# 	define ALIGNMENT		(8)
# endif

# define ALIGN(size)			(((size) + (ALIGNMENT - 1)) &~ (ALIGNMENT - 1))
# define MAP_SIZE			ALIGN((ALIGNMENT * 10 * sysconf(_SC_PAGESIZE)))
//# define MAP_SIZE			ALIGN((ALIGNMENT * 10 * sysconf(_SC_PAGESIZE))) why is it so big?
#define MAGIC (0xFEEDFACE)
#define NALLOC        4096 * 2

#define MIN(a,b) (((a)<(b))?(a):(b))
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

#define BLK_SZ     sizeof(block_t)

typedef struct global_header {
    void *vm_start;
    block_t *list_of_all;
    block_t *free_list;
    //block_t *list_of_small_free;
    //block_t *list_of_middle_free;
    //block_t *list_of_big_free;
    void *curr_break;
    void *end_of_allocated;
    unsigned int blocks_alloc;
    unsigned int blocks_free;

}global_t;

void print_malloc_header();

size_t next_pow_two(size_t size);

void 						lock_thread(int flag);
void 						unlock_thread(int flag);

void add_to_free_list(block_t *new_free_block);
void *heap_init(size_t nbytes);
void *morecore(size_t nbytes);
int get_a_chunk(int pages);
void vm_dump();
void vm_init(size_t size);
void my_putchar(char c);
int my_put_nbr(int nb);
void *malloc( size_t size );
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size) ;
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void *my_malloc( unsigned nunits);
void my_free(void *ptr);
void *my_best_fit(size_t nbytes);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size) ;
void *my_reallocarray(void *ptr, size_t nmemb, size_t size);


#endif //MALLOC_MALLOC_H
