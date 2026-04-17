/**
 * @file gameplay.h
 * @brief Main game loop (Part 6).
 */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "types.h"

/**
 * @brief Runs the full two-player Monopoly game until one player goes bankrupt.
 *
 * Manages turn order, dice rolling, block landing logic, punishment tracking,
 * rent collection, and the per-turn action menu.
 */
void gameplay(struct block* board,
              struct player player_one,
              struct player player_two);

#endif /* GAMEPLAY_H */
