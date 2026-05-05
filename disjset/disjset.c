/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: disjset.c                                                          *
 * Description: Implements Disjoint Set Data Structure.                       *
 * Created: Jul 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <disjset.h>

#define DISJSET_MINSIZE       10

struct disjset_s {
  int num;
  int *arr;
};

disjset_t disjsetCreate(int num)
{
  int i;
  disjset_t set;

  if (num < 1) num = DISJSET_MINSIZE;
  set = (disjset_t)malloc(sizeof(struct disjset_s) + num * sizeof(int));
  if (!set) return NULL;

  set->num = num;
  set->arr = (int *)(set + 1);

  for (i = 0; i < set->num; i++) {
    set->arr[i] = -1;
  }

  return set;
}

void disjsetDestroy(disjset_t set)
{
  if (!set) return;

  free(set);
  return;
}

int disjsetFindInternal(int *arr, int a)
{
  while (arr[a] >= 0) {
    a = arr[a];
  }

  return a;
}

/* Return's root index as name of the set
 * - returns -ve value in case of error
*/
int disjsetFind(disjset_t set, int a)
{
  if (!set || a < 0 || a >= set->num) return EBADPARM;

  return disjsetFindInternal(set->arr, a);
}

int disjsetUnion(disjset_t set, int a, int b)
{
  if (a == b) return EOK;
  if (!set || a < 0 || a >= set->num) return EBADPARM;

  a = disjsetFind(set, a);
  b = disjsetFind(set, b);

  if (set->arr[a] < set->arr[b]) {
    /* a's height > b's height. So merge b with a */
    set->arr[b] = a;
  } else {
    /* if a's height == b's height and
     * since a is being merged with b, increment b's height.
     * Because height is represent negative decrement operator is applied
     */
    if (set->arr[a] == set->arr[b]) set->arr[b]--;
    /* a's height <= b's height then merge a with b */
    set->arr[a] = b;
  }

  return EOK;
}

void disjsetPrint(disjset_t set)
{
  int i;

  if (!set) return;

  for (i = 0; i < set->num; i++) {
    printf("%3d (%3d), ", i, set->arr[i]);
    if (!((i + 1) % 10)) printf("\n");
  }
  if (i % 10) printf("\n");

  return;
}
