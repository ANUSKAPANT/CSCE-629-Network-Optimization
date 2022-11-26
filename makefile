CC = g++
CFLAGS  = -g -std=c++11

all : graph
graph: main.cpp graph.cpp heap.cpp dijkstra.cpp  kruskal.cpp queue.cpp
	$(CC) $(CFLAGS) -o graph main.cpp graph.cpp heap.cpp dijkstra.cpp kruskal.cpp queue.cpp
clean:
	rm -rf graph

