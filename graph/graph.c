/******************************************************************************
 * Author: Rajasekhar Saladi                                                  *
 * Module: graph.c                                                            *
 * Description: Implements Graph Data Structure.                              *
 * Created: Aug 2019                                                          *
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <queue.h>
#include <stack.h>
#include <gheap.h>
#include <disjset.h>

#define MARK_NONE           0
#define MARK_TEMP           1
#define MARK_PERM           2

#define MAX_EDGES           100
#define MAX_VERTICES        10

typedef struct enode_s enode;
struct enode_s {
  enode *next;
  int v;
  int weight;
};

typedef struct edge_s {
  int u;
  int v;
  int weight;
} edge_t;

typedef struct vnode_s {
  /* vertex info */
  int inDegree;    /* in-degree of the node */
  enode *elist;    /* adjacent edge list */

  /* Temporary Variables */
  int curInDegree; /* place used to copy in-degree and modify during topological order computation */
  int inQ;         /* Used during shortest path comupation to check whether the vertex is in queue already */
  int dqCount;     /* Dequeue count of the vertex, used during compuation of shortest path with -ve edges */
  int mark;        /* mark used to check if the node has been visited in DFS topological order computation */
  int prev;
  int dist;
} vnode;

struct graph_s {
  int direct; /* non-zero -> digraph */
  int numE;
  int numV;
  vnode *vlist;
  edge_t *edges;
};

void graph_queue_display(void *p)
{
  printf("%d, ", *(int *)p);
}

graph_t graphCreate(int direct, int numV, int numE)
{
  int i;
  graph_t g;

  if (numV < 1) numV = MAX_VERTICES;
  if (numE < 1) numE = MAX_EDGES;
  g = (graph_t)malloc(sizeof(struct graph_s) + numV * sizeof(vnode) + numE * sizeof(edge_t));
  if (!g) return NULL;

  g->direct = direct;
  g->numV = numV;
  g->vlist = (vnode *)(g + 1);
  for (i = 0; i < numV; i++) {
    g->vlist[i].elist = NULL;
    g->vlist[i].inDegree = 0;
  }
  g->numE = 0;
  g->edges = (edge_t *)(g->vlist + numV);

  return g;
}

void graphDestroy(graph_t g)
{
  int i;
  enode *p, *tmp;

  if (!g) return;

  for (i = 0; i < g->numV; i++) {
    p = g->vlist[i].elist;
    while (p) {
      tmp = p->next;
      free(p);
      p = tmp;
    }
  }
  free(g);

  return;
}

void graphAddEdge(graph_t g, int u, int v, int weight)
{
  enode *p, *q;

  if (!g || u >= g->numV || v >= g->numV) return;

  p = (enode *)malloc(sizeof(enode));
  if (!p) return;

  if (!g->direct) {
    q = (enode *)malloc(sizeof(enode));
    if (!q) {free(p); return;}
  }

  /* Adding edge */
  p->v = v; p->weight = weight;
  p->next = g->vlist[u].elist;
  g->vlist[u].elist = p;
  g->vlist[v].inDegree++;

  /* Undirected graph - Adding reverse edge */
  if (!g->direct) {
    q->v = u; q->weight = weight;
    q->next = g->vlist[v].elist;
    g->vlist[v].elist = q;
    g->vlist[u].inDegree++;
  }

  /* Copying to edge array */
  g->edges[g->numE].u = u;
  g->edges[g->numE].v = v;
  g->edges[g->numE].weight = weight;
  g->numE++;

  return;
}

void graphTpDFS(int *tp, vnode *vlist, int v, int *pCount)
{
  enode *p;

  if (vlist[v].mark) return;

  vlist[v].mark = MARK_TEMP;
  p = vlist[v].elist;
  while (p) {
    graphTpDFS(tp, vlist, p->v, pCount);
    p = p->next;
  }
  vlist[v].mark = MARK_PERM;
  //printf("index = %d, ", *pCount);
  tp[*pCount] = v;
  --*pCount;

  return;
}

int graphTopologicalOrderDFS(graph_t g, int *tp, int size)
{
  int i, j, count, tmp;

  if (!g || !tp || size < g->numV) return -1;

  for (i = 0; i < g->numV; i++) {
    g->vlist[i].mark = MARK_NONE;
  }

  count = g->numV - 1;
  for (i = 0; i < g->numV; i++) {
    graphTpDFS(tp, g->vlist, i, &count);
  }

  return g->numV - count - 1;
}

/*
 * Returns number of elements copied to tp array
 *  - Negative number in case of error
*/
int graphTopologicalOrderBFS(graph_t g, int *tp, int size)
{
  int i, j, count, len;
  enode *p;
  queue_t q;

  if (!g || !tp || size < g->numV) return -1;

  q = queue_create(g->numV, sizeof(int));
  if (!q) return -1;

  for (i = 0; i < g->numV; i++) {
    //printf("inDeg[%d] = %d, ", i, g->vlist[i].inDegree);
    g->vlist[i].curInDegree = g->vlist[i].inDegree;
    if (!g->vlist[i].inDegree) queue_enqueue(q, (void *)&i);
  }

  count = 0;
  while ((len = queue_length(q))) {
    //printf("qlen: %d\n", len);
    queue_dequeue(q, &i);
    tp[count++] = i;

    p = g->vlist[i].elist;
    while (p) {
      j = p->v;
      if (!(--g->vlist[j].curInDegree)) queue_enqueue(q, (void *)&j);
      p = p->next;
    }
  }
  queue_destroy(q);

  return count;
}

/* A BFS algorithm to solve shortest path problem with weighted paths */
int graphFindShortestPathsFromSource(graph_t g, int v, pathinfo_t *paths, int size)
{
  int i, w;
  enode *p;
  queue_t q;

  if (!g || !paths || size < g->numV) return -1;

  q = queue_create(g->numV, sizeof(int));
  if (!q) return -1;

  for (i = 0; i < g->numV; i++) {
    paths[i].dist = DIST_UNDEF;
    paths[i].v = PATH_UNDEF;
    g->vlist[i].inQ = g->vlist[i].dqCount = 0;
  }

  paths[v].dist = 0;
  paths[v].v = v;
  queue_enqueue(q, (void *)&v);
  g->vlist[v].inQ = 1;
  while(queue_length(q)) {
    queue_dequeue(q, (void *)&v);
    g->vlist[v].inQ = 0;
    if(++g->vlist[v].dqCount > g->numV) {
      break;
    }
    p = g->vlist[v].elist;
    while (p) {
      w = p->v;
      if (paths[v].dist + p->weight < paths[w].dist) {
        paths[w].dist = paths[v].dist + p->weight;
        paths[w].v = v;
        if (!g->vlist[w].inQ) {
          queue_enqueue(q, (void *)&w);
          g->vlist[w].inQ = 1;
        }
      }
      p = p->next;
    }
  }
  queue_destroy(q);

  return g->numV;
}

int graphSmallestUnmarkedVertex(graph_t g, pathinfo_t *paths)
{
  int i, res, min;
  vnode *vlist;

  vlist = g->vlist;
  res = -1; min = DIST_UNDEF;
  for (i = 0; i < g->numV; i++) {
    if (!vlist[i].mark && paths[i].dist < min) {
      min = paths[i].dist;
      res = i;
    }
  }

  return res;
}

int graphDijkstraShortestPathsFromSource(graph_t g, int v, pathinfo_t *paths, int size)
{
  int i, w, count = 0;
  enode *p;
  vnode *vlist;

  if (!g || !paths || size < g->numV) return -1;

  vlist = g->vlist;
  for (i = 0; i < g->numV; i++) {
    vlist[i].mark = 0;
    paths[i].v = PATH_UNDEF;
    paths[i].dist = DIST_UNDEF;
  }

  paths[v].v = v;
  paths[v].dist = 0;
  while ((v = graphSmallestUnmarkedVertex(g, paths)) >= 0) {
    count++;
    p = vlist[v].elist;
    while (p) {
      w = p->v;
      if (paths[v].dist + p->weight < paths[w].dist) {
        paths[w].dist = paths[v].dist + p->weight;
        paths[w].v = v;
      }
      p = p->next;
    }
    vlist[v].mark = 1;
  }

  return g->numV;
}

int graphSmallestUnmarkedVertex2(graph_t g)
{
  int i, res, min;
  vnode *vlist;

  vlist = g->vlist;
  res = -1; min = DIST_UNDEF;
  for (i = 0; i < g->numV; i++) {
    if (!vlist[i].mark && vlist[i].dist < min) {
      min = vlist[i].dist;
      res = i;
    }
  }

  return res;
}

/*
 * Returns the number of entries copied in the mst array.
 *  - Returns 0, if no MST.
*/
int graphPrimsMinimumSpanningTree(graph_t g, mst_t *mst, int size, int *pDist)
{
  int i, j, v, w, dist;
  enode *p;
  vnode *vlist;

  if (!g || !mst || size < g->numV - 1) return -1;

  vlist = g->vlist;
  for (i = 0; i < g->numV; i++) {
    vlist[i].mark = 0;
    vlist[i].prev = PATH_UNDEF;
    vlist[i].dist = DIST_UNDEF;
  }

  vlist[0].dist = 0;
  while ((v = graphSmallestUnmarkedVertex2(g)) >= 0) {
    p = vlist[v].elist;
    while (p) {
      w = p->v;
      if (!vlist[w].mark && p->weight < vlist[w].dist) {
        vlist[w].dist = p->weight;
        vlist[w].prev = v;
      }
      p = p->next;
    }
    vlist[v].mark = 1;
  }

  dist = 0;
  for (i = 0, j = 0; i < g->numV; i++) {
    if (PATH_UNDEF != vlist[i].prev) {
      dist += vlist[i].dist;
      mst[j].u = vlist[i].prev;
      mst[j].v = i;
      j++;
    }
  }
  if (pDist) *pDist = dist;

  return (j == g->numV - 1) ? j : 0;
}

int graphKruskalsMinimumSpanningTree(graph_t g, mst_t *mst, int size, int *pDist)
{
  /*
   * Algorithm:
   * 1. Create a disjoint set of the vertices.
   * 2. Create a minheap of the edges based on their weight.
   * 3. In a loop,
   *    a. delete the smallest weight edge from the minheap
   *    b. check if the vertices belong to the same disjoint set.
   *    c. If they don't belong to the same set then
   *       i. merge both vertices into single disjoint set.
   *       ii. copy the edge into list of edges of minimum spanning tree.
   *       iii. increment the count of the edges in MST.
   *    d. repeat the above steps until number of edges in MST is not
   *       equal to number of vertices - 1.
   * 4. Return the list of edges in MST.
   */

  int i, u, v, weight, count, dist;
  disjset_t set;
  heap_t minh;
  edge_t *edges;

  if (!g || !mst || size < g->numV - 1) return -1;

  set = disjsetCreate(g->numV);
  if (!set) return ENOMEMORY;

  minh = heap_create(HEAPTYPE_MIN, g->numE);
  if (!minh) {disjsetDestroy(set); return ENOMEMORY;}

  edges = g->edges;
  for (i = 0; i < g->numE; i++) {
    heap_insert(minh, edges[i].weight, edges[i].u, edges[i].v);
  }

  count = 0; dist = 0;
  while (count != g->numV - 1) {
    if(heap_deletemin(minh, &weight, &u, &v)) break;
    if (disjsetFind(set, u) != disjsetFind(set, v)) {
      disjsetUnion(set, u, v);
      mst[count].u = u;
      mst[count].v = v;
      dist += weight;
      count++;
    }
  }
  if (pDist) *pDist = dist;

  heap_destroy(minh);
  disjsetDestroy(set);

  return (count == g->numV - 1) ? count : 0;
}

void graphPrint(graph_t g)
{
  int i, count;
  enode *p;

  printf("Graph: ");
  if (!g) {
    printf("empty!\n"); return;
  }

  printf("\n");
  for (i = count = 0; i < g->numV; i++) {
    p = g->vlist[i].elist;
    while (p) {
      printf("%d -> %d (%d), ", i, p->v, p->weight);
      p = p->next;
    }
    printf("\n");
  }
  printf("\n");

  return;
}

void graphPrintEdges(graph_t g)
{
  int i;

  printf("Graph: ");
  if (!g) {
    printf("empty!\n"); return;
  }

  for (i = 0; i < g->numE; i++) {
    printf("(%d, %d, %d), ", g->edges[i].u, g->edges[i].v, g->edges[i].weight);
  }
  printf("\n");

  return;
}
