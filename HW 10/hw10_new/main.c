#include <stddef.h>

#include "hw10.h"
#include "ds_utils.h"

int main(void)
{
    int data[DATA_SIZE] = {5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
    bst* bst_ = NULL;
    queue* queue_ = NULL;
    stack* stack_ = NULL;

    fill_structures(&stack_, &queue_, &bst_, data);
    ordered_print(stack_, queue_, bst_);
    search(stack_, queue_, bst_, 5);
    special_traverse(stack_, queue_, bst_);

    free_stack(stack_);
    free_queue(queue_);
    free_bst(bst_);

    return 0;
}
