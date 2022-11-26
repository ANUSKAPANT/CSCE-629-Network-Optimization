#include <iostream>
#define BOUND_BW 4096                   // to add weights in range [1,4096]
#define RAND_BW (rand() % BOUND_BW + 1) // Add 1, weight may not be 0.
class Node {
  public:
    int vertex;
    int weight;
    Node *next;
    Node() {}
    Node(int v, int e) : vertex(v), weight(e), next(NULL) {}
};

class Graph {
  public:
    int n;
    int degree;
    int percent;
    Node **edges;
    Graph(int num) : n(num), edges(new Node *[num]) {}
    Graph(int num, int deg, int prob) : n(num), degree(deg), percent(prob), edges(new Node *[num]) {}
    void init();
    void generateGraph1();
    void generateGraph2();
    void addEdge(int u, int v, int wt);
    bool isEdge(int s, int t);
};

// for edge sort in kruskal
class Edge {
  public:
    int startVertex;
    int endVertex;
    int weight;
    
    Edge() {}
    Edge(int u, int v, int bw) : startVertex(u), endVertex(v), weight(bw) {}
};
