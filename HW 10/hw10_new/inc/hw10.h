#ifndef HW10_H
#define HW10_H

#include "hw10_types.h"

void fill_structures(stack** stack_, queue** queue_, bst** bst_, int data[DATA_SIZE]);
void ordered_print(stack* stack_, queue* queue_, bst* bst_);
void search(stack* stack_, queue* queue_, bst* bst_, int val_to_search);
void special_traverse(stack* stack_, queue* queue_, bst* bst_);

#endif
