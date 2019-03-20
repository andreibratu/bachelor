#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 1

typedef void* TElem;

typedef struct {
    TElem* items;
    int capacity;
    int size;
} Vector;

Vector* vector_init();
void vector_resize(Vector*, int);
void vector_add(Vector*, void *);
void vector_set(Vector*, int, TElem);
TElem vector_get(Vector*, int);
int vector_find(Vector*, TElem, int (*)(TElem, TElem));
void vector_remove(Vector*, int, void (*)(TElem));
void vector_destructor(Vector*, void (*) (TElem));

#endif
