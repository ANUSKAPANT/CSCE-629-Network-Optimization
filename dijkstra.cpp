#include <iostream>
#include <algorithm>
using namespace std;

#include "graph.h"
#include "heap.h"
#include "routingAlgorithm.h"

/* Infinite value is declared as the maximum value that int can hold*/
const int infinite = std::numeric_limits<int>::max();

const int IN_TREE = 2;
const int FRINGE = 1;
const int UNSEEN = 0; 

void pathTraversal(int *dad, int t)
{
  if (dad[t] == -1)
  {
    std::cout << t;
    return;
  }
  else
  {
    /* Recurse with the dad of the vertex */
    pathTraversal(dad, dad[t]);
  }
  std::cout << "->" << t;
  return;
}

bool fringes(int *status)
{
  for (int i = 0; i < 5000; i++)
  {
    if (status[i] == FRINGE)
      return true;
  }
  return false;
}

/* Implementation of Dijkstra without using Heap structure */
int dijkstra(Graph G, int s, int t)
{
  int n = 5000;
  int *status = new int[n];
  int *maxbw = new int[n];
  int *dad = new int[n];

  for (int i = 0; i < n; i++)
  {
    status[i] = UNSEEN;
    maxbw[i] = 0;
    dad[i] = -1;
  }

  // maxbw[t] will contains the maximum bandwidth
  maxbw[s] = infinite;
  status[s] = IN_TREE;
  Node *i = G.edges[s]->next;
  while (i != NULL)
  {
    int w = i->vertex;
    dad[w] = s;
    maxbw[w] = i->weight;
    status[w] = FRINGE;
    i = i->next;
  }

  /* check every fringe, add the one with max bandwidth */
  while (fringes(status))
  {
    int weight_max = 0;
    int vertex_max = 0;
    int i = 0;
    for (int i = 0; i < n; i++)
    {
      if ((status[i] == FRINGE) && (weight_max < maxbw[i]))
      {
        vertex_max = i;
        weight_max = maxbw[i];
      }
    }

    if (vertex_max != -1)
    {
      int v = vertex_max;
      status[v] = IN_TREE;
      Node *i = G.edges[v]->next;
      while (i != NULL)
      {
        int w = i->vertex;
        int wt = i->weight;
        if (status[w] == UNSEEN)
        {
          status[w] = FRINGE;
          dad[w] = v;
          maxbw[w] = min(maxbw[v], wt); // update the max bandwidth value here
        }
        else if ((maxbw[w] < min(maxbw[v], wt)) && (status[w] == FRINGE))
        {
          maxbw[w] = min(maxbw[v], wt);
          dad[w] = v;
        }
        i = i->next;
      }
    }
    else
    {
      return 0;
    }
  }

  pathTraversal(dad, t);
  cout<<" " <<endl;
  return maxbw[t];
}

/* Implementation of Dijkstra using Heap structure */
int dijkstraHeap(Graph G, int s, int t)
{
  int n = 5000;
  int *status = new int[n];
  int *maxbw = new int[n];
  int *dad = new int[n];

  for(int i = 0; i < 5000; i++) {
    status[i] = UNSEEN;
    maxbw[i] = 0;
    dad[i] = -1;
  }

  /* init max heap structure*/
  Heap heapDijkstra(n);
  maxbw[s] = infinite;
  status[s] = IN_TREE;

  Node *i = G.edges[s]->next;
  while (i != NULL) {
    int w = i->vertex;
    dad[w] = s;
    maxbw[w] = i->weight;
    status[w] = FRINGE;

    /*Insert a node in the heap*/
    heapDijkstra.insert(w, maxbw[w]);
    i = i->next;
  }

  while (!heapDijkstra.empty())
  {
    int maxBWfringe = heapDijkstra.max();
    heapDijkstra.del(maxBWfringe);

    int v = maxBWfringe;
    status[v] = IN_TREE;
    Node *j = G.edges[v]->next;
    while (j != NULL) {
      int w = j->vertex;
      int wt = j->weight;
      if (status[w] == UNSEEN)
      {
        dad[w] = v;
        status[w] = FRINGE;
        maxbw[w] = min(maxbw[v], wt);
        heapDijkstra.insert(w, maxbw[w]);
      }
      else if (status[w] == FRINGE)
      {
        if (maxbw[w] < min(maxbw[v], wt))
        {
          heapDijkstra.del(w);
          dad[w] = v;
          maxbw[w] = min(maxbw[v], wt);
          heapDijkstra.insert(w, maxbw[w]);
        }
      }
      j = j->next;
    }
  }

  pathTraversal(dad, t);
  cout << " " << endl;
  return maxbw[t];
}
