/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: quicksort.c                                                        *
 * Description: Implements Quick Sort and Quick Select Algorithms.            *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>

#define QUICKSORT_LAST_PIVOT          0
#define QUICKSORT_SKIP_CHECK          0

/*
 * Hoare Partition Scheme
 *  - Invented by C.A.R. Hoare.
 *  - Also, used in Mark Allen Weiss Data Structures Book.
*/
int partition(int *a, int low, int high)
{
  int i, j, pivot, tmp;
  
#if QUICKSORT_LAST_PIVOT
  /* Simply picking last element as pivot */
  pivot = a[high];
#else
  /* Pick a pivot index.
   * Other options are:
   *  - Randomization (i.e. a random element between low and high is used) or
   *  - Median (i.e. median of first, last and middle elements).
   *  - Middle (or simply middle element. Also, the option chosen in this implementation).
  */
  i = (low + high)/2;

  /* Swap the pivot with last element
  */
  pivot = a[i]; a[i] = a[high]; a[high] = pivot;
#endif

  i = low;
  j = high - 1; /* Skipping last element, as it has been moved in between low and high */
  
  while (1) {
    while (a[i] < pivot) i++;
#if QUICKSORT_SKIP_CHECK
    while (a[j] > pivot) j--;
    if (j < low) printf("Warning! right is out-of-bound %d < (%d, %d)\n", j, low, high);
#else
    /* Alternatively, a check can be made in second while loop,
     * so as to make sure j does not progress back beyond low
     * ex: while (j > i && a[j] > pivot) j--;
    */
    while (j > i && a[j] > pivot) j--;
#endif

    if (i >= j) break;

    /* Swap elements so that lesser element moves to the left and
     * larger element moves to the right of the pivot
    */
    tmp = a[i]; a[i] = a[j]; a[j] = tmp;
    i++; j--;
  }
  
  a[high] = a[i];
  a[i] = pivot;
  
  return i;
}

#if 0
/* Older implementation - Needs to be Removed */
int partition(int *a, int left, int right)
{
  int j, tmp, p, pivot;
  int i;

  i = left;
  /* Pick a pivot element */
  p = (left + right)/2;
  pivot = a[p];

  /* Swap pivot with right most element */
  a[p] = a[right];
  j = right;
  a[right--] = pivot;

  /* Walk thru the array */
  while (1) {
    while (a[left] < pivot)
      left++;
    while (a[right] > pivot)
      right--;

    if (right < i) printf("Warning! right is out-of-bound %d < (%d, %d)\n", right, i, j);
    if (left > j) printf("Warning! left is out-of-bound %d > (%d, %d)\n", left, i, j);

    if (left < right) {
      /* Swap the elements */
      tmp = a[left];
      a[left] = a[right];
      a[right] = tmp;
      left++;
      right--;
    }
    else
      break;
  }

  /* Swap pivot with left element */
  //tmp = a[j];
  a[j] = a[left];
  //a[left] = tmp;
  a[left] = pivot;

  return left;
}
#endif

/*
 * Lomuto Partition Scheme
 *  - Invented by Nico Lomuto
 *  - Popularized by
 *    -  Bentley in his book Programming Pearls and
 *    -  Cormen et al. (CLRS - Introduction to Algorithms)
*/
int partition2(int *a, int low, int high)
{
  int i, j;
  int pivot, tmp;

  /* Pick a pivot index. In randomized approach, as described in CLRS, this
   * would be a random number picked between low and high (both inclusive).
   * Here, I am picking the middle element as pivot.
  */
  i = (low + high)/2;

  /* Make a copy of the pivot and place last element in the place of pivot
  */
  pivot = a[i]; a[i] = a[high];

  /* Note: j progresses from low -> high-1 skipping the last element as it has
   *       been placed between low and high-1 (both inclusive) in above statement.
  */
  for (i = j = low; j < high; j++) {
    if (a[j] <= pivot) {
      tmp = a[i]; a[i] = a[j]; a[j] = tmp;
      i++;
    }
  }
  a[high] = a[i]; a[i] = pivot;

  return i;
}

/* Quick Sort - Internal Recursive function */
void qsort(int *a, int low, int high)
{
  int index;

  if (low < high) {
    index = partition(a, low, high);
    qsort(a, low, index - 1);
    qsort(a, index + 1, high);
  }

  return;
}

/* Quick Sort */
void quicksort(int *a, int n)
{
  if (!a || n < 2) return;
  return qsort(a, 0, n-1);
}

/* QSelect - Internal Recursive function to find kth smallest element */
static int qselect (int *a, int k, int left, int right)
{
  int index;

  if (left == right) return a[left];

  index = partition(a, left, right);
  /* Repeat on left sub-array */
  if (k - 1 < index) return qselect(a, k, left, index - 1);
  /* Repeat on right sub-array */
  if (k - 1 > index) return qselect(a, k, index + 1, right);

  return a[index];
}

/* QSelect2 - Internal Iterative function to find kth smallest element */
static int qselect2 (int *a, int n, int k)
{
  int index, left, right;

  k--; left = 0; right = n - 1;
  while (left < right) {
    index = partition(a, left, right);
    if (k == index) break;
    if (k > index) {
      left = index + 1;
    } else {
      right = index - 1;
    }
  }

  return a[k];
}

/* QuickSelect - kth largest element */
int quickselect (int *a, int n, int k)
{
  if (k < 1 || k > n) return -1;

  /* kth largest is (n-k+1)th smallest element */
  return qselect2(a, n, n-k+1);
}
