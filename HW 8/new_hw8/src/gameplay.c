/*
 * gameplay.c - Main game loop (Part 6)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/gameplay.h"
#include "../inc/display.h"
#include "../inc/property.h"

/* -----------------------------------------------------------------------
 * Module-private constants
 * --------------------------------------------------------------------- */
#define DICE_MIN  (1)
#define DICE_MAX  (6)
#define MENU_MIN  (1)
#define MENU_MAX  (7)
#define MENU_EXIT (-1)

/* Turn-state return values from do_turn() / handle_landing() */
#define SOLVENT   (1)  /**< player is able to continue playing      */
#define BANKRUPT  (0)  /**< player is out of money and properties   */
#define QUIT_GAME (-2) /**< player chose to exit voluntarily        */

/* rolled-flag states used inside do_turn() */
#define TURN_PENDING (0) /**< player has not yet rolled this turn     */
#define TURN_DONE    (1) /**< player has rolled; turn is complete     */

/* game_over flag states used inside gameplay() */
#define GAME_RUNNING (0) /**< game loop is still active               */
#define GAME_ENDED   (1) /**< game loop should terminate              */

/* binary user-prompt answer */
#define CHOICE_YES (1) /**< user answered yes at a binary prompt    */

/* property-search result flag */
#define PROP_NOT_FOUND (0) /**< search loop found no matching entry     */
#define PROP_FOUND     (1) /**< search loop found a matching entry      */

/* sentinel to exit a debt-repayment while-loop */
#define NO_DEBT (0) /**< zero amount owed; terminates debt loop  */

/* -----------------------------------------------------------------------
 * Internal helper - roll a single die [DICE_MIN, DICE_MAX].
 * --------------------------------------------------------------------- */
static int roll_dice(void)
{
    return (int)(rand() % (DICE_MAX - DICE_MIN + 1)) + DICE_MIN;
}

/* -----------------------------------------------------------------------
 * Internal helper - return the current rent owed on a block.
 * --------------------------------------------------------------------- */
static int current_rent(const struct block* b)
{
    int rent;

    switch (b->house_count)
    {
        case 1:
            rent = b->rent_1;
            break;
        case 2:
            rent = b->rent_2;
            break;
        case 3:
            rent = b->rent_3;
            break;
        default:
            rent = b->rent;
            break;
    }

    return rent;
}

/* -----------------------------------------------------------------------
 * Internal helper - count how many properties a player owns.
 * --------------------------------------------------------------------- */
static int count_owned(const struct player* p)
{
    int32_t i;
    int count = 0;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        if (p->owned_block_ids[i] != NO_BLOCK)
        {
            count++;
        }
    }

    return count;
}

/* -----------------------------------------------------------------------
 * Internal helper - find block in linked list by id.
 * --------------------------------------------------------------------- */
static struct block* find_block_by_id(struct block* board,
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
 * Internal helper - synchronise the owner field inside every board block
 * owned by @p after any change to p->account / p->name etc.
 * --------------------------------------------------------------------- */
static void sync_owner_fields(struct block* board,
                              const struct player* p)
{
    int32_t i;
    struct block* b;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        if (p->owned_block_ids[i] != NO_BLOCK)
        {
            for (b = board; b != NULL; b = b->next)
            {
                if (b->block_id == p->owned_block_ids[i])
                {
                    b->owner = *p;
                }
            }
        }
    }
}

/* -----------------------------------------------------------------------
 * Internal helper - show the per-turn action menu and return selection.
 * --------------------------------------------------------------------- */
static int show_menu(const struct player* p)
{
    char buf[32];
    int choice;

    printf("\n--- %s's turn   Balance: %d$ ---\n", p->name, p->account);
    printf("  1 - Roll the dice\n");
    printf("  2 - Show my account\n");
    printf("  3 - Show my properties\n");
    printf("  4 - Show property deeds\n");
    printf("  5 - Buy property\n");
    printf("  6 - Buy house\n");
    printf("  7 - Sell property\n");
    printf("  (type EXIT to quit the game)\n");
    printf("Please select an option to continue: ");

    if (scanf("%31s", buf) != 1)
    {
        while (getchar() != '\n')
        {
            ;
        }
        return 0;
    }

    if (strcmp(buf, "EXIT") == 0)
    {
        return MENU_EXIT;
    }

    if (sscanf(buf, "%d", &choice) != 1)
    {
        choice = 0;
    }

    return choice;
}

/* -----------------------------------------------------------------------
 * Internal helper - print which properties the current player owns.
 * --------------------------------------------------------------------- */
static void show_my_properties(struct block* board,
                               const struct player* p)
{
    int32_t i;
    struct block* b;
    int found;

    found = PROP_NOT_FOUND;
    printf("\n%s's properties:\n", p->name);

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        if (p->owned_block_ids[i] != NO_BLOCK)
        {
            for (b = board; b != NULL; b = b->next)
            {
                if (b->block_id == p->owned_block_ids[i])
                {
                    printf("  [%2d] %-14s  houses: %d\n", b->block_id, b->name, b->house_count);
                    found = PROP_FOUND;
                }
            }
        }
    }

    if (found == PROP_NOT_FOUND)
    {
        printf("  (none)\n");
    }
}

/* -----------------------------------------------------------------------
 * Internal helper - handle the event of landing on a block.
 * Returns 1 if the player is still solvent, 0 if bankrupt.
 * --------------------------------------------------------------------- */
static int handle_landing(struct block* board,
                          struct player* current,
                          struct player* other)
{
    struct block* b;
    int owed;
    int solvent;

    solvent = SOLVENT;
    b = find_block_by_id(board, current->current_block_id);
    if (b == NULL)
    {
        return BANKRUPT;
    }

    switch (b->type)
    {
        case start:
            /* nothing extra on landing */
            break;

        case property:
            if (b->owner.type == noone)
            {
                /* offer purchase - buy_property validates location */
                buy_property(b, current);
                sync_owner_fields(board, current);
            }
            else if (b->owner.type != current->type)
            {
                /* pay rent to the other player */
                owed = current_rent(b);
                printf("\n%s is owned by %s. You owe %d$ rent.\n", b->name, other->name, owed);

                while (current->account < owed)
                {
                    if (count_owned(current) == 0)
                    {
                        printf("%s cannot pay and has no properties to sell. BANKRUPT!\n", current->name);
                        solvent = BANKRUPT;
                        owed = NO_DEBT; /* break out of while */
                    }
                    else
                    {
                        printf("Not enough money (%d$). You must sell a property first.\n", current->account);
                        sell_property(board, current);
                        sync_owner_fields(board, current);
                    }
                }

                if (solvent == SOLVENT)
                {
                    current->account -= owed;
                    other->account += owed;
                    sync_owner_fields(board, current);
                    sync_owner_fields(board, other);
                    printf("Paid %d$ to %s. Your balance: %d$\n", owed, other->name, current->account);
                }
            }
            else
            {
                /* landed on own property - offer to build a house */
                printf("\nYou landed on your own property: %s\n", b->name);
                if (b->house_count < (int32_t)MAX_HOUSES)
                {
                    int choice;
                    printf("Build a house here? (1 = Yes / 0 = No): ");
                    if (scanf("%d", &choice) != 1)
                    {
                        while (getchar() != '\n')
                        {
                            ;
                        }
                        choice = 0;
                    }
                    if ((choice == CHOICE_YES) && (current->account >= b->house_price))
                    {
                        current->account -= b->house_price;
                        b->house_count += 1;
                        sync_owner_fields(board, current);
                        printf("House built on %s. Balance: %d$\n", b->name, current->account);
                    }
                    else if (choice == CHOICE_YES)
                    {
                        printf("Not enough money to build a house.\n");
                    }
                }
                else
                {
                    printf("Maximum houses already built on %s.\n", b->name);
                }
            }
            break;

        case tax:
            owed = b->price;
            printf("\nTax block: %s. You owe %d$.\n", b->name, owed);

            while (current->account < owed)
            {
                if (count_owned(current) == 0)
                {
                    printf("%s cannot pay tax and has no properties to sell. BANKRUPT!\n", current->name);
                    solvent = BANKRUPT;
                    owed = NO_DEBT;
                }
                else
                {
                    printf("Not enough money (%d$). You must sell a property first.\n", current->account);
                    sell_property(board, current);
                    sync_owner_fields(board, current);
                }
            }

            if (solvent == SOLVENT)
            {
                current->account -= owed;
                sync_owner_fields(board, current);
                printf("Paid %d$ in tax. Balance: %d$\n", owed, current->account);
            }
            break;

        case punish:
            current->turn_to_wait = b->price;
            printf("\n%s: you must wait %d turn(s).\n", b->name, b->price);
            break;

        case fortune:
            printf("\nYou landed on a Fortune Card block!\n");
            break;

        default:
            break;
    }

    /* Update the block's owner snapshot for any property we own here */
    {
        struct block* bk;
        for (bk = board; bk != NULL; bk = bk->next)
        {
            if ((bk->type == property) && (bk->owner.type == current->type))
            {
                bk->owner = *current;
            }
        }
    }

    return solvent;
}

/* -----------------------------------------------------------------------
 * Internal helper - move the player by @p steps and handle pass-Start.
 * --------------------------------------------------------------------- */
static void move_player(struct block* board,
                        struct player* p,
                        int steps)
{
    struct block* b;
    int i;
    int passed_start;

    b = find_block_by_id(board, p->current_block_id);
    passed_start = TURN_PENDING;

    for (i = 0; i < steps; i++)
    {
        b = b->next;
        if (b == NULL) /* end of list: wrap to start */
        {
            b = board;
            passed_start = TURN_DONE;
        }
    }

    p->current_block_id = b->block_id;

    if (passed_start == TURN_DONE)
    {
        p->account += PASS_START_BONUS;
        printf("Passed Start! Received %d$. Balance: %d$\n", PASS_START_BONUS, p->account);
    }
}

/* -----------------------------------------------------------------------
 * Internal helper - execute the menu-driven part of one player's turn.
 * Returns 1 while the turn is still ongoing, 0 when the player has rolled.
 * Returns -1 if the player went bankrupt during a forced sale.
 * --------------------------------------------------------------------- */
static int do_turn(struct block* board,
                   struct player* current,
                   struct player* other)
{
    int choice;
    int rolled;
    int dice;
    int solvent;
    struct block* b;
    struct block* cur_b;

    rolled = TURN_PENDING;
    solvent = SOLVENT;

    while ((rolled == TURN_PENDING) && (solvent == SOLVENT))
    {
        choice = show_menu(current);

        switch (choice)
        {
            case 1: /* Roll the dice */
                dice = roll_dice();
                printf("\n%s rolled a %d!\n", current->name, dice);
                move_player(board, current, dice);
                cur_b = find_block_by_id(board, current->current_block_id);
                printf("%s moved to [%d] %s\n", current->name, current->current_block_id, (cur_b != NULL) ? cur_b->name : "?");

                solvent = handle_landing(board, current, other);
                rolled = TURN_DONE;
                break;

            case 2: /* Show account */
                printf("\n%s's balance: %d$\n", current->name, current->account);
                break;

            case 3: /* Show my properties */
                show_my_properties(board, current);
                break;

            case 4: /* Show property deeds */
                show_properties(board);
                break;

            case 5: /* Buy property */
                b = find_block_by_id(board, current->current_block_id);
                buy_property(b, current);
                sync_owner_fields(board, current);
                break;

            case 6: /* Buy house */
                b = find_block_by_id(board, current->current_block_id);
                if ((b->type == property) && (b->owner.type == current->type))
                {
                    if (b->house_count < (int32_t)MAX_HOUSES)
                    {
                        if (current->account >= b->house_price)
                        {
                            current->account -= b->house_price;
                            b->house_count += 1;
                            sync_owner_fields(board, current);
                            printf("House built on %s. Balance: %d$\n", b->name, current->account);
                        }
                        else
                        {
                            printf("Not enough money to build a house here.\n");
                        }
                    }
                    else
                    {
                        printf("Maximum houses already built on %s.\n", b->name);
                    }
                }
                else
                {
                    printf("You can only build on a property you own that you are standing on.\n");
                }
                break;

            case 7: /* Sell property */
                sell_property(board, current);
                sync_owner_fields(board, current);
                break;

            case MENU_EXIT: /* Voluntary quit */
            {
                char confirm[16];
                printf("Are you sure you want to quit? Type YES to confirm: ");
                if (scanf("%15s", confirm) == CHOICE_YES && strcmp(confirm, "YES") == 0)
                {
                    printf("Quitting the game. Goodbye!\n");
                    return QUIT_GAME;
                }
                printf("Quit cancelled.\n");
                break;
            }

            default:
                printf("Invalid option. Please enter a number between %d and %d.\n", MENU_MIN, MENU_MAX);
                break;
        }

        /* Check bankruptcy after any action that changes the balance */
        if ((solvent == SOLVENT) && (current->account < 0))
        {
            if (count_owned(current) == 0)
            {
                printf("%s is bankrupt!\n", current->name);
                solvent = BANKRUPT;
            }
        }
    }

    /* Release all blocks belonging to a bankrupt player */
    if (solvent == BANKRUPT)
    {
        struct block* bk;
        for (bk = board; bk != NULL; bk = bk->next)
        {
            if (bk->owner.type == current->type)
            {
                bk->owner.type = noone;
                bk->house_count = 0;
            }
        }
    }

    return solvent;
}

/* -----------------------------------------------------------------------
 * Part 6 - gameplay [40 pts]
 * --------------------------------------------------------------------- */
void gameplay(struct block* board,
              struct player player_one,
              struct player player_two)
{
    struct player* active;
    struct player* waiting;
    struct player* tmp;
    int game_over;
    int solvent;

    srand((unsigned int)time(NULL));

    game_over = GAME_RUNNING;
    active = &player_one;
    waiting = &player_two;

    show_board(board, player_one, player_two);

    while (game_over == GAME_RUNNING)
    {
        /* Skip turn if player is in a punishment wait */
        if (active->turn_to_wait > 0)
        {
            printf("\n%s must wait %d more turn(s) and skips this turn.\n", active->name, active->turn_to_wait);
            active->turn_to_wait -= 1;
            solvent = SOLVENT;
        }
        else
        {
            solvent = do_turn(board, active, waiting);
        }

        show_board(board, player_one, player_two);

        if (solvent == QUIT_GAME)
        {
            /* Voluntary quit */
            game_over = GAME_ENDED;
        }
        else if (solvent == BANKRUPT)
        {
            printf("\n=== %s is eliminated! %s wins! ===\n", active->name, waiting->name);
            game_over = GAME_ENDED;
        }
        else
        {
            /* swap turns */
            tmp = active;
            active = waiting;
            waiting = tmp;
        }
    }
}
