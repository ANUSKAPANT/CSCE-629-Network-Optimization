#include "queue.h"

Queue::Queue()
{
    f = 0;
    r = -1;
}

void Queue::pop()
{
    f++;
}

void Queue::push(int x)
{
    r++;
    arr[r] = x;
}

int Queue::front()
{
    return arr[f];
}

bool Queue::empty()
{
    return f > r;
}