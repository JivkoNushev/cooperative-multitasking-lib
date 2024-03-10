#include <stdio.h>

#include "coop_mt/coop_multitasking.h"
#include "coop_mt/semaphore/coop_mt_semaphore.h"


void first_task()
{
    for(int i = 0; i < 5; i++)
    {
        printf("In tasklet1, iteration: %d\n", i);
        sched_task_switch();
    }
}


void second_task()
{
    for(int i = 0; i < 5; i++)
    {
        printf("In tasklet2, iteration: %d\n", i);
        sched_task_switch();
    }
}

coop_mt_semaphore_t s;
void third_task()
{
    coop_mt_semaphore_wait(&s);

    printf("semaphore caught\n");
}


int main()
{
    sched_init();
    coop_mt_semaphore_create(&s, 0);

    sched_task_run(first_task);
    sched_task_run(second_task);
    sched_task_run(third_task);

    for(int i = 0; i < 5; i++)
    {
        printf("In main, iteration: %d\n", i);
        sched_task_switch();
    }

//    coop_mt_semaphore_signal(&s, 1);

    return 0;
}
