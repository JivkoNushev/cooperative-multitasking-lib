#include <stddef.h>
#include <assert.h>
#include "coop_mt_semaphore.h"
#include "../coop_multitasking.h"

// ------------------ ASSEMBLY FUNCTIONS ------------------
extern void context_switch(context_t *old_context, context_t *new_context);
extern void switch_to(context_t *context);

// ------------------ COOP_MT_SEMAPHORE METHODS ------------------

void coop_mt_semaphore_create(coop_mt_semaphore_t* semaphore, unsigned count)
{
    semaphore->count = count;
    semaphore->wait_queue = NULL;
}

void coop_mt_semaphore_wait(coop_mt_semaphore_t* semaphore)
{
    // add to wait_queue
    context_t *old_context = sched.dispatcher.current_context;
    old_context->next = NULL;

    task_queue_add(&semaphore->wait_queue, old_context);
    while(!semaphore->count)
    {
        if (!sched.dispatcher.current_context->next)
        {
            // end of the wait queue
            // push the wait queue to the ready queue
            task_queue_add(&sched.ready, semaphore->wait_queue->tail);

            // get tail of ready queue and just switch_to
            context_t *next_context = sched_get_next_context();
            assert(next_context);

            sched.dispatcher.current_context = next_context;
            switch_to(next_context);
        }

        sched.dispatcher.current_context = sched.dispatcher.current_context->next;
        context_switch(old_context, sched.dispatcher.current_context);
    }

    // remove from the queue
    task_queue_remove(semaphore->wait_queue, sched.dispatcher.current_context);

    semaphore->count--;
}

void coop_mt_semaphore_signal(coop_mt_semaphore_t* semaphore, unsigned count)
{
    semaphore->count += count;
    // switch from wait_queue ? or just wait from the ready queue
}

void coop_mt_semaphore_destroy(coop_mt_semaphore_t* semaphore)
{
    // TODO:
    // 1?.  put cleanup functions in the contexts of the wait queue
    //      free the semaphore
    // 2?.  allow the execution of the tasks
    //      wait until wait_queue == NULL or wait_queue->head == wait_queue->head == NULL
}

