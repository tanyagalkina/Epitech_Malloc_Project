//
// Created by tag43 on 2/9/21.
//


#include "../include/malloc.h"
#include <unistd.h>


static free_block_t free_block_list_head = { 0, 0 };

// static const size_t overhead = sizeof(size_t);

static const size_t align_to = 16;

void *malloc(size_t size)
{
    //write(1, "I am my own malloc!\n", 20);
    //write(1, "I added this for check!\n", 24);
    //return NULL;
    size = (size + sizeof(free_block_t) + (align_to - 1)) & ~ (align_to - 1);
    free_block_t* block = free_block_list_head.next;
    free_block_t** head = &(free_block_list_head.next);
    while (block != 0) {
        if (block->size >= size) {
            *head = block->next;
            return ((char*)block) + sizeof(free_block_t);
        }
        head = &(block->next);
        block = block->next;
    }

    block = (free_block_t*)sbrk(size);
    block->size = size;

    return ((char*)block) + sizeof(free_block_t);

}

void free(void *ptr)
{
    free_block_t* block = (free_block_t*)(((char*)ptr) - sizeof(free_block_t));
    block->next = free_block_list_head.next;
    free_block_list_head.next = block;
    //write(1, "I am free now!\n", 16);
    //return;
}

void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
