# Graph

Graph data structure using an adjacency list (an array of vertices, each with
a linked edge list). Supports directed and undirected graphs with weighted
edges, and implements several classic graph algorithms on top.

## Implementations

| File | Library | Description |
|---|---|---|
| `graph.c` | `lib/libgraph.a` | Graph and the algorithms listed below |
| `gheap.c` / `gheap.h` | (same library) | Internal min-heap keyed for graph use (priority queue for Dijkstra/Prim's); not part of the public interface |

## Public Interface

`inc/graph.h`:

- `graphCreate(direct, numV, numE)` — `GRAPH_DIRECT` or `GRAPH_UNDIRECT`
- `graphAddEdge(g, v, w, weight)`
- `graphTopologicalOrderBFS` / `graphTopologicalOrderDFS` — topological sort
  (directed acyclic graphs)
- `graphFindShortestPath(g, v, w)` — shortest path between two vertices
- `graphFindShortestPathsFromSource` — single-source shortest paths,
  unweighted (BFS)
- `graphDijkstraShortestPathsFromSource` — single-source shortest paths,
  weighted (Dijkstra)
- `graphPrimsMinimumSpanningTree` / `graphKruskalsMinimumSpanningTree` —
  minimum spanning tree, returning the edge list and total distance
- `graphPrint`, `graphPrintEdges`

Path results are returned through `pathinfo_t` (distance and predecessor
vertex) arrays; MST results through `mst_t` (edge endpoints) arrays. The
constants `DIST_UNDEF`, `VERTEX_UNDEF`, `PATH_UNDEF` mark unreachable
vertices.

## Build

This module links against the queue, stack and disjoint-set libraries (BFS
uses the queue, DFS the stack, Kruskal's the disjoint set), so build `stack`,
`queue` and `disjset` first — or just run `make` from the repository root,
which builds everything in dependency order.

```
make        # builds the library into ../lib and executables into bin/
make clean
```

## Executables

| Binary | Description |
|---|---|
| `bin/graph_test` | Self-contained tests: builds sample graphs and exercises topological ordering, shortest paths (unweighted and Dijkstra) and both MST algorithms |

Just run it — no input files needed.
