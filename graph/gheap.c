/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: gheap.c                                                            *
 * Description: Implements heap data structure as needed for Graph data       *
 *              structure.                                                    *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <gheap.h>

typedef struct heape_s {
  int key;
  int u;
  int v;
  //void *param;
} heape_t;

struct heap_s {
  int size;
  int count;
  heape_t *arr;
};

heap_t heap_create(int type, int size)
{
  heap_t h;

  if (size < 1) size = HEAPSIZE_MIN;
  h = (heap_t)malloc(sizeof(struct heap_s) + size * sizeof(heape_t));
  if (!h) return NULL;

  h->size = size;
  h->count = 0;
  h->arr = (heape_t *)(h + 1);

  return h;
}

void heap_destroy(heap_t h)
{
  if (!h) return;
  free(h);
  return;
}

//int heap_insert(heap_t h, int key, void *param)
int heap_insert(heap_t h, int key, int u, int v)
{
  int i, parent;
  heape_t tmp;
  heape_t *arr;

  if (!h) return EBADPARM;
  if (h->count == h->size) return EFULL;

  i = h->count++;
  arr = h->arr;
  arr[i].key = key;
  //arr[i].param = param;
  arr[i].u = u;
  arr[i].v = v;

  parent = (i - 1)/2;
  while (parent >= 0 && arr[parent].key > arr[i].key) {
    tmp = arr[parent]; arr[parent] = arr[i]; arr[i] = tmp;
    i = parent; parent = (i - 1)/2;
  }

  return EOK;
}

//int heap_deletemin(heap_t h, int *pKey, void **pParam)
int heap_deletemin(heap_t h, int *pKey, int *pU, int *pV)
{
  int i, child, smallest;
  heape_t tmp;
  heape_t *arr;

  if (!h) return EBADPARM;
  if (!h->count) return EEMPTY;

  arr = h->arr;
  if (pKey) *pKey = arr[0].key;
  //if (pParam) *pParam = arr[0].param;
  if (pU) *pU = arr[0].u;
  if (pV) *pV = arr[0].v;
  if (!(--h->count)) return EOK;

  arr[0] = arr[h->count];
  i = 0; child = 2 * i + 1;
  while (child < h->count) {
    smallest = (arr[child].key < arr[i].key) ? child : i;
    if (child + 1 < h->count && arr[child + 1].key < arr[smallest].key) smallest = child + 1;
    if (i == smallest) break;
    tmp = arr[i]; arr[i] = arr[smallest]; arr[smallest] = tmp;
    i = smallest; child = 2 * i + 1;
  }

  return EOK;
}
