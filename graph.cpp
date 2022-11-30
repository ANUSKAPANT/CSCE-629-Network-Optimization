#include <stdlib.h>
#include "graph.h"
#include <iostream>

void Graph::init()
{
  for (int i = 0; i < n; ++i) {
    edges[i] = new Node(i, 0);
  }
}

void Graph::addEdge(int s, int t, int weight = RAND_BW)
{
  Node *src = new Node(s, weight);
  Node *dest = new Node(t, weight);

  Node *x = edges[s];
  while (x->next != NULL)
    x = x->next;
  x->next = dest;

  Node *y = edges[t];
  while (y->next != NULL)
    y = y->next;
  y->next = src;
}

bool Graph::isEdge(int s, int t)
{
  Node *x = edges[s];
  while (x != NULL) {
    if (x->vertex == t)
      return true;
    x = x->next;
  }
  return false;
}

void Graph::generateGraph1()
{
  int deg[5000] = {0};
  init();

  for (int i = 0; i < n; i++)
  {
    int j = (i + 1) % n;
    addEdge(i, j);
    deg[i]++;
    deg[j]++;
  };

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (deg[i] == 6) break;
      int x = rand() % n;
      if (!isEdge(i, x))
      {
        if(deg[i] < degree && deg[x] < degree) {
          addEdge(i, x);
          deg[i] = deg[i] + 1;
          deg[x] = deg[x] + 1;
        }
      }
    }
  }
}

void Graph::generateGraph2()
{
  init();
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    addEdge(i, j);
  };

  for (int i = 0; i < n; i++) {
    int j = 0;
    int num = ((percent*n/100)*0.5 - 50) + rand() % 100;
    while(j < num) {
      int x = rand() % n;
      if (!isEdge(i, x) && i != x) {
        addEdge(i, x);
        j++;
      }
      else j--;
    }
  }
}
