#ifndef HW10_TYPES_H
#define HW10_TYPES_H

#define DATA_SIZE 20
#define BENCH_REPEAT 10000

typedef struct stack
{
    int data;
    struct stack* next;
} stack;

typedef struct queue
{
    int data;
    struct queue* next;
} queue;

typedef struct bst
{
    int data;
    struct bst* right;
    struct bst* left;
} bst;

#endif
