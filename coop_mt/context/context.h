#ifndef COOP_MULTITASKING_CONTEXT_H
#define COOP_MULTITASKING_CONTEXT_H

typedef struct context_t
{
    char stack[1 << 14]; // 16KB
    void *sp;
    struct context_t *next; // for the wait queue
} context_t;

#endif //COOP_MULTITASKING_CONTEXT_H
