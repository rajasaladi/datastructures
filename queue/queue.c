/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: queue.c                                                            *
 * Description: Implements Queue Data Structure using Linked List.            *
 * Created: July, 2019                                                        *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue.h>

#define DEFAULT_QSIZE      512

typedef struct qnode_s qnode;
struct qnode_s {
  qnode *next;
  void *data;
};

struct queue_s {
  qnode *first;
  qnode *last;
  int queue_size;
  int elem_size;
  int count;
};


queue_t queue_create(int queue_size, int elem_size)
{
  queue_t q;

  q = (queue_t)malloc(sizeof(struct queue_s));
  if (q) {
    q->first = q->last = NULL;
    q->count = 0;
    q->queue_size = (queue_size < DEFAULT_QSIZE) ? DEFAULT_QSIZE : queue_size;
    q->elem_size = (elem_size <= 0) ? sizeof(int) : elem_size;
    //printf("Queue using Linked List!\n");
  }

  return q;
}

void queue_destroy(queue_t q)
{
  qnode *cur, *tmp;

  if (!q) return;

  cur = q->first;
  while(cur) {
    tmp = cur;
    cur = cur->next;
    free(tmp);
  }
  free(q);

  return;
}

int queue_enqueue(queue_t q, void *data)
{
  qnode *tmp;

  if (!q || !data) return EBADPARM;

  tmp = (qnode *)malloc(sizeof(qnode) + q->elem_size);
  if (!tmp) return ENOMEMORY;

  tmp->next = NULL;
  tmp->data = (void *)(tmp + 1);
  memcpy(tmp->data, data, q->elem_size);

  if (q->last) {
    q->last->next = tmp;
  }
  else {
    q->first = tmp;
  }
  q->last = tmp;
  q->count++;

  return EOK;
}

int queue_dequeue(queue_t q, void *data)
{
  qnode *tmp;

  if (!q || !data) return EBADPARM;
  if (!(q->first)) return EEMPTY;

  tmp = q->first;
  q->first = tmp->next;

  if (!(q->first)) {
    q->last = NULL;
  }

  memcpy(data, tmp->data, q->elem_size);
  free(tmp);
  q->count--;

  return EOK;
}

int queue_length(queue_t q)
{
  return ((q) ? q->count : 0);
}

void queue_display(queue_t q, queue_dispfn_t fn)
{
  qnode *cur;
  int count = 1;

  if (!q || !q->first) {
    printf("Queue is Empty!\n");
    return;
  }

  printf("[%d]: ", q->count);
  cur = q->first;
  while(cur) {
    //printf("%4d (0x%x) ", cur->element, (int)cur);
    if (fn) {
      fn(cur->data);
    } else {
      printf(" (0x%x) ", (int)cur->data);
    }
    if (!(count & 0x7)) {
      printf("\n");
    }
    cur = cur->next;
    count++;
  }
  printf("\n");

  return;
}
