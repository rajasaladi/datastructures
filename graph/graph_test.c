/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: graph_test.c                                                       *
 * Description: Implements Test module to test Graph Data Structure.          *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

#define TESTCASE               5

#define MAX_EDGES             10

typedef struct edge_input_s {
  int u;
  int v;
  int weight;
} edge_input_t;

typedef struct graph_input_s {
  char *title;
  char *desc;
  int numV;
  int numE;
  edge_input_t edges[MAX_EDGES];
} graph_input_t;


graph_input_t graphs[] = {
  /* Positive Edges */
  "Positive Edges",
  "Graph has edges with only positive weights and has no cycle",
  6, 9, {
    {0, 1, 1}, {0, 2, 2},
    {1, 3, 3}, {1, 4, 4},
    {2, 3, 5}, {2, 5, 6},
    {3, 4, 7}, {3, 5, 8},
    {4, 5, 9},
    //{5, 0, 6},
  },

  /* Positive Edges - Cycle */
  "Positive Edges with a cycle",
  "Graph has edges with only positive weights but has a cycle",
  6, 9, {
    {0, 1, 1}, {0, 2, 2},
    {1, 3, 3}, {1, 4, 4},
    {2, 3, 5}, //{2, 5, 6},
    {3, 4, 7}, {3, 5, 8},
    {4, 5, 9},
    {5, 0, 6},
  },

  /* Negative Edges */
  "Negative Edges",
  "Graph has some edges with negative weights but has no cycle",
  6, 9, {
    {0, 1, -1}, {0, 2, 2},
    {1, 3, -3}, {1, 4, 4},
    {2, 3, -5}, {2, 5, 6},
    {3, 4, 7}, {3, 5, 8},
    {4, 5, 9},
    //{5, 0, -6},
  },

  /* Negative Edges - Cycle */
  "Negative Edges with a cycle",
  "Graph has some edges with negative weights and has a cycle",
  6, 9, {
    {0, 1, -1}, {0, 2, 2},
    {1, 3, -3}, {1, 4, 4},
    {2, 3, -5}, //{2, 5, 6},
    {3, 4, 7}, {3, 5, 8},
    {4, 5, 9},
    {5, 0, -6},
  },

  /* Full Cycle */
  "Full Cycle",
  "Graph is a full cycle i.e. all edges connect with each other to form a full cycle",
  6, 6, {
    {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}, {5, 0, 1},
  },

#if 0
  /* Loop */
  "Loop",
  "Graph has a loop i.e. an edge connecting itself (at vertex 5)",
  6, 6, {
    {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}, {5, 5, 1},
  },
#endif

  /* Disconnected Graph */
  "Disconnected Graph",
  "Graph has vertices that are not connected with other vertices (4 and 5)",
  6, 4, {
    {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, /* {3, 4, 1}, */ {4, 5, 1},
  },
};

graph_t graphTestCreate(int direct, graph_input_t *graph)
{
  int i;
  graph_t g;

  g = graphCreate(direct, graph->numV, graph->numE);
  if (!g) {
    printf("Failed creating a Graph!\n");
    return NULL;
  }

  for (i = 0; i < graph->numE; i++) {
    graphAddEdge(g, graph->edges[i].u, graph->edges[i].v, graph->edges[i].weight);
  }

  return g;
}

void pathPrintRec(pathinfo_t *paths, int *visit, int size, int s, int d)
{
  if (d >= size || PATH_UNDEF == d || visit[d]) return;
  visit[d] = 1;
  if (d != s) pathPrintRec(paths, visit, size, s, paths[d].v);
  printf("%d, ", d);

  return;
}

void pathPrint(pathinfo_t *paths, int *visit, int size, int s, int d)
{
  int i;
  if (!visit) return;

  for (i = 0; i < size; i++) visit[i] = 0;

  pathPrintRec(paths, visit, size, s, d);
  return;
}

void pathPrintArr(pathinfo_t *paths, int size)
{
  int i;

  printf("Paths: ");
  if (!paths) {printf("empty\n"); return;}

  for (i = 0; i < size; i++) {
    printf("%d, ", paths[i].v);
  }
  printf("\n");

  return;
}

void graphTestTopologicalOrderTest(graph_t g, int numV)
{
  int i, j, res;
  int *arr;

  /* Topological Order */
  arr = (int *)malloc(numV * sizeof(int));
  if (arr) {
    for (i = 0; i < 2; i++) {
      res = graphTopologicalOrderBFS(g, arr, numV);
    }
    printf("Topological Order (BFS): ");
    if (!res) {
      printf("full cycle");
    } else if (res < 0) {
      printf("error(%d)", res);
    } else {
      for (j = 0; j < res; j++) {
        printf("%d, ", arr[j]);
      }
    }
    printf("\n");

    for (i = 0; i < 2; i++) {
      res = graphTopologicalOrderDFS(g, arr, numV);
    }
    printf("Topological Order (DFS): ");
    if (!res) {
      printf("full cycle");
    } else if (res < 0) {
      printf("error(%d)", res);
    } else {
      for (j = 0; j < res; j++) {
        printf("%d, ", arr[j]);
      }
    }
    printf("\n");

    free(arr);
  }

  return;
}

void graphTestShortestPathTest(graph_t g, int numV)
{
  int i, j;
  int *visit;
  pathinfo_t *paths;

  /* Shortest Path */
  paths = (pathinfo_t *)malloc(numV * sizeof(pathinfo_t));
  visit = (int *)malloc(numV * sizeof(int));
  if (paths) {
    for (i = 0; i < numV; i++) {
      printf("BFS Shortest Paths:\n");
      graphFindShortestPathsFromSource(g, i, paths, numV);
      //pathPrintArr(paths, numV);
      for (j = 0; j < numV; j++) {
        printf("(%d -> %d, ", i, j);
        if (DIST_UNDEF == paths[j].dist) {
          printf("d: -): ");
        } else {
          printf("d:%2d): ", paths[j].dist);
          pathPrint(paths, visit, numV, i, j);
        }
        printf("\n");
      }
      printf("\n");

      printf("Dijkstra's Shortest Paths:\n");
      graphDijkstraShortestPathsFromSource(g, i, paths, numV);
      //pathPrintArr(paths, numV);
      for (j = 0; j < numV; j++) {
        printf("(%d -> %d, ", i, j);
        if (DIST_UNDEF == paths[j].dist) {
          printf("d: -): ");
        } else {
          printf("d:%2d): ", paths[j].dist);
          pathPrint(paths, visit, numV, i, j);
        }
        printf("\n");
      }
      printf("\n");
    }
    free(visit);
    free(paths);
  }

  return;
}

void graphTestMinimumSpanningTreeTest(graph_t g, int numV)
{
  int i, res, dist;
  mst_t *e;

  e = (mst_t *)malloc(numV * sizeof(mst_t));
  if (e) {
    res = graphPrimsMinimumSpanningTree(g, e, numV, &dist);
    printf("Prim's Minimum Spanning Tree");
    if (!res) {
      printf(": Not exist!\n");
    } else {
      printf("(dist = %d):\n", dist);
      for (i = 0; i < res; i++) {
        printf("(%d, %d), ", e[i].u, e[i].v);
      }
      printf("\n");
    }

    res = graphKruskalsMinimumSpanningTree(g, e, numV, &dist);
    printf("Kruskal's Minimum Spanning Tree");
    if (!res) {
      printf(": Not exist!\n");
    } else {
      printf("(dist = %d):\n", dist);
      for (i = 0; i < res; i++) {
        printf("(%d, %d), ", e[i].u, e[i].v);
      }
      printf("\n");
    }
    free(e);
  }

  return;
}

int main(void)
{
  int i, numG;
  graph_input_t *gi;
  graph_t g;

  numG = sizeof(graphs)/sizeof(graphs[0]);

#define GRAPH_DIRECT_TEST         1
#if GRAPH_DIRECT_TEST
  /* Directed Graph Tests */
  for (i = 0; i < numG; i++) {
    gi = &graphs[i];
    g = graphTestCreate(GRAPH_DIRECT, &graphs[i]);
    if (!g) continue;
    printf("\nTest: %s\n", gi->title);
    printf("Desc: %s\n", gi->desc);
    graphPrintEdges(g);
    graphTestTopologicalOrderTest(g, gi->numV);
    graphTestShortestPathTest(g, gi->numV);
    graphDestroy(g);
  }
#endif

#define GRAPH_UNDIRECT_TEST         1
#if GRAPH_UNDIRECT_TEST
  /* Undirected Graph Tests */
  for (i = 0; i < numG; i++) {
    gi = &graphs[i];
    g = graphTestCreate(GRAPH_UNDIRECT, &graphs[i]);
    if (!g) continue;
    printf("\nTest: %s\n", gi->title);
    printf("Desc: %s\n", gi->desc);
    graphPrintEdges(g);
    graphTestMinimumSpanningTreeTest(g, gi->numV);
    graphDestroy(g);
  }
#endif

  return 0;
}
