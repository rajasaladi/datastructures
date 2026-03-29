/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack.c                                                            *
 * Description: Implements Stack Data Structure using Linked List.            *
 * Created: January, 2019                                                     *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

#define DEFAULT_STACKSIZE         256

typedef struct snode_s snode;
struct snode_s {
  snode *next;
  void *data;
};

struct stack1_s {
  snode *top;
  int stack_size;
  int elem_size;
  int count;
};

stack1_t stack_create(int stack_size, int elem_size)
{
  stack1_t st;

  st = (stack1_t)malloc(sizeof(struct stack1_s));
  if (st) {
    st->top = NULL;
    st->count = 0;
    st->stack_size = (stack_size < DEFAULT_STACKSIZE) ? DEFAULT_STACKSIZE : stack_size;
    st->elem_size = (elem_size <= 0) ? sizeof(int) : elem_size;
    //printf("Stack using Linked List!\n");
  }

  return st;
}

void stack_destroy(stack1_t st)
{
  snode *cur, *tmp;

  if (st) {
    cur = st->top;
    while(cur) {
      tmp = cur->next;
      free(cur);
      cur = tmp;
    }
    free(st);
  }

  return;
}

int stack_push(stack1_t st, void *data)
{
  snode *tmp;

  if (!st || !data)
    return EBADPARM;

  if (st->count == st->stack_size) /* Stack Full */
    return EFULL;

  tmp = (snode *)malloc(sizeof(snode) + st->elem_size);
  if (!tmp) /* out of memory */
    return ENOMEMORY;

  tmp->next = st->top;
  st->top = tmp;
  st->count++;
  tmp->data = (void *)(tmp + 1);
  memcpy(tmp->data, data, st->elem_size);

  return EOK;
}

int stack_pop(stack1_t st, void *data)
{
  snode *tmp;

  if (!st || !data) return EBADPARM;
  if (!(st->top)) {
    //printf("Stack Empty!\n");
    return EEMPTY;
  }

  tmp = st->top;
  st->top = tmp->next;
  memcpy(data, tmp->data, st->elem_size);
  free(tmp);
  st->count--;

  return EOK;
}

int stack_top(stack1_t st, void *data)
{
  if (!st || !data) return EBADPARM;
  if (!(st->top)) return EEMPTY;

  memcpy(data, st->top->data, st->elem_size);
  return EOK;
}

int stack_clear(stack1_t st)
{
  snode *p, *tmp;

  if (!st) return EBADPARM;

  p = st->top;
  while (p) {
    tmp = p->next;
    free(p);
    p = tmp;
  }

  st->top = NULL;
  st->count = 0;

  return EOK;
}

void stack_display(stack1_t st)
{
  snode *cur;
  int count = 1;

  if (NULL == st || NULL == st->top) {
    printf("Stack is Empty!\n");
    return;
  }

  printf("c:%d", st->count);
  cur = st->top;
  while(cur) {
    //printf("%4d (0x%x)", cur->element, (int)cur);
    printf(" (0x%x)", (int)cur->data);
    if (!(count & 0x7)) {
      printf("\n");
    }
    cur = cur->next;
    count++;
  }
  printf("\n");

  return;
}

void stack_custom_display(stack1_t st, customfn_t fn)
{
  snode *cur;
  int count = 1;

  if (NULL == st || NULL == st->top) {
    printf("Stack is Empty!\n");
    return;
  }

  if (!fn) {
    stack_display(st);
    return;
  }

  printf("c:%d", st->count);
  cur = st->top;
  while(cur) {
    //printf("%4d (0x%x)", cur->element, (int)cur);
    //printf(" (0x%x)", (int)cur->data);
    fn(cur->data);
    if (!(count & 0x7)) {
      printf("\n");
    }
    cur = cur->next;
    count++;
  }
  printf("\n");

  return;
}

int stack_is_empty(stack1_t st)
{
  return (!st || !(st->top));
}
