/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: insertionsort.c                                                    *
 * Description: Implements Inseration Sort Algorithm.                         *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <sort.h>

void insertionsort(int *a, int n)
{
  int i, j, key;

  if (!a || n < 2) return;

  for (i = 1; i < n; i++) {
    key = a[i];
    for (j = i - 1; j >= 0 && a[j] > key; j--) {
      a[j+1] = a[j];
    }
    a[j+1] = key;
  }

  return;
}

#if 0
/* Old code -- Remove */
void insertionsort(int *a, int n)
{
  int i, j, tmp;

  if (!a) return;

  for (i = 1; i < n; i++) {
    tmp = a[i];
    for (j = i; j > 0; j--) {
      if (a[j-1] <= tmp) {
        break;
      }
      a[j] = a[j-1];
    }
    a[j] = tmp;
  }

  return;
}
#endif
