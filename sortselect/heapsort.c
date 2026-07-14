/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: heapsort.c                                                         *
 * Description: Implements Heap Sort and Heap Select Algorithms.              *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <binheap.h>

/* Note:
 *   Function name has 2 appended at the end to avoid
 *   conflict with heapsort present in some default libraries.
 * Time complexity: O(N Log N)
 * Space complexity: O(1)
*/
void heapsort2(int *a, int n)
{
  int i, tmp;

  if (!a || n < 2)
    return;

  /* 1. Build Max Heap */
  heap_buildmaxheap(a, n);

  /* 2. In a loop of i = n-1 to 1,
   *   a. As 0th element is the max element, we swap 0th element with last
   *      element i.e. ith element. With this the max element is placed in its
   *      location.
   *   b. Now leaving the last (ith) element, maxheapify the heap at index 0
   *      for the remaining elements in the heap i.e. 0 to i - 1 elements.
   *      With this the swapped element will be moved to its appropriate
   *      location in the heap and heap's order is maintained.
  */
  for (i = n-1; i > 0; i--) {
    /* swap a[0] and a[i] */
    tmp = a[0]; a[0] = a[i]; a[i] = tmp;
    heap_maxheapify(a, i, 0);
  }

  return;
}

/* kth largest - building heap within the array
 * Note:
 *   Re-orders elements in the input array.
 *
 * Time complexity: O(N Log K)
 * Space complexity: O(1)
*/
int heapselect(int *a, int n, int k)
{
  int i, e;

  /* Build min heap with first k elements */
  heap_buildminheap(a, k);

  /* Walking thru the remainder of elements replace if new element is larger
   * than minimum element in the heap.
  */
  e = a[0]; /* min element */
  for (i = k; i < n; i++) {
    if (a[i] > e) {
      /* Swap */
      a[0] = a[i];
      a[i] = e;
      heap_minheapify(a, k, 0);
      /* Update kth largest element */
      e = a[0];
    }
  }

  return e;

}

/* kth largest - using a separate heap
 * Note:
 *   Useful when elements in input array cannot be re-ordered.
 *
 * Time complexity: O(N Log K)
 * Space complexity: O(K)
*/
int heapselect2(int *a, int n, int k)
{
  heap_t bh;
  int i, e;

  bh = heap_create(HEAPTYPE_MIN, k);
  if (NULL == bh)
    return -1;

  /* Build min heap with first k elements */
  for (i = 0; i < k; i++) {
    minheap_insert(bh, a[i]);
  }

  /* Walking thru the remainder of elements replace if new element is larger
   * than minimum element in the heap.
  */
  minheap_getmin(bh, &e);
  for (; i < n; i++) {
    if (a[i] > e) {
      minheap_deletemin(bh, &e);
      minheap_insert(bh, a[i]);
      minheap_getmin(bh, &e);
    }
  }

  heap_destroy(bh);
  return e;
}
