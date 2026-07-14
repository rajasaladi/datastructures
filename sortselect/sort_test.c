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

/* Prints array */
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

/* Copies elements from src array to dst array */
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
  int test_status = 0; /* Success */
  int *inputArr, *tmpArr; /* Dynamic Arrays */

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  inputArr = (int *)malloc(n * sizeof(int));
  tmpArr = (int *)malloc(n * sizeof(int));
  if (!inputArr || !tmpArr) {
    printf("Out of memory\n");
    free(inputArr);
    free(tmpArr);
    return -1;
  }

  printf("Enter %d elements separated by space:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &inputArr[i]);
  }
  printf("Array:\n");
  print_array(inputArr, 0, n-1);

  /* Bubble Sort */
  printf("\nBubble Sort:\n");
  copy_array(tmpArr, inputArr, n);
  bubblesort(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  /* Insertion Sort */
  printf("\nInsertion Sort:\n");
  copy_array(tmpArr, inputArr, n);
  insertionsort(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  /* Heap Sort */
  printf("\nHeap Sort:\n");
  copy_array(tmpArr, inputArr, n);
  heapsort2(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  /* Merge Sort */
  printf("\nMerge Sort:\n");
  copy_array(tmpArr, inputArr, n);
  mergesort2(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  /* Quick Sort */
  printf("\nQuick Sort:\n");
  copy_array(tmpArr, inputArr, n);
  quicksort(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  /* Radix Sort */
  printf("\nRadix Sort:\n");
  copy_array(tmpArr, inputArr, n);
  radixsort2(tmpArr, n);
  print_array(tmpArr, 0, n-1);

  free(inputArr);
  free(tmpArr);
  return 0;
}
