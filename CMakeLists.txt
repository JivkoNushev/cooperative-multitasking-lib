cmake_minimum_required(VERSION 3.25)
project(coop_multitasking C)

set(CMAKE_C_STANDARD 17)

enable_language(ASM_NASM)

set(ASM_SOURCES
        coop_mt/coop_multitasking.asm
)

set(SOURCES
        coop_mt/coop_multitasking.c
        coop_mt/semaphore/coop_mt_semaphore.c
        coop_mt/task_queue/task_queue.c
)

set(HEADERS
        coop_mt/coop_multitasking.h
        coop_mt/semaphore/coop_mt_semaphore.h
        coop_mt/task_queue/task_queue.h
        coop_mt/context/context.h
)

add_executable(coop_multitasking main.c
        ${ASM_SOURCES}
        ${SOURCES}
        ${HEADERS}
)
