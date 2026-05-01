#include <stdio.h>

#include "hw10.h"
#include "time_utils.h"

static int copy_stack_to_array(const stack* stack_, int values[DATA_SIZE])
{
    int count = 0;
    const stack* iter = stack_;

    while ((iter != NULL) && (count < DATA_SIZE))
    {
        values[count] = iter->data;
        ++count;
        iter = iter->next;
    }

    return count;
}

static int copy_queue_to_array(const queue* queue_, int values[DATA_SIZE])
{
    int count = 0;
    const queue* iter = queue_;

    while ((iter != NULL) && (count < DATA_SIZE))
    {
        values[count] = iter->data;
        ++count;
        iter = iter->next;
    }

    return count;
}

static void fill_bst_ascending(const bst* bst_, int values[DATA_SIZE], int* count)
{
    if ((bst_ == NULL) || (*count >= DATA_SIZE))
    {
        return;
    }

    fill_bst_ascending(bst_->left, values, count);
    if (*count < DATA_SIZE)
    {
        values[*count] = bst_->data;
        ++(*count);
    }
    fill_bst_ascending(bst_->right, values, count);
}

static void sort_ascending(int values[DATA_SIZE], int size)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 0; i < size - 1; ++i)
    {
        for (j = i + 1; j < size; ++j)
        {
            if (values[i] > values[j])
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
}

static void build_special_order(const int sorted_values[DATA_SIZE], int special_values[DATA_SIZE], int size)
{
    int left = 0;
    int right = size - 1;
    int index = 0;

    while (left <= right)
    {
        special_values[index] = sorted_values[right];
        ++index;
        --right;

        if (left <= right)
        {
            special_values[index] = sorted_values[left];
            ++index;
            ++left;
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

void special_traverse(stack* stack_, queue* queue_, bst* bst_)
{
    int stack_values[DATA_SIZE];
    int queue_values[DATA_SIZE];
    int bst_values[DATA_SIZE];
    int stack_special[DATA_SIZE];
    int queue_special[DATA_SIZE];
    int bst_special[DATA_SIZE];
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
        sort_ascending(stack_values, stack_size);
        build_special_order(stack_values, stack_special, stack_size);
    }
    end_time = get_time_ms();
    stack_ms = end_time - start_time;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        queue_size = copy_queue_to_array(queue_, queue_values);
        sort_ascending(queue_values, queue_size);
        build_special_order(queue_values, queue_special, queue_size);
    }
    end_time = get_time_ms();
    queue_ms = end_time - start_time;

    start_time = get_time_ms();
    for (repeat = 0; repeat < BENCH_REPEAT; ++repeat)
    {
        bst_size = 0;
        fill_bst_ascending(bst_, bst_values, &bst_size);
        build_special_order(bst_values, bst_special, bst_size);
    }
    end_time = get_time_ms();
    bst_ms = end_time - start_time;

    printf("\n================== PART 4: SPECIAL TRAVERSE ====================\n");
    printf("Special Stack: ");
    print_array(stack_special, stack_size);
    printf("\nSpecial Queue: ");
    print_array(queue_special, queue_size);
    printf("\nSpecial BST:   ");
    print_array(bst_special, bst_size);

    printf("\n(Total of %d runs, computation only)\n", BENCH_REPEAT);
    printf("| Structures      | Stack | Queue | BST   |\n");
    printf("| :-------------- | :---- | :---- | :---- |\n");
    printf("| Total Time (ms) | %.3f | %.3f | %.3f |\n", stack_ms, queue_ms, bst_ms);
}
