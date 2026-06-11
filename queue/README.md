# Queue

Queue (FIFO) data structure implemented in two variants. Elements are generic:
the element size is given at create time and data is passed in/out through
`void *` pointers.

## Implementations

| File | Library | Description |
|---|---|---|
| `queue.c` | `lib/libqueue.a` | Queue using a linked list |
| `queue_array.c` | `lib/libqueue_array.a` | Circular queue using a fixed-size array |

## Public Interface

`inc/queue.h` — `queue_create`, `queue_destroy`, `queue_enqueue`,
`queue_dequeue`, `queue_length`, `queue_display` (takes a caller-supplied
display callback so any element type can be printed).

Both implementations provide the same interface, so they are interchangeable
at link time. Other modules in this repository (e.g. `bst`, `graph`) link
against these libraries for level-order/breadth-first traversals.

## Build

```
make        # builds libraries into ../lib and executables into bin/
make clean
```

No dependencies on other modules.

## Executables

| Binary | Description |
|---|---|
| `bin/queue_test` | Tests the linked-list queue (1000 inserts/deletes, full/empty conditions) |
| `bin/queue_test2` | Same tests linked against the array queue |

Both test programs are self-contained — just run them.

*Documentation generated using [Claude Code](https://claude.com/claude-code).*
