/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: bubblesort.c                                                       *
 * Description: Implements Bubble Sort Algorithm.                             *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>

void bubblesort(int *a, int n)
{
  int i, j, tmp;

  if (!a || n < 2) return;

  for (i = n; i > 1; i--) {
    for (j = 1; j < i; j++) {
      if (a[j-1] > a[j]) {
        tmp = a[j-1];
        a[j-1] = a[j];
        a[j] = tmp;
      }
    }
  }

  return;
}
