/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: insertionsort.c                                                    *
 * Description: Implements Inseration Sort Algorithm.                         *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <sort.h>

/*
 * Insertion Sort
 * Runtime complexity: O(n^2)
 * Space complexity: O(1)
 *
*/
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
