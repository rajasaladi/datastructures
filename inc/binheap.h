/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: binheap.h                                                          *
 * Description: Defines interface for Binary Heap Datastructure.              *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#ifndef HEAP_H
#define HEAP_H
#include <err.h>

typedef struct heap_s *heap_t;

typedef enum {
  HEAPTYPE_MIN,   /* Min Heap */
  HEAPTYPE_MAX    /* Max Heap */
} heaptype_e;

/* Heap - Methods */
heap_t heap_create(heaptype_e type, int size);
void heap_destroy(heap_t bh);
void heap_print(heap_t bh);
void heap_print_array(heap_t bh);

/* Min Heap - Methods */
int minheap_insert(heap_t bh, int element);
int minheap_getmin(heap_t bh, int *pelement);
int minheap_deletemin(heap_t bh, int *pelement);

/* Max Heap - Methods */
int maxheap_insert(heap_t bh, int element);
int maxheap_getmax(heap_t bh, int *pelement);
int maxheap_deletemax(heap_t bh, int *pelement);

/* Array Heap - Methods */
/* heapify - Ensures heap order is maintained from root index 'i' */
void heap_minheapify(int *a, int n, int i);
void heap_maxheapify(int *a, int n, int i);
/* buildheap - Builds heap from a given array */
void heap_buildminheap(int *a, int n);
void heap_buildmaxheap(int *a, int n);
void heap_print2(int *a, int n);

#endif /* HEAP_H */
