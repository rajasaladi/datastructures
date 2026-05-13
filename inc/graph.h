/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: graph.h                                                            *
 * Description: Defines interface for Graph Datastructure.                    *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <err.h>
#include <limits.h>

#define GRAPH_DIRECT             1  /* Directed Graph */
#define GRAPH_UNDIRECT           0  /* Undirected Graph */

#define DIST_MAX                 INT_MAX
#define DIST_UNDEF               DIST_MAX
#define VERTEX_UNDEF             -1
#define PATH_UNDEF               VERTEX_UNDEF 

typedef struct graph_s *graph_t;
typedef struct pathinfo_s {
  int dist;
  int v;
} pathinfo_t;

typedef struct mst_s {
  int u;
  int v;
} mst_t;

graph_t graphCreate(int direct, int numV, int numE);
void graphDestroy(graph_t g);
void graphAddEdge(graph_t g, int v, int w, int weight);
int graphTopologicalOrderBFS(graph_t g, int *tp, int size);
int graphTopologicalOrderDFS(graph_t g, int *tp, int size);
int graphFindShortestPath(graph_t g, int v, int w);
int graphFindShortestPathsFromSource(graph_t g, int v, pathinfo_t *path, int size);
int graphDijkstraShortestPathsFromSource(graph_t g, int v, pathinfo_t *path, int size);
int graphPrimsMinimumSpanningTree(graph_t g, mst_t *mst, int size, int *pDist);
int graphKruskalsMinimumSpanningTree(graph_t g, mst_t *mst, int size, int *pDist);
void graphPrint(graph_t g);
void graphPrintEdges(graph_t g);

#endif /* GRAPH_H */
