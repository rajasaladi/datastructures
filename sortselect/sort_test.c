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
void arrayPrint(int *a, int left, int right)
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
void arrayCopy(int *dst, int *src, int n)
{
  int i;

  if (!dst || !src) return;

  for (i = 0; i < n; i++) {
    dst[i] = src[i];
  }

  return;
}

/* Returns 0 if arrays a and b are element-wise identical, 1 otherwise */
int arrayCmp(int *a, int *b, int n)
{
  int i;

  for (i = 0; i < n; i++) {
    if (a[i] != b[i]) return 1;
  }

  return 0;
}

/* Verifies result against the reference (bubble sort) output */
int verify_sort(char *name, int *result, int *expected, int n)
{
  if (arrayCmp(result, expected, n)) {
    printf("Test failed! %s result does not match expected sorted order\n", name);
    return 1;
  }

  return 0;
}

int main()
{
  int i, n;
  int test_status = 0; /* Success */
  int *inputArr, *tmpArr, *expected; /* Dynamic Arrays */

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  inputArr = (int *)malloc(n * sizeof(int));
  tmpArr = (int *)malloc(n * sizeof(int));
  expected = (int *)malloc(n * sizeof(int));
  if (!inputArr || !tmpArr || !expected) {
    printf("Out of memory\n");
    free(inputArr);
    free(tmpArr);
    free(expected);
    return -1;
  }

  printf("Enter %d elements separated by space:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &inputArr[i]);
  }
  printf("Array:\n");
  arrayPrint(inputArr, 0, n-1);

  /* Bubble Sort -- used as the reference result for the other algorithms */
  printf("\nBubble Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  bubblesort(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  arrayCopy(expected, tmpArr, n);

  /* Insertion Sort */
  printf("\nInsertion Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  insertionsort(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Insertion Sort", tmpArr, expected, n);

  /* Selection Sort */
  printf("\nSelection Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  selectionsort(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Selection Sort", tmpArr, expected, n);

  /* Heap Sort */
  printf("\nHeap Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  heapsort2(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Heap Sort", tmpArr, expected, n);

  /* Merge Sort */
  printf("\nMerge Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  mergesort2(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Merge Sort", tmpArr, expected, n);

  /* Quick Sort */
  printf("\nQuick Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  quicksort(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Quick Sort", tmpArr, expected, n);

  /* Radix Sort */
  printf("\nRadix Sort:\n");
  arrayCopy(tmpArr, inputArr, n);
  radixsort2(tmpArr, n);
  arrayPrint(tmpArr, 0, n-1);
  test_status |= verify_sort("Radix Sort", tmpArr, expected, n);

  if (!test_status) {
    printf("\nAll sort algorithms produced correct results!\n");
  }

  free(inputArr);
  free(tmpArr);
  free(expected);
  return test_status;
}
