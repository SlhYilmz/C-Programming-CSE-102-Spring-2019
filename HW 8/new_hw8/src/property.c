/*
 * property.c - Buy and sell property (Parts 4 & 5)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/property.h"

/* -----------------------------------------------------------------------
 * Module-private constants
 * --------------------------------------------------------------------- */
#define CHOICE_YES          (1)  /**< User answered yes at a 1/0 prompt.            */
#define ADD_OWNED_OK        (1)  /**< add_owned(): block id stored successfully.     */
#define ADD_OWNED_FAIL      (0)  /**< add_owned(): owned list is full.               */
#define SELL_EXIT           (0)  /**< Selection value that exits sell_property loop. */
#define INVALID_SCAN_RESULT (-1) /**< Sentinel assigned when scanf fails.            */

/* -----------------------------------------------------------------------
 * Internal helper - find a block in the board by its id.
 * Returns NULL when not found.
 * --------------------------------------------------------------------- */
static struct block* find_block(struct block* board,
                                int id)
{
    struct block* b = board;

    while (b != NULL)
    {
        if (b->block_id == id)
        {
            return b;
        }
        b = b->next;
    }

    return NULL;
}

/* -----------------------------------------------------------------------
 * Internal helper - add a block id to the player's owned list.
 * Returns ADD_OWNED_OK on success, ADD_OWNED_FAIL if the list is full.
 * --------------------------------------------------------------------- */
static int add_owned(struct player* p,
                     int block_id)
{
    int32_t i;
    int result = ADD_OWNED_FAIL;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        if (p->owned_block_ids[i] == NO_BLOCK)
        {
            p->owned_block_ids[i] = block_id;
            result = ADD_OWNED_OK;
            break;
        }
    }

    return result;
}

/* -----------------------------------------------------------------------
 * Internal helper - remove a block id from the player's owned list.
 * Shifts nothing; just sets the matching slot back to NO_BLOCK.
 * --------------------------------------------------------------------- */
static void remove_owned(struct player* p,
                         int block_id)
{
    int32_t i;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        if (p->owned_block_ids[i] == block_id)
        {
            p->owned_block_ids[i] = NO_BLOCK;
        }
    }
}

/* -----------------------------------------------------------------------
 * Internal helper - try to build houses on a property the player just
 * bought (or landed on). Loops until the player declines, runs out of
 * money, or reaches MAX_HOUSES.
 * --------------------------------------------------------------------- */
static void offer_build_houses(struct block* b,
                               struct player* p)
{
    int choice;
    bool done;

    done = false;

    while ((!done) && (b->house_count < (int32_t)MAX_HOUSES))
    {
        printf("\n  Houses on %s: %d / %d   (cost per house: %d$)\n", b->name, b->house_count, MAX_HOUSES, b->house_price);

        if (p->account < b->house_price)
        {
            printf("  Not enough money to build another house.\n");
            done = true;
        }
        else
        {
            printf("  Build a house? (1 = Yes / 0 = No): ");
            if (scanf("%d", &choice) != 1)
            {
                while (getchar() != '\n')
                {
                    ;
                }
                choice = 0;
            }

            if (choice == CHOICE_YES)
            {
                p->account -= b->house_price;
                b->house_count += 1;
                printf("  House built. Balance: %d$\n", p->account);
            }
            else
            {
                done = true;
            }
        }
    }

    if (b->house_count >= (int32_t)MAX_HOUSES)
    {
        printf("  Maximum houses reached on %s.\n", b->name);
    }
}

/* -----------------------------------------------------------------------
 * Part 4 - buy_property [15 pts]
 * --------------------------------------------------------------------- */
void buy_property(struct block* current_block,
                  struct player* current_player)
{
    int choice;

    /* --- validation --- */
    if (current_block->type != property)
    {
        printf("This block is not a property.\n");
        return;
    }

    if (current_block->owner.type != noone)
    {
        printf("%s is already owned.\n", current_block->name);
        return;
    }

    if (current_player->current_block_id != current_block->block_id)
    {
        printf("You must be standing on the property to buy it.\n");
        return;
    }

    if (current_player->account < current_block->price)
    {
        printf("Not enough money to buy %s (price: %d$, balance: %d$).\n", current_block->name, current_block->price, current_player->account);
        return;
    }

    /* --- offer to buy --- */
    printf("\n%s - price: %d$   Your balance: %d$\n", current_block->name, current_block->price, current_player->account);
    printf("Buy this property? (1 = Yes / 0 = No): ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
        {
            ;
        }
        choice = 0;
    }

    if (choice != CHOICE_YES)
    {
        printf("Purchase cancelled.\n");
        return;
    }

    /* --- transfer --- */
    if (add_owned(current_player, current_block->block_id) == ADD_OWNED_FAIL)
    {
        printf("Cannot buy: property list is full.\n");
        return;
    }

    current_player->account -= current_block->price;
    current_block->owner = *current_player;

    printf("You bought %s. Balance: %d$\n", current_block->name, current_player->account);

    /* --- optional house building --- */
    offer_build_houses(current_block, current_player);
}

/* -----------------------------------------------------------------------
 * Part 5 - sell_property [15 pts]
 *
 * Refund = (property price + houses built * house_price) / SELL_REFUND_RATIO
 * --------------------------------------------------------------------- */
void sell_property(struct block* board,
                   struct player* current_player)
{
    int32_t i;
    int count;
    int selection;
    int refund;
    struct block* b;
    bool done;

    done = false;

    do
    {
        /* collect owned properties */
        count = 0;
        for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
        {
            if (current_player->owned_block_ids[i] != NO_BLOCK)
            {
                count++;
            }
        }

        if (count == 0)
        {
            printf("You have no properties to sell.\n");
            done = true;
        }
        else
        {
            printf("\nProperties you can sell:\n");
            for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
            {
                if (current_player->owned_block_ids[i] != NO_BLOCK)
                {
                    b = find_block(board, current_player->owned_block_ids[i]);
                    if (b != NULL)
                    {
                        refund = (b->price + b->house_count * b->house_price) / SELL_REFUND_RATIO;
                        printf("  %2d - %-14s  houses: %d   refund: %d$\n", b->block_id, b->name, b->house_count, refund);
                    }
                }
            }
            printf("   0 - Exit\n\nSelect property to sell: ");

            if (scanf("%d", &selection) != 1)
            {
                while (getchar() != '\n')
                {
                    ;
                }
                selection = INVALID_SCAN_RESULT;
            }

            if (selection == SELL_EXIT)
            {
                done = true;
            }
            else
            {
                b = find_block(board, selection);

                if ((b == NULL) || (b->type != property) ||
                    (b->owner.type == noone))
                {
                    printf("Invalid selection.\n");
                }
                else
                {
                    /* verify the player actually owns this block */
                    bool owned = false;
                    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
                    {
                        if (current_player->owned_block_ids[i] == selection)
                        {
                            owned = true;
                        }
                    }

                    if (!owned)
                    {
                        printf("You do not own that property.\n");
                    }
                    else
                    {
                        refund = (b->price + b->house_count * b->house_price) / SELL_REFUND_RATIO;

                        current_player->account += refund;
                        b->house_count = 0;
                        b->owner = *current_player; /* will be cleared below */
                        b->owner.type = noone;

                        remove_owned(current_player, selection);

                        printf("Sold %s for %d$. Balance: %d$\n", b->name, refund, current_player->account);
                    }
                }
            }
        }
    } while (!done);
}
