class Heap {
  private:
    int *H;
    int *D;
    int *P;
    void swap(int i, int j);
    void shiftUP(int i);
    void shiftDown(int i);

  public:
    Heap(int n) : hSize(0), H(new int[n]), D(new int[n]), P(new int[n]{-1}) {}
    int max();
    int hSize;
    bool empty();
    int getIndex(int vertex);
    void insert(int v, int wt);
    void del(int h);
    static void heapify(Edge *edges, int n, int i);
    static void heapSort(Edge *edges, int n);
};
