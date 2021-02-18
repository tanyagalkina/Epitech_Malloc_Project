/*
** EPITECH PROJECT, 2020
** tetris
** File description:
** main
*/

#include "../include/my_malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
    char				*tmp;
    size_t			total;

    total = nmemb * size;
    if (!total)
        return (malloc(size));
    if (size && (total / size != nmemb))
        return (NULL);
    if ((tmp = malloc(total)) == NULL)
        return (NULL);
    memset(tmp, 0, total);
    return (tmp);
}

static void *probe(void *ptr, size_t size)
{
    if (ptr == NULL)
        return (malloc(size));
    else if (size == 0) {
        free(ptr);
        return (malloc(0));
    }
    return ((void *)1);
}

void *realloc(void *ptr, size_t size) {
    void *tmp;
    block_t *old = (block_t *)ptr - 1;
    size_t i = 0;
    size_t old_size;

    if ((tmp = probe(ptr, size)) != (void *)1)
            return (tmp);
    old_size = old->s.size;
    if (!((size & (size - 1)) == 0 && size >= 128) || old_size <= 0 )
        return (malloc(size));
    if (old_size > size)
        return (ptr);
    if ((tmp = malloc(size)) == NULL)
        return (NULL);
    while (i < old_size) {
        ((char *)tmp)[i] = ((char *)ptr)[i];
        ++i;
    }
    free(ptr);
    return (tmp);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}