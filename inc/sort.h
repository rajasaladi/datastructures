/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: sort.h                                                             *
 * Description: Defines interface for Sorting Algorithms.                     *
 * Created: Mar 2019                                                          *
*******************************************************************************
*/
#ifndef SORT_H
#define SORT_H
#include <err.h>

void bubblesort(int *a, int n);
void insertionsort(int *a, int n);
/*
 * NOTE:
 *   Using 2 suffix below to some of the function names due to name conflict
 *   with default implementations on mac.
 *   Hence heapsort2(), heapselect2() etc.
*/
void heapsort2(int *a, int n);
void mergesort2(int *a, int n);
void quicksort(int *a, int n);
void radixsort2(int *a, int n);

/* Select */
int heapselect(int *a, int n, int k);
int heapselect2(int *a, int n, int k);
int quickselect(int *a, int n, int k);

#endif /* SORT_H */
