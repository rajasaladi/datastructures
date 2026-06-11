/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: merge_sort.c                                                       *
 * Description: Implements Merge Sort algorithm.                              *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <sort.h>

void merge(int *a, int *tmp, int low, int mid, int high)
{
  int i, left, right, current;

  for (i = low; i <= high; i++)
    tmp[i] = a[i];

  current = low;
  left = low;
  right = mid + 1;

  while (left <= mid && right <= high) {
    if (tmp[left] <= tmp[right])
      a[current++] = tmp[left++];
    else
      a[current++] = tmp[right++];
  }

  while (left <= mid)
    a[current++] = tmp[left++];

  return;
}

void msort(int *a, int *tmp, int low, int high)
{
  int mid;

  if (low < high) {
    mid = (low + high)/2;
    msort(a, tmp, low, mid);
    msort(a, tmp, mid + 1, high);
    merge(a, tmp, low, mid, high);
  }

  return;
}

void mergesort2(int *a, int n)
{
  int *tmp; /* Temp Array */

  if (!a || n < 2) {
    return;
  }

  tmp = malloc(n * sizeof(int));
  if (!tmp) {
    printf("Not enough memory!\n");
    return;
  }

  msort(a, tmp, 0, n - 1);
  free(tmp);

  return;
}
