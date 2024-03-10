#ifndef TTT_COOP_MULTITASKING_H
#define TTT_COOP_MULTITASKING_H

#include "task_queue/task_queue.h"

typedef struct dispatcher
{
    context_t *current_context;
    // task_queue *wait_q; ??
} dispatcher_t;

typedef struct sched_t
{
    dispatcher_t dispatcher;
    task_queue_t *ready;
} sched_t;

sched_t sched;

// ------------------- PUBLIC SCHEDULER METHODS -------------------

int sched_init();
int sched_task_run(void (*t)());
void sched_task_switch();
context_t* sched_get_next_context();



#endif //TTT_COOP_MULTITASKING_H
