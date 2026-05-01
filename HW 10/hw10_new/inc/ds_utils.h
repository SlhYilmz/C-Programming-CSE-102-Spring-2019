#ifndef DS_UTILS_H
#define DS_UTILS_H

#include "hw10_types.h"

void push_stack(stack** stack_, int value);
void enqueue(queue** queue_, int value);
void bst_insert(bst** bst_, int value);

void free_stack(stack* stack_);
void free_queue(queue* queue_);
void free_bst(bst* bst_);

#endif
