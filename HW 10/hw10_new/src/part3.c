#include <stdio.h>

#include "hw10.h"

static int search_stack_steps(const stack* stack_, int val_to_search, int steps[DATA_SIZE])
{
    int step = 0;
    int found_count = 0;
    const stack* iter = stack_;

    while ((iter != NULL) && (step < DATA_SIZE))
    {
        ++step;
        if ((iter->data == val_to_search) && (found_count < DATA_SIZE))
        {
            steps[found_count] = step;
            ++found_count;
        }
        iter = iter->next;
    }

    return found_count;
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

static int search_queue_steps(const queue* queue_, int val_to_search, int steps[DATA_SIZE])
{
    int values[DATA_SIZE];
    int count = 0;
    int found_count = 0;
    int i = 0;
    int step = 1;

    count = copy_queue_to_array(queue_, values);
    for (i = count - 1; i >= 0; --i)
    {
        if ((values[i] == val_to_search) && (found_count < DATA_SIZE))
        {
            steps[found_count] = step;
            ++found_count;
        }
        ++step;
    }

    return found_count;
}

static void search_bst_internal(const bst* bst_, int val_to_search, int* step, int steps[DATA_SIZE], int* found_count)
{
    if (bst_ == NULL)
    {
        return;
    }

    ++(*step);
    if (val_to_search < bst_->data)
    {
        search_bst_internal(bst_->left, val_to_search, step, steps, found_count);
    }
    else if (val_to_search > bst_->data)
    {
        search_bst_internal(bst_->right, val_to_search, step, steps, found_count);
    }
    else
    {
        if (*found_count < DATA_SIZE)
        {
            steps[*found_count] = *step;
            ++(*found_count);
        }

        search_bst_internal(bst_->right, val_to_search, step, steps, found_count);
    }
}

static int search_bst_steps(const bst* bst_, int val_to_search, int steps[DATA_SIZE])
{
    int step = 0;
    int found_count = 0;

    search_bst_internal(bst_, val_to_search, &step, steps, &found_count);
    return found_count;
}

static void print_search_result(const char* name, const int steps[DATA_SIZE], int found_count)
{
    int i = 0;

    printf("  %s: ", name);
    if (found_count == 0)
    {
        printf("No result found.\n");
        return;
    }

    printf("%d result(s) found at step(s): ", found_count);
    for (i = 0; i < found_count; ++i)
    {
        if (i > 0)
        {
            printf(", ");
        }
        printf("%d", steps[i]);
    }
    printf("\n");
}

void search(stack* stack_, queue* queue_, bst* bst_, int val_to_search)
{
    int stack_steps[DATA_SIZE];
    int queue_steps[DATA_SIZE];
    int bst_steps[DATA_SIZE];
    int stack_found = 0;
    int queue_found = 0;
    int bst_found = 0;

    stack_found = search_stack_steps(stack_, val_to_search, stack_steps);
    queue_found = search_queue_steps(queue_, val_to_search, queue_steps);
    bst_found = search_bst_steps(bst_, val_to_search, bst_steps);

    printf("\n======================= PART 3: SEARCH =========================\n");
    printf("Search value: %d\n", val_to_search);
    print_search_result("Stack", stack_steps, stack_found);
    print_search_result("Queue", queue_steps, queue_found);
    print_search_result("BST", bst_steps, bst_found);
}
