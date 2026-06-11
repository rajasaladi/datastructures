# Binary Heap

Binary heap of integers supporting both min-heap and max-heap behavior. The
heap type is chosen at create time (`HEAPTYPE_MIN` or `HEAPTYPE_MAX`). In
addition to the heap object API, the module exposes array-based heap
utilities (`heapify`, `buildheap`) that operate directly on a caller's array —
these are used by the heap sort implementation in `sortselect`.

## Implementation

| File | Library | Description |
|---|---|---|
| `binheap.c` | `lib/libbinheap.a` | Binary heap (min/max) plus array heap utilities |

## Public Interface

`inc/binheap.h`:

- Heap object: `heap_create(type, size)`, `heap_destroy`, `heap_print`
  (tree-shaped console output), `heap_print_array`.
- Min heap: `minheap_insert`, `minheap_getmin`, `minheap_deletemin`.
- Max heap: `maxheap_insert`, `maxheap_getmax`, `maxheap_deletemax`.
- Array utilities (no heap object needed): `heap_minheapify`,
  `heap_maxheapify`, `heap_buildminheap`, `heap_buildmaxheap`, `heap_print2`.

## Build

```
make        # builds the library into ../lib and executables into bin/
make clean
```

No dependencies on other modules. The `sortselect` module depends on this
library, so build this one first (the top-level Makefile already does).

## Executables

| Binary | Description |
|---|---|
| `bin/binheap_test` | Inserts elements into a min heap and a max heap side by side, printing both as trees after every insert, then drains them with paired DeleteMin/DeleteMax |

## Test Inputs

The `test/` folder holds sample inputs. Each input gives the element count
followed by the elements:

```
./bin/binheap_test < test/bh_input15.txt
./bin/binheap_test < test/bh_input63.txt
./bin/binheap_test < test/bh_input100.txt
```

*Documentation generated using [Claude Code](https://claude.com/claude-code).*
