/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: gheap.c                                                            *
 * Description: Defines interface of heap data structure as needed for the    *
 *              Graph data structure.                                         *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#ifndef GHEAP_H
#define GHEAP_H
#include <err.h>

#define HEAPTYPE_MIN          0
#define HEAPTYPE_MAX          1

#define HEAPSIZE_MIN          10

typedef struct heap_s *heap_t;

heap_t heap_create(int type, int size);
void heap_destroy(heap_t h);
int heap_insert(heap_t h, int key, int u, int v);
int heap_deletemin(heap_t h, int *pKey, int *pU, int *pV);

#endif /* #ifndef GHEAP_H */
