/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack_array.c                                                      *
 * Description: Implements Stack Data Structure using Array.                  *
 * Created: Jan 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>

#define DEFAULT_STACKSIZE         256

struct stack1_s {
  int top;
  int stack_size;
  int elem_size;
  void *arr;
};

stack1_t stack_create(int stack_size, int elem_size)
{
  stack1_t st;

  stack_size = (stack_size < DEFAULT_STACKSIZE) ? DEFAULT_STACKSIZE : stack_size;
  elem_size = (elem_size <= 0) ? sizeof(int) : elem_size;
  st = (stack1_t)malloc(sizeof(struct stack1_s) + stack_size * elem_size);
  if (st) {
    st->top = -1;
    st->stack_size = stack_size;
    st->elem_size = elem_size;
    st->arr = (void *)(st + 1);
    //printf("Stack using Array!\n");
  }

  return st;
}

void stack_destroy(stack1_t st)
{
  if (st) {
    free(st);
  }

  return;
}

int stack_push(stack1_t st, void *data)
{
  void *tmp;

  if (!st || !data)
    return EBADPARM;

  if (st->top == st->stack_size - 1)
    return EFULL;

  //st->arr[++st->top] = element;
  st->top++;
  tmp = (char *)st->arr + (st->top * st->elem_size);
  memcpy(tmp, data, st->elem_size);

  return EOK;
}

int stack_pop(stack1_t st, void *data)
{
  void *tmp;

  if (!st || !data)
    return EBADPARM;

  if (-1 == st->top)
    return EEMPTY;

  //*pelement = st->arr[st->top--];
  tmp = (char *)st->arr + (st->top * st->elem_size);
  memcpy(data, tmp, st->elem_size);

  st->top--;

  return EOK;
}

int stack_top(stack1_t st, void *data)
{
  void *tmp;

  if (!st || !data)
    return EBADPARM;

  if (-1 == st->top)
    return EEMPTY;

  tmp = (char *)st->arr + (st->top * st->elem_size);
  memcpy(data, tmp, st->elem_size);

  return EOK;
}

int stack_clear(stack1_t st)
{
  if (!st) return EBADPARM;

  st->top = -1;
  return EOK;
}

void stack_display(stack1_t st)
{
  int i, count = 1;

  if (stack_is_empty(st)) {
    printf("Stack is Empty!\n");
    return;
  }

  printf("c:%d ", st->top+1);
  for (i = st->top; i >= 0; i--, count++) {
    //printf("%4d (0x%x)", st->arr[i], (int)&st->arr[i]);
    printf(" (0x%x)", (int)((char *)st->arr + i * st->elem_size));
    if (!(count & 0x7)) {
      printf("\n");
    }
  }
  printf("\n");

  return;
}

void stack_custom_display(stack1_t st, customfn_t fn)
{
  int i, count = 1;

  if (stack_is_empty(st)) {
    printf("Stack is Empty!\n");
    return;
  }

  if (!fn) {
    stack_display(st);
    return;
  }

  printf("c:%d ", st->top+1);
  for (i = st->top; i >= 0; i--, count++) {
    //printf("%4d (0x%x)", st->arr[i], (int)&st->arr[i]);
    //printf(" (0x%x)", (int)((char *)st->arr + i * st->elem_size));
    //fn(&st->arr[i]);
    fn((void *)((char *)st->arr + i * st->elem_size));
    if (!(count & 0x7)) {
      printf("\n");
    }
  }
  printf("\n");

  return;
}

int stack_is_empty(stack1_t st)
{
  return (!st || -1 == st->top);
}
