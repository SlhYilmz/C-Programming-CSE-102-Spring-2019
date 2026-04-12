#ifndef BOARD_H
#define BOARD_H

#include "types.h"

/*
 * Initialises all 20 blocks of the board with their static data.
 * Must be called once before any other board operation.
 */
void init_the_board(struct block board[BOARD_SIZE]);

#endif /* BOARD_H */
