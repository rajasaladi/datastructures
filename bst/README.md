# Binary Search Tree (BST) and AVL Tree

Binary search tree with integer keys and values, in two variants: a plain
(unbalanced) BST and a self-balancing AVL tree.

## Implementations

| File | Library | Description |
|---|---|---|
| `bst.c` | `lib/libbst.a` | Plain binary search tree |
| `avl.c` | `lib/libavl.a` | AVL self-balancing binary search tree |

## Public Interface

- `inc/bst.h` — `bst_create`, `bst_destroy`, `bst_height`, `bst_find`,
  `bst_findmin`/`bst_findmax`, `bst_insert`, `bst_delete`,
  `bst_deletemin`/`bst_deletemax`, `bst_delete_all`, and traversal printing:
  `bst_print_inorder`, `bst_print_preorder`, `bst_print_postorder`,
  `bst_print_levelorder`, `bst_print_tree` (tree-shaped console output).
- `inc/avl.h` — `avl_create`, `avl_destroy`, `avl_height`, `avl_find`,
  `avl_insert`, `avl_delete`, `avl_deleteall`, `avl_print`, plus `avl_check`
  which verifies the AVL balance property — useful as a self-test after a
  sequence of inserts/deletes.

## Build

This module links against the stack and queue libraries (stack for iterative
traversals, queue for level-order traversal), so build `stack` and `queue`
first — or just run `make` from the repository root, which builds everything
in dependency order.

```
make        # builds libraries into ../lib and executables into bin/
make clean
```

## Executables

| Binary | Description |
|---|---|
| `bin/bst_test` | BST tests, linked against the linked-list stack/queue |
| `bin/bst_test2` | Same tests, linked against the array stack/queue |
| `bin/avl_test` | AVL tests (sequential insert/delete with balance verification), linked-list stack/queue |
| `bin/avl_test2` | Same tests, linked against the array stack/queue |

All test programs are self-contained — just run them.
