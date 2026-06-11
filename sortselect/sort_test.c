/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: sort_test.c                                                        *
 * Description: Implements Test module to test various Sort algorithms.       *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sort.h>

void print_array(int *a, int left, int right)
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

void copy_array(int *dst, int *src, int n)
{
  int i;

  if (!dst || !src) return;

  for (i = 0; i < n; i++) {
    dst[i] = src[i];
  }
 
  return;
}

int main()
{
  int i, n;
  int *in, *out, *tmp; /* Dynamic Arrays */
  int test_status = 0; /* Success */

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  in = (int *)malloc(2 * n * sizeof(int));
  if (!in) {
    printf("Out of memory\n");
    return -1;
  }
  tmp = in + n;
  //out = tmp + n;

  printf("Enter %d elements separated by space:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &in[i]);
  }
  printf("Array:\n");
  print_array(in, 0, n-1);

  /* Bubble Sort */
  printf("\nBubble Sort:\n");
  copy_array(tmp, in, n);
  bubblesort(tmp, n);
  print_array(tmp, 0, n-1);

  /* Insertion Sort */
  printf("\nInsertion Sort:\n");
  copy_array(tmp, in, n);
  insertionsort(tmp, n);
  print_array(tmp, 0, n-1);

  /* Heap Sort */
  printf("\nHeap Sort:\n");
  copy_array(tmp, in, n);
  heapsort2(tmp, n);
  print_array(tmp, 0, n-1);

  /* Merge Sort */
  printf("\nMerge Sort:\n");
  copy_array(tmp, in, n);
  mergesort2(tmp, n);
  print_array(tmp, 0, n-1);

  /* Quick Sort */
  printf("\nQuick Sort:\n");
  copy_array(tmp, in, n);
  quicksort(tmp, n);
  print_array(tmp, 0, n-1);

  /* Radix Sort */
  printf("\nRadix Sort:\n");
  copy_array(tmp, in, n);
  radixsort2(tmp, n);
  print_array(tmp, 0, n-1);

  free(in);
  return 0;
}
