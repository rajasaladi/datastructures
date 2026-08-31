/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: kth_largest.c                                                      *
 * Description: Finds kth largest element using heap select and quick select. *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
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
  int i, n, k, eh, eq;
  int *a, *b; /* Dynamic Array */
  int test_status = 0; /* Success */
  char *kth[10] = { "th", "st", "nd", "rd", "th", "th", "th", "th", "th", "th"};

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  a = (int *)malloc(2 * n * sizeof(int));
  if (!a) {
    printf("Out of memory\n");
    return -1;
  }
  b = a + n;

  printf("Enter %d elements separated by space:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  printf("Array:\n");
  print_array(a, 0, n-1);

  /* Heap Select */
  printf("\nHeap Select:\n");
  for (k = 1; k <= n; k++) {
    copy_array(b, a, n);
    eh = heapselect(b, n, k);
    printf("%d%s largest element is %d\n", k, kth[k % 10], eh);
  }
  print_array(b, 0, n-1);

  /* Heap Select 2 */
  printf("\nHeap Select2:\n");
  for (k = 1; k <= n; k++) {
    copy_array(b, a, n);
    eh = heapselect2(b, n, k);
    printf("%d%s largest element is %d\n", k, kth[k % 10], eh);
  }
  print_array(b, 0, n-1);

  /* Quick Select */
  printf("\nQuick Select:\n");
  for (k = 1; k <= n; k++) {
    copy_array(b, a, n);
    eq = quickselect(b, n, k);
    printf("%d%s largest element is %d\n", k, kth[k % 10], eq);
  }
  print_array(b, 0, n-1);

  /* Compare */
  for (k = 1; k <= n; k++) {
    copy_array(b, a, n);
    eh = heapselect(b, n, k);
    copy_array(b, a, n);
    eq = quickselect(b, n, k);
    if (eh != eq) {
      printf("Test failed!\n");
      printf("%d%s largest, heapselect=%d is not equal to quickselect=%d\n",
                                                           k, kth[k % 10], eh, eq); 
      test_status = 1; /* Failure */
      break;
    }
  }

  if (!test_status) {
    printf("\nTest is Successful\n");
  }

  free(a);
  return test_status;
}
