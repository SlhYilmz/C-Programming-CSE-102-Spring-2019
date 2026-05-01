#include <stdio.h>

#include "hw10.h"
#include "time_utils.h"

static int copy_stack_to_array(const stack* list_head, int values[DATA_SIZE])
{
    int index = 0;
    const stack* iter = list_head;

    while ((iter != NULL) && (index < DATA_SIZE))
    {
        values[index] = iter->data;
        iter = iter->next;
        ++index;
    }

    return index;
}

static int copy_queue_to_array(const queue* queue_head, int values[DATA_SIZE])
{
    int index = 0;
    const queue* iter = queue_head;

    while ((iter != NULL) && (index < DATA_SIZE))
    {
        values[index] = iter->data;
        iter = iter->next;
        ++index;
    }

    return index;
}

static void sort_descending(int values[DATA_SIZE], int size)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 0; i < size - 1; ++i)
    {
        for (j = i + 1; j < size; ++j)
        {
            if (values[i] < values[j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
}

static void print_array(const int values[DATA_SIZE], int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        if (i > 0)
        {
            printf(", ");
        }
        printf("%d", values[i]);
    }
}

static void fill_bst_descending(const bst* bst_, int values[DATA_SIZE], int* index)
{
    if ((bst_ == NULL) || (*index >= DATA_SIZE))
    {
        return;
    }

    fill_bst_descending(bst_->right, values, index);
    if (*index < DATA_SIZE)
    {
        values[*index] = bst_->data;
        ++(*index);
    }
    fill_bst_descending(bst_->left, values, index);
}

void ordered_print(stack* stack_, queue* queue_, bst* bst_)
{
    int stack_values[DATA_SIZE];
    int queue_values[DATA_SIZE];
    int bst_values[DATA_SIZE];
    int stack_size = 0;
    int queue_size = 0;
    int bst_size = 0;
    int repeat = 0;
    double start_time = 0.0;
    double end_time = 0.0;
    double stack_ms = 0.0;
    double queue_ms = 0.0;
    double bst_ms = 0.0;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        stack_size = copy_stack_to_array(stack_, stack_values);
        sort_descending(stack_values, stack_size);
    }
    end_time = get_time_ms();
    stack_ms = end_time - start_time;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        queue_size = copy_queue_to_array(queue_, queue_values);
        sort_descending(queue_values, queue_size);
    }
    end_time = get_time_ms();
    queue_ms = end_time - start_time;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        bst_size = 0;
        fill_bst_descending(bst_, bst_values, &bst_size);
    }
    end_time = get_time_ms();
    bst_ms = end_time - start_time;

    printf("\n================= PART 2: ORDERED PRINT (DESC) =================\n");
    printf("Ordered Stack: ");
    print_array(stack_values, stack_size);
    printf("\nOrdered Queue: ");
    print_array(queue_values, queue_size);
    printf("\nOrdered BST:   ");
    print_array(bst_values, bst_size);

    printf("\n(Total of %d runs, computation only)\n", BENCH_REPEAT);
    printf("| Structures      | Stack | Queue | BST   |\n");
    printf("| :-------------- | :---- | :---- | :---- |\n");
    printf("| Total Time (ms) | %.3f | %.3f | %.3f |\n", stack_ms, queue_ms, bst_ms);
}
