/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: binheap_test.c                                                     *
 * Description: Implements Test module to test Binary Heap Data Structure.    *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <binheap.h>

int main()
{
  int i, n, e1, e2;
  heap_t bh1, bh2;

  printf("Enter the number of elements for binary heap: ");
  scanf("%d", &n);

  bh1 = heap_create(HEAPTYPE_MIN, n);
  bh2 = heap_create(HEAPTYPE_MAX, n);

  if (NULL == bh1 || NULL == bh2) {
    heap_destroy(bh1);
    heap_destroy(bh2);
    printf("Initialization failed..\n");
    return 1;
  }

  printf("Please enter %d elements separated by space:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &e1);
    printf("\nInsert(%d)\n", e1);

    /* Min Heap */
    minheap_insert(bh1, e1);
    heap_print(bh1);

    /* Max Heap */
    maxheap_insert(bh2, e1);
    heap_print(bh2);
  }

  for (i = 0; i < n; i++) {
    /* Min Heap */
    minheap_deletemin(bh1, &e1);
    maxheap_deletemax(bh2, &e2);
    printf("\nDeleteMin(%d),DeleteMax(%d)\n", e1, e2);
    heap_print(bh1);
    heap_print(bh2);
  }

  heap_destroy(bh1);
  heap_destroy(bh2);

  return 0;
}
