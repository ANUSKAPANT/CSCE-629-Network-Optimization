class Queue
{
    int arr[5000];
    int f;
    int r;

public:
    Queue();
    void push(int x);
    void pop();
    int front();
    bool empty();
};