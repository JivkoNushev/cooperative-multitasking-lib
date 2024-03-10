    %macro push_nonvolatile 0
        push    rbx
        push    rbp
        push    r12
        push    r13
        push    r14
        push    r15
    %endmacro

    %macro pop_nonvolatile 0
            pop    r15
            pop    r14
            pop    r13
            pop    r12
            pop    rbp
            pop    rbx
    %endmacro

    struc context
        .stack:     resb    1 << 14
        .sp:        resq    1
        .next:      resq    1
    endstruc

segment .text

    global load_current_sp ; void load_current_sp(context_t *context);
    global task_context_create ; void task_context_create(context_t *context, void (*f)(), void (*clean)());
    global switch_to ; void switch_to(context_t *context);
    global context_switch ; void context_switch(context_t *old_context, context_t *new_context);


load_current_sp:
    mov     [rdi + context.sp], rsp

    mov     rax, rsp
    ret

task_context_create:
    push_nonvolatile
    mov     rax, rsp

    mov     rsp, [rdi + context.sp]
    push    rdx
    push    rsi
    push_nonvolatile

    mov     [rdi + context.sp], rsp
    mov     rsp, rax
    pop_nonvolatile
    ret

switch_to:
    mov     rsp, [rdi + context.sp]

    pop_nonvolatile
    ret

context_switch:
    push_nonvolatile

    mov     [rdi + context.sp], rsp
    mov     rsp, [rsi + context.sp]

    pop_nonvolatile
    ret
