# Disjoint Set (Union-Find)

Disjoint set data structure over the integers `0` to `num-1`, supporting
union and find operations. Used by the `graph` module for Kruskal's minimum
spanning tree algorithm (cycle detection).

## Implementation

| File | Library | Description |
|---|---|---|
| `disjset.c` | `lib/libdisjset.a` | Disjoint set |

## Public Interface

`inc/disjset.h` — `disjsetCreate(num)` creates `num` singleton sets,
`disjsetUnion(s, a, b)` merges the sets containing `a` and `b`,
`disjsetFind(s, a)` returns the representative of `a`'s set,
`disjsetPrint`, `disjsetDestroy`.

Two elements are in the same set exactly when `disjsetFind` returns the same
representative for both.

## Build

```
make        # builds the library into ../lib and executables into bin/
make clean
```

No dependencies on other modules. The `graph` module depends on this library,
so build this one first (the top-level Makefile already does).

## Executables

| Binary | Description |
|---|---|
| `bin/disjset_test` | Self-contained test: unions all even numbers into one set and all odd numbers into another, then verifies membership of every element |

Just run it — no input files needed.

*Documentation generated using [Claude Code](https://claude.com/claude-code).*
