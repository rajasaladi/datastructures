/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: stack2.c                                                           *
 * Description: Implements Data Structure with two stacks in one array.       *
 * Created: Jan 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack2.h>

#define DEFAULT_STACKSIZE2          128

struct stack2_s {
  int top1;
  int top2;
  int stacks_size;
  int elem_size;
  void *arr;
};

stack2_t stack2_create(int stack_size1, int stack_size2, int elem_size)
{
  stack2_t st;
  int stack_size;

  stack_size1 = (stack_size1 <= 0) ? DEFAULT_STACKSIZE2 : stack_size1;
  stack_size2 = (stack_size2 <= 0) ? DEFAULT_STACKSIZE2 : stack_size2;
  elem_size = (elem_size <= 0) ? sizeof(int) : elem_size;
  stack_size = stack_size1 + stack_size2;

  st = (stack2_t) malloc(sizeof(struct stack2_s) + stack_size * elem_size);
  if (st) {
    st->top1 = -1;
    st->top2 = st->stacks_size = stack_size;
    st->elem_size = elem_size;
    st->arr = (void *)(st + 1);
  }

  return st;
}

void stack2_destroy(stack2_t st)
{
  if (st) {
    free(st);
  }

  return;
}

int stack2_push1(stack2_t st, void *pdata)
{
  void *p;

  if (!st || !pdata) return EBADPARM;
  if (st->top1 + 1 == st->top2) return EFULL;

  st->top1++;
  p = (char *)st->arr + (st->top1 * st->elem_size);
  memcpy(p, pdata, st->elem_size);

  return EOK;
}

int stack2_pop1(stack2_t st, void *pdata)
{
  void *p;

  if (!st || !pdata) return EBADPARM;
  if (-1 == st->top1) return EEMPTY;

  p = (char *)st->arr + (st->top1 * st->elem_size);
  memcpy(pdata, p, st->elem_size);
  st->top1--;

  return EOK;
}

int stack2_push2(stack2_t st, void *pdata)
{
  void *p;

  if (!st || !pdata) return EBADPARM;
  if (st->top1 + 1 == st->top2) return EFULL;

  st->top2--;
  p = (char *)st->arr + (st->top2 * st->elem_size);
  memcpy(p, pdata, st->elem_size);

  return EOK;
}

int stack2_pop2(stack2_t st, void *pdata)
{
  void *p;

  if (!st || !pdata) return EBADPARM;
  if (st->stacks_size == st->top2) return EEMPTY;

  p = (char *)st->arr + (st->top2 * st->elem_size);
  memcpy(pdata, p, st->elem_size);
  st->top2++;

  return EOK;
}

int stack2_is_empty(stack2_t st)
{
  return (!st || (-1 == st->top1 && st->stacks_size == st->top2));
}

int stack2_is_empty1(stack2_t st)
{
  return (!st || -1 == st->top1);
}

int stack2_is_empty2(stack2_t st)
{
  return (!st || st->stacks_size == st->top2);
}

//void stack2_display(stack2_t st)
void stack2_display(stack2_t st, customfn_t fn)
{
  int i, count = 1;

  if (stack2_is_empty(st)) {
    printf("Both Stacks are Empty!\n");
    return;
  }

  if (stack2_is_empty1(st)) {
    printf("Stack1 is Empty!\n");
  } else {
    printf("Stack1\nc:%d\n", st->top1+1);
    for (i = st->top1; i >= 0; i--, count++) {
      //printf("%4d (0x%x)", st->arr[i], (int)&st->arr[i]);
      if (!fn) {
        printf(" (0x%x)", (int)((char *)st->arr + i * st->elem_size));
      } else {
        //fn(&st->arr[i]);
        fn((void *)((char *)st->arr + i * st->elem_size));
      }
      if (!(count & 0x7)) {
        printf("\n");
      }
    }
    printf("\n");
  }

  printf("Stack2\nc:%d\n", st->stacks_size - st->top2);
  for (i = st->top2; i < st->stacks_size; i++, count++) {
    //printf("%4d (0x%x)", st->arr[i], (int)&st->arr[i]);
    if (!fn) {
      printf(" (0x%x)", (int)((char *)st->arr + i * st->elem_size));
    } else {
      //fn(&st->arr[i]);
      fn((void *)((char *)st->arr + i * st->elem_size));
    }
    if (!(count & 0x7)) {
      printf("\n");
    }
  }
  printf("\n");

  return;
}
