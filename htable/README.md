# Hash Table

Hash table with separate chaining (each bin holds a linked list of entries).
Keys and stored elements are integers. The number of bins is chosen at create
time.

## Implementation

| File | Library | Description |
|---|---|---|
| `htable.c` | `lib/libhtable.a` | Chained hash table |

## Public Interface

`inc/htable.h` — `htable_create`, `htable_destroy`, `htable_insert`,
`htable_delete`, `htable_find`, `htable_print`, and `htable_increment`,
which increments the element stored for a key (inserting it if absent) —
convenient for frequency counting, as used by the `frequent` sample problem.

## Build

```
make        # builds the library into ../lib and executables into bin/
make clean
```

No dependencies on other modules.

## Executables

| Binary | Description |
|---|---|
| `bin/htable_test` | Self-contained tests: 1000 inserts/finds/deletes, collisions, negative keys |
| `bin/frequent` | Sample problem: finds the most frequent element in an array using the hash table (`htable_increment`) |
| `bin/frequent_sorted` | Sample problem: finds the most frequent element in a sorted array (no hash table needed — single pass) |

## Test Inputs

The `test/` folder holds sample inputs for the sample problems. Each input
gives the element count followed by the elements:

```
./bin/frequent < test/frequent_input.txt
./bin/frequent < test/frequent_max_neg_input.txt    # negative keys
./bin/frequent_sorted < test/frequent_sorted_input.txt
```

*Documentation generated using [Claude Code](https://claude.com/claude-code).*
