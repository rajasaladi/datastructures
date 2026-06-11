/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: radixsort.c                                                        *
 * Description: Implements Radix Sort Algorithm.                              *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void print_array(int *a, int left, int right)
{
  int i;

  if (!a) {
    printf("Array is Empty\n");
    return;
  }

  for (i = left; i <= right; i++) {
    printf(" %2d", a[i]);
  }

  printf("\n");

  return;
}

bool isnegative(int *a, int n)
{
  bool ret = false;
  int i;

  for (i = 0; i < n; i++) {
    if (a[i] < 0) {
      printf("isnegative: index = %d\n", i);
      ret = true; break;
    }
  }

  return ret;
}

int getmin(int *a, int n)
{
  int i, min;

  min = a[0];
  for (i = 1; i < n; i++) {
    if (a[i] < min) {
      min = a[i];
    }
  }

  //printf("getmin: index = %d\n", i);
  return min;
}

int getmax(int *a, int n)
{
  int i, max;

  max = a[0];
  for (i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  return max;
}

/*
 * A modified counting sort to sort elements using a single digit
 * computed using exp.
*/
void countingsort(int *a, int *tmp, int n, int exp)
{
  int i, digit;
  int count[10] = {0};

  for (i = 0; i < n; i++) {
    digit = (a[i]/exp)%10;
    //printf("(%d, %d), ", digit, a[i]);
    count[(a[i]/exp)%10]++;
  }

  for (i = 1; i < 10; i++) {
    count[i] += count[i-1];
  }

  //printf("Count array: ");
  //print_array(count, 0, 9);

  for (i = n - 1; i >= 0; i--) {
    tmp[count[(a[i]/exp)%10] - 1] = a[i];
    count[(a[i]/exp)%10]--;
  }

  for (i = 0; i < n; i++) {
    a[i] = tmp[i];
  }

  return;
}

/* Note:
 *   Function name has 2 appended at the end to avoid
 *   conflict with radixsort present in some default libraries.
 * Time complexity: O(N)
 * Space complexity: O(N)
*/
void radixsort2(int *a, int n)
{
  int i, max;
  int *tmp;

  if (!a || n < 2) return;
  if (isnegative(a, n)) {
  //if (getmin(a, n) < 0) {
    printf("Invalid input. Contains values < 0 for Radix Sort\n");
    return;
  }

  tmp = (int *)malloc(n * sizeof(int));
  if (!tmp) return;

  //print_array(a, 0, n - 1);

  max = getmax(a, n);
  printf("Max: %d\n", max);
  for (i = 1; max/i > 0; i *= 10) {
    countingsort(a, tmp, n, i);
    print_array(a, 0, n - 1);
  }

  free(tmp);

  return;
}
