#ifndef TTT_COOP_MT_SEMAPHORE_H
#define TTT_COOP_MT_SEMAPHORE_H

#include "../task_queue/task_queue.h"

typedef struct coop_mt_semaphore_t
{
    unsigned count;
    task_queue_t *wait_queue;
} coop_mt_semaphore_t;


// ------------------- PUBLIC COOP_MT_SEMAPHORE METHODS -------------------

void yield(); // switch_to ready_q head
void coop_mt_semaphore_create(coop_mt_semaphore_t* semaphore, unsigned count);
void coop_mt_semaphore_wait(coop_mt_semaphore_t* semaphore);
void coop_mt_semaphore_signal(coop_mt_semaphore_t* semaphore, unsigned count);
void coop_mt_semaphore_destroy(coop_mt_semaphore_t* semaphore);

#endif //TTT_COOP_MT_SEMAPHORE_H
