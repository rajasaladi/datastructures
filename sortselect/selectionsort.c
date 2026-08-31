/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: selectionsort.c                                                    *
 * Description: Implements Selection Sort Algorithm.                         *
 * Created: Aug 2026                                                          *
*******************************************************************************
*/
#include <stdio.h>

/*
 * Selection Sort
 * Runtime complexity: O(n^2)
 * Space complexity: O(1)
 * Note: Not stable -- swapping the minimum into place can jump it past
 *   other equal elements, changing their relative order.
*/
void selectionsort(int *a, int n)
{
  int i, j, min_idx, tmp;

  if (!a || n < 2) return;

  for (i = 0; i < n - 1; i++) {

    min_idx = i;
    for (j = i + 1; j < n; j++) {
      if (a[j] < a[min_idx]) {
        min_idx = j;
      }
    }

    if (min_idx != i) {
      tmp = a[i];
      a[i] = a[min_idx];
      a[min_idx] = tmp;
    }
  }

  return;
}
