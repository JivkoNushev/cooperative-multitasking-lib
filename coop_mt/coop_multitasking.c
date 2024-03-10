#include <malloc.h>
#include <assert.h>
#include "coop_multitasking.h"

// ------------------ ASSEMBLY FUNCTIONS ------------------
extern void load_current_sp(context_t *context);
extern void task_context_create(context_t *context, void (*f)(), void (*clean)());
extern void switch_to(context_t *context);
extern void context_switch(context_t *old_context, context_t *new_context);



// ------------------ SCHEDULER METHODS ------------------

int sched_init()
{
    // init dispatcher with current context
    context_t *main_context = (context_t*)malloc(sizeof(context_t));
    if (!main_context) return -1;

    load_current_sp(main_context);

    sched.dispatcher = (dispatcher_t) {
            .current_context = main_context
    };
    sched.ready = NULL;

    return 0;
}

context_t* sched_get_next_context()
{
    // TODO: maybe call other queues
    return task_queue_pop(sched.ready);
}

void sched_task_clean()
{
    // free current context and switch to another context
    context_t *next_context = sched_get_next_context();
    assert(next_context);

    free(sched.dispatcher.current_context);
    sched.dispatcher.current_context = NULL;

    switch_to(next_context);
}

int sched_task_run(void (*f)())
{
    // create new context
    context_t *new_context = (context_t*)malloc(sizeof(context_t));
    if (!new_context) return -1;

    new_context->sp = new_context->stack + sizeof(new_context->stack);
    new_context->next = NULL;

    // push sched_task_clean() to ret addr
    // push f() to stack ret addr
    task_context_create(new_context, f, sched_task_clean);

    // push new task to ready_queue
    task_queue_add(&sched.ready, new_context);

    return 0;
}

void sched_task_switch()
{
    // get next context
    context_t *next_context = sched_get_next_context();
    if (!next_context) return;

    // push current context to ready_queue
    context_t *old_context = sched.dispatcher.current_context;
    old_context->next = NULL;
    task_queue_add(&sched.ready, old_context);

    // switch to new context
    sched.dispatcher.current_context = next_context;
    context_switch(old_context, sched.dispatcher.current_context);
}