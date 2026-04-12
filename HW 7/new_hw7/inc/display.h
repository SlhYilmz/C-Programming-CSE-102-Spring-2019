/**
 * @file display.h
 * @brief Board rendering and property deed viewer (Parts 2 & 3).
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"

/**
 * @brief Prints the full board as a grid.
 *
 * Each cell shows the block name, price (properties and tax blocks only),
 * and the token label of any player currently standing on it.
 *
 * Layout - block indices:
 * - Top row  (L→R) : 0  1  2  3  4  5
 * - Right col (T→B): 6  7  8  9
 * - Bottom row (R→L): 10 11 12 13 14 15
 * - Left col  (B→T): 16 17 18 19
 */
void show_board(struct block board[BOARD_SIZE],
                struct player player_one,
                struct player player_two);

/**
 * @brief Interactive property deed viewer.
 *
 * Lists all property blocks by id and name, prompts the user to select one,
 * then prints a formatted deed card (rents, house price). Loops until the
 * user enters 0 to exit.
 */
void show_properties(struct block board[BOARD_SIZE]);

#endif /* DISPLAY_H */
