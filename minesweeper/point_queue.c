#include "point_queue.h"

PointQueue *CreatePointQueue()
{
    PointQueue *newQueue = (PointQueue *)malloc(sizeof(PointQueue));
    newQueue->head = NULL;
    newQueue->tail = NULL;
    return newQueue;
}

bool IsPointQueueEmpty(PointQueue *queue)
{
    return queue->head == NULL;
}

void EnqueuePointQueue(PointQueue *queue, Point point)
{
    if (queue->head == NULL)
    {
        PointNode *newPointNode = malloc(sizeof(PointNode));
        newPointNode->next =  NULL;
        newPointNode->point = point;
        queue->head = newPointNode;
        queue->tail = newPointNode;
    }
    else
    {
        PointNode *newPointNode = malloc(sizeof(PointNode));
        newPointNode->next = NULL;
        newPointNode->point = point;
        queue->tail->next = newPointNode;
        queue->tail = newPointNode;
    }
}

Point DequeuePointQueue(PointQueue *queue)
{
#ifndef NDEBUG
    assert(IsPointQueueEmpty(queue) == false);
#endif
    Point dequeuedPoint = queue->head->point;
    if (queue->head == queue->tail)
    {
        free(queue->head);
        queue->head = queue->tail = NULL;
    }
    else
    {
        PointNode *next = queue->head->next;
        free(queue->head);
        queue->head = next;
    }
    return dequeuedPoint;
}

void FreePointQueue(PointQueue *queue)
{
    if (queue != NULL)
    {
        PointNode *curr = queue->head;
        PointNode *tmp;
        while (curr != NULL)
        {
            tmp = curr->next;
            free(curr);
            curr = tmp;
        }
    }
}
