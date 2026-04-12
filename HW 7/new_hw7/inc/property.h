/**
 * @file property.h
 * @brief Buy and sell property operations (Parts 4 & 5).
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include "types.h"

/**
 * @brief Attempts to let @p current_player buy @p current_block.
 *
 * Validates that the block is a property, is unowned, the player is standing
 * on it, and has sufficient funds. On success, transfers ownership, deducts
 * the price, and optionally builds up to MAX_HOUSES houses.
 */
void buy_property(struct block* current_block,
                  struct player* current_player);

/**
 * @brief Lets @p current_player sell owned properties back to the bank.
 *
 * The bank refunds (price + houses * house_price) / SELL_REFUND_RATIO per
 * property. Loops until the player exits or has no more properties.
 */
void sell_property(struct block board[BOARD_SIZE],
                   struct player* current_player);

#endif /* PROPERTY_H */
