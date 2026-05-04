/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: queue_array.c                                                      *
 * Description: Implements Queue Data Structure using Array.                  *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

#define DEFAULT_QSIZE      512

struct queue_s {
  int first;
  int last;
  int queue_size;
  int elem_size;
  int count;
  void *arr;
};


queue_t queue_create(int queue_size, int elem_size)
{
  queue_t q;

  queue_size = (queue_size < DEFAULT_QSIZE) ? DEFAULT_QSIZE : queue_size;
  elem_size = (elem_size <= 0) ? sizeof(int) : elem_size;
  q = (queue_t)malloc(sizeof(struct queue_s) + queue_size * elem_size);
  if (q) {
    q->first = q->last = -1;
    q->count = 0;
    q->queue_size = queue_size;
    q->elem_size = elem_size;
    q->arr = (void *)(q + 1);
    //printf("Queue using Array!\n");
  }

  return q;
}

void queue_destroy(queue_t q)
{
  if (q) {
    free(q);
  }

  return;
}

int queue_enqueue(queue_t q, void *data)
{
  int target;
  void *tmp;

  if (!q || !data) return EBADPARM;

  target = (q->last + 1) % q->queue_size;
  if (target == q->first) return EFULL;

  q->last = target;
  tmp = (char *)q->arr + (target * q->elem_size);
  memcpy(tmp, data, q->elem_size);

  if (-1 == q->first) {
    q->first = q->last;
  }
  q->count++;

  return EOK;
}

int queue_dequeue(queue_t q, void *data)
{
  void *tmp;

  if (!q || !data) return EBADPARM;
  if (-1 == q->first) return EEMPTY;

  tmp = (char *)q->arr + (q->first * q->elem_size);
  memcpy(data, tmp, q->elem_size);

  if (q->first == q->last) {
    q->first = q->last = -1;
  } else {
    q->first = (q->first + 1) % q->queue_size;
  }
  q->count--;

  return EOK;
}

int queue_length(queue_t q)
{
  return ((q) ? q->count : 0);
}

void queue_display(queue_t q, queue_dispfn_t fn)
{
  int i, count = 1, limit;

  if (!q || -1 == q->first) {
    printf("Queue is Empty!\n");
    return;
  }

  printf("[%d]: ", q->count);
  limit = (q->first <= q->last) ? q->last : q->queue_size - 1;
  for (i = q->first; i <= limit; i++, count++) {
    //printf("%4d (0x%x) ", q->arr[i], (int)&q->arr[i]);
    if (fn) {
      fn(q->arr + i * q->elem_size);
    } else {
      printf(" (0x%x) ", (int)((char *)q->arr + i * q->elem_size));
    }
    if (!(count & 0x7)) {
      printf("\n");
    }
  }

  limit = (q->first <= q->last) ? -1 : q->last;
  for (i = 0; i <= limit; i++, count++) {
    //printf("%4d (0x%x) ", q->arr[i], (int)&q->arr[i]);
    if (fn) {
      fn(q->arr + i * q->elem_size);
    } else {
      printf(" (0x%x) ", (int)((char *)q->arr + i * q->elem_size));
    }
    if (!(count & 0x7)) {
      printf("\n");
    }
  }

  printf("\n");

  return;
}
