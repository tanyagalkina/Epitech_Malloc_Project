/*
** EPITECH PROJECT, 2020
** malloc
** File description:
** src
*/

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "../include/my_malloc.h"

void *my_vm = NULL;

void *morecore(size_t nbytes)
{
    block_t *new_alloc;
    block_t *new_free;

    new_alloc = sbrk(nbytes * BLK_SZ);
    if (new_alloc == (void *) -1) {
            errno = ENOMEM;
            return (NULL);
    }
    new_alloc->s.size = (nbytes * 8);
    new_alloc->s.data_ptr = (void *)(new_alloc + 1);
    new_free = ((void *)new_alloc->s.data_ptr) + new_alloc->s.size;
    new_free->s.size = (nbytes * BLK_SZ - new_alloc->s.size - BLK_SZ * 2 );
    new_free->s.data_ptr = (void *)(new_free + 1);
    add_to_free_list(new_free);
    return (new_alloc->s.data_ptr);
}

void *heap_init(size_t nbytes)
{
    block_t *new_alloc;
    block_t *new_free;

    global_t *my_heap = sbrk(nbytes * BLK_SZ );
    if (my_heap == (void *) -1) {
        errno = ENOMEM;
        return (NULL);
    }
    my_vm = my_heap;
    my_heap->free_list = NULL;
    my_heap->vm_start = ((char *)my_heap) + sizeof(global_t);
    new_alloc = (block_t *)my_heap->vm_start;
    new_alloc->s.size = (nbytes * 8);
    new_alloc->s.data_ptr = (void *)(new_alloc + 1);
    new_free = ((void *)new_alloc->s.data_ptr) + new_alloc->s.size;
    new_free->s.size = (nbytes * BLK_SZ - new_alloc->s.size - \
BLK_SZ * 2 - sizeof(global_t));
    new_free->s.data_ptr = (void *)(new_free + 1);
    add_to_free_list(new_free);
    return (new_alloc->s.data_ptr);
}

void add_to_free_list(block_t *new_free_block)
{
    new_free_block->s.next = NULL;
    new_free_block->s.previous = NULL;
    global_t *my_heap = my_vm;

    if (new_free_block == NULL) {
        return;
    }
    if (!my_heap->free_list) {
        my_heap->free_list = new_free_block;
        return;
    }
    my_heap->free_list->s.previous = new_free_block;
    new_free_block->s.next = my_heap->free_list;
    my_heap->free_list = new_free_block;
    return;
}

static block_t *remove_from_free(block_t *best)
{
    global_t *my_heap = my_vm;

    if (!best->s.previous && !best->s.next) {
        my_heap->free_list = NULL;
        return (best);
    }
    if (!best->s.previous && best->s.next) {
        my_heap->free_list = best->s.next;
        my_heap->free_list->s.previous = NULL;
        return (best);
    }
    else if (!best->s.next) {
        best->s.previous->s.next = NULL;
        return (best);
    }
    best->s.previous->s.next = best->s.next;
    return (best);
}

void *my_best_fit(size_t nbytes)
{
    static int i = 0;
    global_t *my_heap = my_vm;
    block_t *tmp = my_heap->free_list;
    block_t *best = NULL;

    ++i;
    if (i  % 1000)
        return NULL;
    if (!tmp)
        return NULL;
    while (tmp) {
        if (tmp->s.size >= nbytes && !best)
            best = tmp;
        if (tmp->s.size >= nbytes && best && tmp->s.size < best->s.size)
            best = tmp;
        tmp = tmp->s.next;
    }
    if (best)
        best = remove_from_free(best);
    return (best);
}