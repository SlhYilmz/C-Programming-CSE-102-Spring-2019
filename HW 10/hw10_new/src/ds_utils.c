#include <stdlib.h>

#include "ds_utils.h"

void push_stack(stack** stack_, int value)
{
    stack* node = (stack*)malloc(sizeof(stack));

    if (node == NULL)
    {
        return;
    }

    node->data = value;
    node->next = *stack_;
    *stack_ = node;
}

void enqueue(queue** queue_, int value)
{
    queue* node = (queue*)malloc(sizeof(queue));
    queue* iter = NULL;

    if (node == NULL)
    {
        return;
    }

    node->data = value;
    node->next = NULL;

    if (*queue_ == NULL)
    {
        *queue_ = node;
        return;
    }

    iter = *queue_;
    while (iter->next != NULL)
    {
        iter = iter->next;
    }
    iter->next = node;
}

void bst_insert(bst** bst_, int value)
{
    bst* node = NULL;

    if (*bst_ == NULL)
    {
        node = (bst*)malloc(sizeof(bst));
        if (node == NULL)
        {
            return;
        }

        node->data = value;
        node->left = NULL;
        node->right = NULL;
        *bst_ = node;
        return;
    }

    if (value < (*bst_)->data)
    {
        bst_insert(&((*bst_)->left), value);
    }
    else
    {
        bst_insert(&((*bst_)->right), value);
    }
}

void free_stack(stack* stack_)
{
    stack* next = NULL;

    while (stack_ != NULL)
    {
        next = stack_->next;
        free(stack_);
        stack_ = next;
    }
}

void free_queue(queue* queue_)
{
    queue* next = NULL;

    while (queue_ != NULL)
    {
        next = queue_->next;
        free(queue_);
        queue_ = next;
    }
}

void free_bst(bst* bst_)
{
    if (bst_ == NULL)
    {
        return;
    }

    free_bst(bst_->left);
    free_bst(bst_->right);
    free(bst_);
}
