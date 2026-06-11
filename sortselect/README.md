# Sort and Select

Sorting and selection algorithms over integer arrays. All sorts share the
same signature — `void sortname(int *a, int n)` — sorting the array in place
in ascending order. The selection functions return the kth element without
fully sorting the array.

## Implementations

| File | Algorithms |
|---|---|
| `bubblesort.c` | Bubble sort |
| `insertionsort.c` | Insertion sort |
| `heapsort.c` | Heap sort (`heapsort2`), heap select (`heapselect`, `heapselect2`) — built on the array-heap utilities from the `binheap` module |
| `mergesort.c` | Merge sort (`mergesort2`) |
| `quicksort.c` | Quick sort (`quicksort`), quick select (`quickselect`) |
| `radixsort.c` | Counting sort and radix sort (`radixsort2`) |

All of the sorts are archived into `lib/libsort.a`.

## Public Interface

`inc/sort.h` — `bubblesort`, `insertionsort`, `heapsort2`, `mergesort2`,
`quicksort`, `radixsort2`, and the selection functions `heapselect`,
`heapselect2`, `quickselect`.

Note: some names carry a `2` suffix because BSD libc (used by macOS) already
defines `heapsort`, `mergesort` and `radixsort` in the standard headers.

## Build

This module links against the binary heap library, so build `binheap` first —
or just run `make` from the repository root, which builds everything in
dependency order.

```
make        # builds the library into ../lib and executables into bin/
make clean
```

## Executables

| Binary | Description |
|---|---|
| `bin/sort_test` | Runs every sort algorithm on the same input array and prints each result, so they can be compared at a glance |
| `bin/kth_largest` | Sample problem: finds the kth largest element using both heap select and quick select, verifying they agree for every k |

## Test Inputs

The `test/` folder holds sample inputs of various sizes. Each input gives the
element count followed by the elements:

```
./bin/sort_test < test/input15.txt
./bin/sort_test < test/input100.txt
./bin/sort_test < test/input_sorted_descending.txt   # worst case for quicksort
./bin/kth_largest < test/kth_input15.txt
./bin/kth_largest < test/kth_input100.txt
```
