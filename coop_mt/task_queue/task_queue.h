#ifndef TTT_COOP_MT_TASK_QUEUE_H
#define TTT_COOP_MT_TASK_QUEUE_H

#include "../context/context.h"

typedef struct task_queue
{
    context_t *head, *tail;
} task_queue_t;

// ------------------- PUBLIC TASK_QUEUE METHODS -------------------

int task_queue_add(task_queue_t **tq, context_t *context);
context_t* task_queue_pop(task_queue_t *tq);
int task_queue_remove(task_queue_t *tq, context_t *context);

#endif // TTT_COOP_MT_TASK_QUEUE_H