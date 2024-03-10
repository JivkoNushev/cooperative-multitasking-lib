#include <malloc.h>
#include <assert.h>
#include "task_queue.h"

// ------------------ TASK_QUEUE METHODS ------------------

int task_queue_add(task_queue_t **tq, context_t *context)
{
    if (!tq) return -1;

    if (!(*tq))
    {
        (*tq) = (task_queue_t*)malloc(sizeof(task_queue_t));
        if (!(*tq)) return -1;

        (*tq)->tail = (*tq)->head = NULL;
    }

    assert(!(*tq)->head == !(*tq)->tail);

    if (!(*tq)->head && !(*tq)->tail)
        (*tq)->tail = (*tq)->head = context;
    else
    {
        (*tq)->head->next = context;
        (*tq)->head = (*tq)->head->next;
    }

    return 0;
}

context_t* task_queue_pop(task_queue_t *tq)
{
    if (!tq) return NULL;
    if (!tq->head || !tq->tail) return NULL;

    context_t *next_context = tq->tail;
    if (tq->head == tq->tail)
        tq->head = tq->tail = NULL;
    else
        tq->tail = tq->tail->next;

    return next_context;
}

int task_queue_remove(task_queue_t *tq, context_t *context)
{
    if (!tq) return -1;
    if (!tq->tail) return -1;
    if (!context) return -1;

    context_t *iter = tq->tail;
    while(iter->next && iter->next != context) iter = iter->next;

    if(iter->next != context) return -1;

    iter->next = iter->next->next;

    return 0;
}

