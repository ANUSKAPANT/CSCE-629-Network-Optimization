#include <iostream>
#include <algorithm>
using namespace std;

#include "graph.h"
#include "heap.h"
#include "routingAlgorithm.h"
#include "queue.h"

const int infinite = std::numeric_limits<int>::max();
int max_bwidth = infinite;
Edge edgesToSort[5000*5000];

int Find(int *dad, int v) {
  int w = v;
  while(dad[w] != -1) {
    w = dad[w];
  }
  return w;
}

void Union(int r1, int r2, int *dad, int *rank) {
  if (rank[r1] < rank[r2]) {
    dad[r1] = r2;
  }
  else if (rank[r2] < rank[r1]) {
    dad[r2] = r1;
  } else {
    rank[r1]++;
    dad[r2] = r1;
  }
}

void MakeSet(int *dad, int *rank, int vertex) {
  dad[vertex] = -1;
  rank[vertex] = 0;
}

void BFS(Graph G, int src, int dest, int *parent, int *bw)
{
  int visited[5000] = {0};
  
  Queue Q;
  Q.push(src);
  bw[src] = infinite;
  visited[src] = 1;
  parent[src] = -1;

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    Node * i = G.edges[u]->next;
    while(i != NULL) {
      int v = i->vertex;
      int wt = i->weight;
      if (visited[v] == 0)
      {
        visited[v] = 1;
        Q.push(v);
        bw[v] = wt;
        parent[v] = u;
      }
      i = i->next;
    }
  }
}

int kruskalHeap(Graph G, int s, int t) {
  int n = G.n;
  Graph GSpanTree(n);
  GSpanTree.init();
  int numEdges = 0;

  int *dad = new int[n];
  int *rank = new int[n];

  for(int i = 0; i < n; i++) {
    MakeSet(dad, rank, i);
  }

  // create an array of edges
  for(int i = 0; i < n; i++) {
    Node *j = G.edges[i]->next;
    while (j != NULL)
    {
      int v = j->vertex;
      int wt = j->weight;
      if (i < v) {
        edgesToSort[numEdges] = Edge(i, v, wt);
        numEdges++;
      }
      j = j->next;
    }
  }

  Heap::heapSort(edgesToSort, numEdges);

  int r1, r2, v1, v2;
  for (int i = 0; i < numEdges; i++) {
    Edge x = edgesToSort[i];
    v1 = x.startVertex;
    v2 = x.endVertex;

    r1 = Find(dad, v1);
    r2 = Find(dad, v2);
    if (r2 != r1)
    {
      GSpanTree.addEdge(v1, v2, x.weight);
      Union(r1, r2, dad, rank);
    }
  }

  int *parent = new int[n];
  int *bw = new int[n];
  for(int i = 0; i < n; i++) {
    parent[i] = 0;
    bw[i] = 0;
  }

  BFS(GSpanTree, s, t, parent, bw);

  int pathSize = 0;
  int path[5000] = {0};
  int x = t;
  while (parent[x] != -1) {
    path[pathSize] = x;
    x = parent[x];
    pathSize++;
  }
  path[pathSize] = s;

  if (!(pathSize <= 0))
  {
    int maxbw = infinite;
    for (int i = pathSize; i >= 0; i--)
    {
      maxbw = min(maxbw, bw[path[i]]);
    }
    cout << s;
    for (int i = pathSize - 1; i >= 0; i--)
    {
      cout << " ->" << path[i];
    }
    cout << " " <<endl;
    return maxbw;
  }
  return 0;
}

