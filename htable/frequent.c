/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: frequent.c                                                         *
 * Description: Implements algorithm to find the most frequent element in an  *
 *              Array using Hash Table.                                       *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <htable.h>

int most_frequent_element(int *a, int n, int *pfreq)
{
  int i, count, max_count = 0, most;
  htable_t h;
  int num_bins;

  //num_bins = n/10;
  //num_bins = 1009;
  num_bins = 109;  /* Prime number */

  h = htable_create(num_bins);
  for (i = 0; i < n; i++) {
    htable_increment(h, a[i], &count);
    if (count > max_count) {
      max_count = count;
      most = a[i];
    }
  }
  htable_print(h);
  htable_destroy(h);

  if (pfreq) {
    *pfreq = max_count;
  }
  return most;
}

void printArr(int *a, int n) {
  int i;

  if (!a || n < 1) {
    printf("Array is Empty!\n");
    return;
  }

  printf("%d, ", a[0]);
  for (i = 1; i < n; i++) {
    printf("%d, ", a[i]);
  }
  printf("\n");
  return;
}

int main()
{
  int a[100];
  int i, n, freq;
  int ret = 0;

  printf("Enter the number of elements: ");
  scanf("%d", &n);

  if (n <= 100) {
    printf("Enter the elements separated by space:\n");
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    printArr(a, n);
    printf("Most frequent element is %d (%d)\n",
                   most_frequent_element(a, n, &freq), freq);
  }
  else {
    printf("Error..\nNumber of elements > 100\n");
    ret = 1;
  }

  return ret;
}
