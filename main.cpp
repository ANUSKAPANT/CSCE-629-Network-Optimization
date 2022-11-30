#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <chrono>
#include <iomanip>
using namespace std;

#include "graph.h"
#include "routingAlgorithm.h"


double report_d[50] = {0};
double report_dh[50] = {0};
double report_k[50] = {0};
int source[50] = {0};
int destination[50] = {0};

double test(Graph G, int s, int t, int (*algorithm) (Graph G , int, int))
{
  clock_t start = 0; // start point of running time
  double time;
  int bw = 0; // bandwidth
  start = clock();
  printf("\nMaximum Bandwidth Path: \n");
  bw = algorithm(G, s, t);
  time = (clock() - start) / (double)CLOCKS_PER_SEC;
  printf("\nMax Bandwidth: %d \r\n", bw);
  printf("Time: %lf \r\n", time);
  return time*1000;
}

void testLoop(Graph G, int n, int loop) {
  int src, dest;
  /* loop for different s,t pairs. */
  for (int test_case = 1; test_case <= 5; test_case++) {
    src = rand() % n + 1; // random  source node
    dest = rand() % n + 1; // random destination node
    int index = test_case + 5*loop - 1;
    source[index] = src;
    destination[index] = dest; 

    printf("\r\n=== \r\n");
    printf("Pair #%d\r\n", test_case);
    printf("Source=%d ------ Destination=%d\r\n", src, dest);

    // Test Dijkstra using non heap structure
    printf("\r\n");
    printf("****** DIJKSTRA ****** \r\n");
    report_d[index] = test(G, src, dest, dijkstra);

    // Test Dijkstra using heap structure
    printf("\r\n");
    printf("***** DIJKSTRA HEAP *****\r\n");
    report_dh[index] = test(G, src, dest, dijkstraHeap);

    // Test Kruskal using heap structure
    printf("\r\n");
    printf("********* KRUSKAL ******** \r\n");
    report_k[index] = test(G, src, dest, kruskalHeap);
  }
}

void printReport(int num) {
  cout << "Graph #"<<(num + 25) / 25<< endl;
  cout << "-----------------------------------------------------------------------------------------------" << endl;
  cout << " | " << setw(10) << "GRAPH #";
  cout << " | " << setw(10) << "SOURCE";
  cout << " | " << setw(12) << "DESTINATION";
  cout << " | " << setw(10) << "DIJKSTRA";
  cout << " | " << setw(18) << "DIJKSTRA HEAP";
  cout << " | " << setw(10) << "KRUSKAL";
  cout << " | " << endl;
  cout << "-----------------------------------------------------------------------------------------------" << endl;

  for (int i = num; i < num+25; i++)
  {
    cout << setw(9) << "G" << (i+5) / 5;
    int w = 10;
    cout << setw(15) << source[i] << setw(2);
    cout << setw(12) << destination[i] << setw(5);
    cout << setw(15) << report_d[i] << setw(2);
    cout << setw(18) << report_dh[i] << setw(9);
    cout << setw(18) << report_k[i] << setw(2)<< endl;
  }
  cout << "-------------------------------------------------------------------------------------------------" << endl;
}


int main()
{
  int n = 5000;    // Number of vertices
  int degree = 6; // average vertex degree for sparse graphs
  int percent = 20; // percent probability of adjacent vertices in dense graphs


  srand(time(NULL));

  for(int i = 1; i <= 5; i++) {
    Graph G1(n, degree, percent);
    cout << "Generating Graph #1........" << endl;
    G1.generateGraph1();

    printf("----------------GRAPH#1 RUNNING FOR 5 PAIRS OF SOURCE AND DESTINATION--------------------");
    testLoop(G1, n, i-1);
  }

  for(int i = 1; i <= 5; i++) {
    Graph G2(n, degree, percent);
    cout << "Generating Graph #2........" << endl;
    G2.generateGraph2();

    printf("----------------GRAPH#2 RUNNING FOR 5 PAIRS OF SOURCE AND DESTINATION--------------------");
    testLoop(G2, n, 5+i-1);
  }
  cout << "-------------------------------------------------------------------------------------------------" << endl;
  printReport(0);
  printReport(25);
  return 0;
}