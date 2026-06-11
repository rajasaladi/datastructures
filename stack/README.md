# Stack

Stack (LIFO) data structure implemented in three variants. All variants store
generic elements: the element size is given at create time and data is passed
in/out through `void *` pointers.

## Implementations

| File | Library | Description |
|---|---|---|
| `stack.c` | `lib/libstack.a` | Stack using a linked list |
| `stack_array.c` | `lib/libstack_array.a` | Stack using a fixed-size array |
| `stack2.c` | `lib/libstack2.a` | Two stacks sharing one array, growing toward each other |

## Public Interface

- `inc/stack.h` — single stack API: `stack_create`, `stack_destroy`,
  `stack_push`, `stack_pop`, `stack_top`, `stack_clear`, `stack_is_empty`,
  `stack_display`, `stack_custom_display`.
  Both `stack.c` and `stack_array.c` implement this same interface, so they
  are interchangeable at link time.
- `inc/stack2.h` — two-stacks-in-one-array API: `stack2_create`,
  `stack2_destroy`, `stack2_push1`/`stack2_pop1`, `stack2_push2`/`stack2_pop2`,
  `stack2_display`.

Note: the stack type is named `stack1_t` (not `stack_t`) to avoid a clash with
the POSIX signal stack type `stack_t` from `signal.h`.

## Build

```
make        # builds libraries into ../lib and executables into bin/
make clean
```

No dependencies on other modules.

## Executables

| Binary | Description |
|---|---|
| `bin/stack_test` | Tests the linked-list stack (push/pop 1000 entries, overflow/underflow checks) |
| `bin/stack_array_test` | Same tests linked against the array stack |
| `bin/stack2_test` | Tests the two-stacks-in-one-array variant |
| `bin/check_paranthesis` | Sample problem: checks if parentheses `()[]{}` in an expression are balanced, using the linked-list stack |
| `bin/check_paranthesis2` | Same problem linked against the array stack |

The test programs are self-contained. `check_paranthesis` reads an expression
from stdin:

```
echo "([]{})" | ./bin/check_paranthesis
```
