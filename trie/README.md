# Trie

Trie (prefix tree) for storing words over the lowercase alphabet `a`–`z`
(26 children per node). Supports exact-word lookup as well as prefix lookup.

## Implementation

| File | Library | Description |
|---|---|---|
| `trie.c` | `lib/libtrie.a` | Trie with 26-way branching |

## Public Interface

`inc/trie.h` — `trie_create`, `trie_destroy`, `trie_add`, `trie_delete`,
`trie_find` (exact word match), `trie_find_prefix` (matches if any stored
word starts with the given prefix), `trie_num_words`, `trie_print`.

## Build

```
make        # builds the library into ../lib and executables into bin/
make clean
```

No dependencies on other modules.

## Executables

| Binary | Description |
|---|---|
| `bin/trie_test` | Self-contained tests: adds a set of words, verifies word and prefix lookups, deletes words and re-verifies, checks the word count |

Just run it — no input files needed.

*Documentation generated using [Claude Code](https://claude.com/claude-code).*
