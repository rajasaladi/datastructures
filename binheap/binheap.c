/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: binheap.c                                                          *
 * Description: Implements Binary Heap (Min Heap / Max Heap) Data Structure.  *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <binheap.h>

#define HEAP_DEFAULT_SIZE   256

struct heap_s {
  int *arr;
  int size;
  int count;
  int type; /* Min Heap or Max Heap */
};

/******************************************************************************
 *                    P R I V A T E   F U N C T I O N S                       *
 ******************************************************************************
*/

int heap_isempty(heap_t bh)
{
  return (!bh || !bh->arr || !bh->count);
}

int heap_isfull(heap_t bh)
{
  return (bh && bh->count == bh->size);
}

/******************************************************************************
 *                      P U B L I C   F U N C T I O N S                       *
 ******************************************************************************
*/

/*
 * Function
 *   Name: heap_create
 *   Description: Creates and initializes a new Binary Heap.
 *   Input: size, maximum number of elements in Binary Heap.
 *   Output: New binary heap created and initalized.
*/
heap_t heap_create(heaptype_e type, int size)
{
  heap_t bh;

  size = (size <= 0) ? HEAP_DEFAULT_SIZE : size;

  bh = (heap_t)malloc(sizeof(struct heap_s) + size * sizeof(int));
  if (bh) {
    bh->size = size;
    bh->count = 0;
    bh->type = type;
    bh->arr = (int *)(bh + 1);
  }

  return bh;
}

/*
 * Function
 *   Name: heap_destroy
 *   Description: Destroys a Binary Heap.
 *   Input: Binary heap to be destroyed.
 *   Output: None.
*/
void heap_destroy(heap_t bh)
{
  if(bh) {
    free(bh);
  }

  return;
}

/*
 * Function
 * Name: heap_minheapify
 * Description: Min Heapifies a given array at index i
 *   Heapification is the process of ensuring heap order is maintained
 *   from the given index. If any change is made to maintain heap order
 *   procedure is repeated at the child where the value at i is moved to.
 * Params:
 *   a - Array
 *   n - size of array
 *   i - index to heapify
 * Return:
 *   Returns the pointer to allocated BST data structure.
 *
*/
void heap_minheapify(int *a, int n, int i)
{
  int child, smallest, tmp;

  if (!a || n < 2 || i < 0 || i > n-1)
    return;

  child = 2*i + 1;
  while (child < n) {
    smallest = (a[child] < a[i]) ? child : i;
    if (child+1 < n && a[child+1] < a[smallest]) {
      smallest = child+1;
    }

    if (i == smallest) {
      break;
    }

    tmp = a[i]; a[i] = a[smallest]; a[smallest] = tmp;
    i = smallest; child = 2*i + 1;
  }

  return;
}

/*
 * Function
 * Name: heap_maxheapify
 * Description: Max Heapifies a given array at index i
 * Params:
 *   a - Array
 *   n - size of array
 *   i - index to heapify
 * Return:
 *   Returns the pointer to allocated BST data structure.
 *
*/
void heap_maxheapify(int *a, int n, int i)
{
  int child, largest, tmp;

  if (!a || n < 2 || i < 0 || i > n-1)
    return;

  child = 2*i + 1;
  while (child < n) {
    largest = (a[child] > a[i]) ? child : i;
    if (child+1 < n && a[child+1] > a[largest]) {
      largest = child+1;
    }

    if (i == largest) {
      break;
    }

    tmp = a[i]; a[i] = a[largest]; a[largest] = tmp;
    i = largest; child = 2*i + 1;
  }

  return;
}

/*
 * Function
 *   Name: minheap_insert
 *   Description: Inserts an element into Min Heap.
 *   Input: Element to be inserted and Min Heap.
 *   Output: None.
*/
int minheap_insert(heap_t bh, int element)
{
  int i, parent, tmp;

  if (!bh || !bh->arr) return EBADPARM;
  if (bh->size == bh->count) return EFULL;

  bh->arr[bh->count++] = element;
  i = bh->count - 1; parent = (i - 1)/2;
  while (i > 0 && bh->arr[i] < bh->arr[parent]) {
    tmp = bh->arr[i];
    bh->arr[i] = bh->arr[parent];
    bh->arr[parent] = tmp;

    i = parent; parent = (i - 1)/2;
  }

  return EOK;
}

/*
 * Function
 *   Name: maxheap_insert
 *   Description: Inserts an element into Max Heap.
 *   Input: Element to be inserted and Max Heap.
 *   Output: None.
*/
int maxheap_insert(heap_t bh, int element)
{
  int i, parent, tmp;

  if (!bh || !bh->arr) return EBADPARM;
  if (bh->size == bh->count) return EFULL;

  bh->arr[bh->count++] = element;
  i = bh->count - 1; parent = (i - 1)/2;
  while (i > 0 && bh->arr[i] > bh->arr[parent]) {
    tmp = bh->arr[i];
    bh->arr[i] = bh->arr[parent];
    bh->arr[parent] = tmp;

    i = parent; parent = (i - 1)/2;
  }

  return EOK;
}

/*
 * Function
 * Name: minheap_deletemin
 * Description: Deletes min element from Min heap and returns the same.
 * Params:
 *   bh - Binary Heap
 *   pelement - pointer to memory where min element is stored.
 * Return:
 *   EOK or error.
 *
*/
int minheap_deletemin(heap_t bh, int *pelement)
{
  if (!bh || !bh->arr || !pelement) return EBADPARM;
  if (0 == bh->count) return EEMPTY;
  if (HEAPTYPE_MAX == bh->type) return ENOTALLOWED;

  *pelement = bh->arr[0];
  bh->arr[0] = bh->arr[--bh->count];

  heap_minheapify(bh->arr, bh->count, 0);
  return EOK;
}

/*
 * Function
 * Name: maxheap_deletemax
 * Description: Deletes max element from Max heap and returns the same.
 * Params:
 *   bh - Binary Heap
 *   pelement - pointer to memory where max element is stored.
 * Return:
 *   EOK or error.
 *
*/
int maxheap_deletemax(heap_t bh, int *pelement)
{
  if (!bh || !bh->arr || !pelement) return EBADPARM;
  if (0 == bh->count) return EEMPTY;
  if (HEAPTYPE_MIN == bh->type) return ENOTALLOWED;

  *pelement = bh->arr[0];
  bh->arr[0] = bh->arr[--bh->count];

  heap_maxheapify(bh->arr, bh->count, 0);
  return EOK;
}

/*
 * Function
 * Name: minheap_getmin
 * Description: Gets min element from a Min Heap.
 * Params:
 *   bh - Binary Heap
 *   pelement - Pointer to memory where min element is stored.
 * Return:
 *   EOK or error.
 *
*/
int minheap_getmin(heap_t bh, int *pelement)
{
  if (!bh || !bh->arr || !pelement) return EBADPARM;
  if (0 == bh->count) return EEMPTY;
  if (HEAPTYPE_MAX == bh->type) return ENOTALLOWED;

  *pelement = bh->arr[0];
  return EOK;
}

/*
 * Function
 * Name: maxheap_getmax
 * Description: Gets max element from a Max Heap.
 * Params:
 *   bh - Binary Heap
 *   pelement - Pointer to memory where max element is stored.
 * Return:
 *   EOK or error.
 *
*/
int maxheap_getmax(heap_t bh, int *pelement)
{
  if (!bh || !bh->arr || !pelement) return EBADPARM;
  if (0 == bh->count) return EEMPTY;
  if (HEAPTYPE_MIN == bh->type) return ENOTALLOWED;

  *pelement = bh->arr[0];
  return EOK;
}

/*
 * Function
 * Name: heap_buildminheap
 * Description: Builds a Min Heap from the given array.
 * Params:
 *   a - Array
 *   n - size of the array.
 * Return: None
 *
*/
void heap_buildminheap(int *a, int n)
{
  int i;

  if (a) {
    for (i = n/2 - 1; i >= 0; i--) {
      heap_minheapify(a, n, i);
    }
  }
  
  return;
}

/*
 * Function
 * Name: heap_buildmaxheap
 * Description: Builds a Max Heap from the given array.
 * Params:
 *   a - Array
 *   n - size of the array.
 * Return: None
 *
*/
void heap_buildmaxheap(int *a, int n)
{
  int i;

  if (a) {
    for (i = n/2 - 1; i >= 0; i--) {
      heap_maxheapify(a, n, i);
    }
  }

  return;
}

/*
 * Function
 * Name: heap_printarray
 * Description: Prints the array of Binary Heap.
 * Params:
 *   bh - Binary Heap.
 * Return: None
 *
*/
void heap_printarray(heap_t bh)
{
  int i;

  if (!bh || !bh->arr || 0 == bh->count) {
    printf("Heap is Empty\n");
    return;
  }

  printf("Array: ");
  for (i = 0; i < bh->count; i++) {
    printf("%d ", bh->arr[i]);
  }
  printf("\n");

  return;
}

/*
 * Function
 * Name: heap_print
 * Description: Prints the Binary Heap in a tree form.
 * Params:
 *   bh - Binary Heap.
 * Return: None
 *
*/
void heap_print(heap_t bh)
{
  if (!bh) {
    printf("Heap is Empty\n");
    return;
  }

  heap_print2(bh->arr, bh->count);
  return;
}

/*
 * Function
 * Name: heap_print2
 * Description: Prints the Binary Heap in a tree form.
 * Params:
 *   a - Array
 *   size - size of array.
 * Return: None
 *
*/
void heap_print2(int *a, int size)
{
  int i, j;
  int n, nl, bl, e, b, w;

  /*
   * n - no. of elements at last level.
   * e - no of spaces within which an element is printed.
   * b - no of spaces before and after each element at last level.
   * w - total no. of characters for the last level.
   *     w = n*e + 2*n*b.
   * nl - no. of elements at a given level.
   * bl - no. of spaces before and after each element at a given level.
   *            w - nl*e
   *      bl = ----------
   *              2*nl
   * Note: A new line is printed and new bl is calculated when
   *       i = ispow(2) - 2. (ex: 0, 2, 6, 14 etc.).
   *
   * Example: (This routine prints like below without the asteriks obviously)
   *    Heap:
   *                    2               
   *            4              15       
   *        5      11      23      32   
   *     88  12  34  91  67  76  45  52 
   *
  */

  if (!a || 0 == size) {
    printf("Heap is Empty\n");
    return;
  }

  /* computing n */
  i = size; n = 1;
  i >>= 1;
  while (i) {
    n <<= 1;
    i >>= 1;
  }

  e = 2; b = 1;
  w = n*e + 2*n*b;
  nl = 1;
  bl = (w - nl*e)/(2*nl);

  printf("\nHeap:\n");
  for (i = 0; i < size; i++) {

    /* Print bl spaces before */
    for (j = 0; j < bl; j++) {
      printf(" ");
    }
    /* Print the element within e characters  */
    printf("%2d", a[i]); /* Note: Make sure n in %nd is equal to e */
    /* Print bl spaces after */
    for (j = 0; j < bl; j++) {
      printf(" ");
    }

    /* Checking if (i+2) is a power of 2 */
    if (!((i + 2) & (i + 1))) {
      nl <<= 1;
      bl = (w - nl*e)/(2*nl);
      printf("\n");
    }
  }
  printf("\n");

  return;
}
