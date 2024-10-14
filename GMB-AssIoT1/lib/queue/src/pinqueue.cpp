
#include "pinqueue.h"

static unsigned char *volatile queue;
static int rear;
static int front;
static size_t queue_size;

void queue_init(size_t queue_t_size)
{
    front = -1;
    rear = -1;
    queue_size = queue_t_size;
    queue = (unsigned char *)malloc(queue_size * sizeof(unsigned char));
}

bool is_full(void)
{
    return ((size_t)rear) == ((queue_size - 1));
}

bool is_empty(void)
{
    return front == -1;
}

void enqueue(unsigned char pin)
{
    if (!is_full())
    {
        if (front == -1)
        {
            front = 0;
        }
        rear++;
        queue[rear] = pin;
    }
}

void dequeue(void)
{
    if (!is_empty())
    {
        front++;
        if (front > rear)
        {
            front = rear = -1;
        }
    }
}

unsigned char peek(void)
{
    if (!is_empty())
    {
        return queue[front];
    }
    else
    {
        return -1;
    }
}

void queue_empty(void){
    front = -1;
    rear = -1;
}

void queue_destroy(void)
{
    if (queue != NULL) 
    {
        free(queue);
        queue = NULL;
    }
}