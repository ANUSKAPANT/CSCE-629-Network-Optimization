#include <iostream>
using namespace std;
#include "graph.h"
#include "heap.h"

void Heap::shiftUP(int i) {
  while ((i > 0) && (D[H[i]] > D[H[(i - 1) / 2]])) {
    swap((i - 1) / 2, i);
    i = (i - 1) / 2;
  }
}

void Heap::shiftDown(int i) {
  int l, r;
  int largest = i;
  int len = hSize;

  l = 2 * i + 1;
  if (l < len) {
    if (D[H[l]] > D[H[largest]]) {
      largest = l;
    }
  }

  r = 2 * (1 + i);
  if (r < len) {
    if (D[H[r]] > D[H[largest]]) {
      largest = r;
    }
  }

  if (largest != i) {
    swap(i, largest);
    shiftDown(largest);
  }
}

int Heap::getIndex(int vertex) {
  return P[vertex];
}

void Heap::insert(int v, int wt) {
  H[hSize] = v;
  D[v] = wt;
  hSize++;
  P[v] = hSize - 1;
  shiftUP(hSize - 1);
}

void Heap::del(int vertex) {
  int idx = P[vertex];
  int node = H[idx];
  P[node] = -1;

  if ((idx >= hSize) || (idx < 0)) {
    printf("Index %d Out of Bounds \r\n", idx);
    assert(false);
  }
  int lastIndex = hSize - 1;
  H[idx] = H[lastIndex];
  P[H[lastIndex]] = idx;
  hSize--;
  shiftDown(idx);
}

int Heap::max() {
  return H[0];
}

bool Heap::empty() {
  return (hSize <= 0);
}

void Heap::swap(int x, int y) {
  int a = H[x];
  int b = H[y];
  P[a] = y;
  P[b] = x;
  int temp = H[x];
  H[x] = H[y];
  H[y] = temp;
}

void Heap::heapify(Edge *edges, int n, int i)
{
  int smallest = i;
  int left_index = 2 * i + 1;
  int right_index = 2 * i + 2;

  if (left_index < n && edges[left_index].weight < edges[smallest].weight)
    smallest = left_index;

  if (right_index < n && edges[right_index].weight < edges[smallest].weight)
    smallest = right_index;

  if (smallest != i)
  {
    Edge temp = edges[smallest];
    edges[smallest] = edges[i];
    edges[i] = temp;
    heapify(edges, n, smallest);
  }
}

void Heap::heapSort(Edge *edges, int n)
{
  for (int i = (n / 2) - 1; i >= 0; i--)
    heapify(edges, n, i);

  for (int i = n - 1; i >= 0; i--)
  {
    Edge temp = edges[i];
    edges[i] = edges[0];
    edges[0] = temp;
    heapify(edges, i, 0);
  }
}
