#ifndef BOARD_H
#define BOARD_H

#include "types.h"

/**
 * Allocates 24 board nodes on the heap, initialises them with static data
 * from blocks2.csv, links them into a singly-linked list, and returns a
 * pointer to the head (block 0 / Start).
 * The caller is responsible for freeing the list with free_board().
 */
struct block* init_the_board(void);

/**
 * Frees every node in the linked list previously allocated by init_the_board().
 */
void free_board(struct block* head);

#endif /* BOARD_H */
