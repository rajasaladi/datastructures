/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: frequent_sorted.c                                                  *
 * Description: Implements algorithm to find the most frequent element in a   *
 *              sorted array.                                                 *
 * Created: Jun 2018                                                          *
*******************************************************************************
*/
#include <stdio.h>

int most_frequent_element_sorted(int *a, int n, int *pfreq)
{
  int max_count, count, most, i;

  if (!a || n < 1) {
    return -1;
  }

  max_count = count = 1;
  most = a[0]; i = 0;
  do {
    i++;
    if (n == i || a[i] != a[i - 1]) {
      if (count > max_count) {
        max_count = count;
        most = a[i - 1];
      }
      count = 1;
    } else {
      count++;
    }
  } while (i < n);

  if (pfreq) {
    *pfreq = max_count;
  }

  return most;
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
    printf("Most frequent element is %d (%d)\n",
                  most_frequent_element_sorted(a, n, &freq), freq);
  }
  else {
    printf("Error..\nNumber of elements cannot be greater than 100\n");
    ret = 1;
  }

  return ret;
}
