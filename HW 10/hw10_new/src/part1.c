#include <stdio.h>

#include "ds_utils.h"
#include "hw10.h"
#include "time_utils.h"

static double benchmark_stack_fill(const int data[DATA_SIZE])
{
    int repeat = 0;
    int i = 0;
    double start_time = 0.0;
    double end_time = 0.0;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        stack* temp_stack = NULL;
        for (i = 0; i < DATA_SIZE; ++i)
        {
            push_stack(&temp_stack, data[i]);
        }
        free_stack(temp_stack);
    }
    end_time = get_time_ms();

    return end_time - start_time;
}

static double benchmark_queue_fill(const int data[DATA_SIZE])
{
    int repeat = 0;
    int i = 0;
    double start_time = 0.0;
    double end_time = 0.0;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        queue* temp_queue = NULL;
        for (i = 0; i < DATA_SIZE; ++i)
        {
            enqueue(&temp_queue, data[i]);
        }
        free_queue(temp_queue);
    }
    end_time = get_time_ms();

    return end_time - start_time;
}

static double benchmark_bst_fill(const int data[DATA_SIZE])
{
    int repeat = 0;
    int i = 0;
    double start_time = 0.0;
    double end_time = 0.0;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        bst* temp_bst = NULL;
        for (i = 0; i < DATA_SIZE; ++i)
        {
            bst_insert(&temp_bst, data[i]);
        }
        free_bst(temp_bst);
    }
    end_time = get_time_ms();

    return end_time - start_time;
}

void fill_structures(stack** stack_, queue** queue_, bst** bst_, int data[DATA_SIZE])
{
    int i = 0;
    double stack_ms = 0.0;
    double queue_ms = 0.0;
    double bst_ms = 0.0;

    *stack_ = NULL;
    *queue_ = NULL;
    *bst_ = NULL;

    stack_ms = benchmark_stack_fill(data);
    queue_ms = benchmark_queue_fill(data);
    bst_ms = benchmark_bst_fill(data);

    for (i = 0; i < DATA_SIZE; ++i)
    {
        push_stack(stack_, data[i]);
    }
    for (i = 0; i < DATA_SIZE; ++i)
    {
        enqueue(queue_, data[i]);
    }
    for (i = 0; i < DATA_SIZE; ++i)
    {
        bst_insert(bst_, data[i]);
    }

    printf("\n==================== PART 1: FILL STRUCTURES ====================\n");
    printf("(Total of %d runs, computation only)\n", BENCH_REPEAT);
    printf("| Structures      | Stack | Queue  | BST   |\n");
    printf("| :-------------- | :---- | :----- | :---- |\n");
    printf("| Total Time (ms) | %.3f | %.3f  | %.3f |\n", stack_ms, queue_ms, bst_ms);
}
