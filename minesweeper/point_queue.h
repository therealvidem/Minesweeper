#ifndef POINT_QUEUE_H
#define POINT_QUEUE_H

#include "include/point.h"
#ifndef NDEBUG
#include <assert.h>
#endif
#include <stdlib.h>

typedef struct PointNode
{
    struct PointNode *next;
    Point point;
} PointNode;

typedef struct
{
    struct PointNode *head;
    struct PointNode *tail;
} PointQueue;

// Allocates and initializes a PointQueue.
// This means it must eventually be freed using FreePointQueue().
PointQueue *CreatePointQueue();

// Returns true if `queue` has no elements, false otherwise.
bool IsPointQueueEmpty(PointQueue *queue);

// Note: `queue` MUST NOT be empty in order to call this function,
// otherwise it will fail. Check to make sure !IsPointQueueEmpty()
// before using this function.
// Returns the point at the front of the queue.
Point PeekPointQueue(PointQueue *queue);

// Returns true on successful enqueue (allocated successfully), false otherwise
bool EnqueuePointQueue(PointQueue *queue, Point point);

// Note: `queue` MUST NOT be empty in order to call this function,
// otherwise it will fail. Check to make sure !IsPointQueueEmpty()
// before using this function.
Point DequeuePointQueue(PointQueue *queue);

void FreePointQueue(PointQueue *queue);

#endif
