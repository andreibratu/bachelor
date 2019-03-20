#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Vector.h"


Vector* vector_init()
{
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->capacity = VECTOR_INIT_CAPACITY;
    v->size = 0;
    v->items = (TElem*)malloc(sizeof(TElem) * VECTOR_INIT_CAPACITY);
    return v;
}


void vector_resize(Vector* v, int capacity)
{
    TElem* n_elems = (TElem*)malloc(sizeof(TElem)* v->capacity * 2);
    int i;
    for (i=0; i<v->size; i++){
      n_elems[i]=v->items[i];
    }
    free(v->items);
    v->items = n_elems;
    v->capacity *= 2;
}


void vector_add(Vector* v, TElem item)
{
    if (v->capacity == v->size)
        vector_resize(v, v->capacity * 2);
    v->items[v->size++] = item;
}


void vector_set(Vector* v, int index, TElem item)
{
    if (index >= 0 && index < v->size)
        v->items[index] = item;
}


TElem vector_get(Vector* v, int index)
{
    if (index >= 0 && index < v->size)
        return v->items[index];
    return NULL;
}


int vector_find(Vector* v, TElem e, int (*equality)(TElem, TElem)) {
  int i;
  for(i=0; i<v->size; i++) {
    assert(e);
    assert(v->items[i]);
    if(equality(e, v->items[i])) return i;
  }

  return -1;
}


void vector_remove(Vector* v, int index, void (*destructor)(TElem))
{
    if (index < 0 || index >= v->size)
        return;

    destructor(v->items[index]);

    memcpy(
      v->items+index,
      v->items+index+1,
      (v->size-index+1) * sizeof(TElem)
    );

    v->size--;

    if (v->size > 0 && v->size == v->capacity / 4)
        vector_resize(v, v->capacity / 2);
}


void vector_destructor(Vector* v, void (*destructor)(TElem))
{
    int i;
    for(i=0; i<v->size; i++) {
      destructor(v->items[i]);
    }
    free(v->items);
    free(v);
}
