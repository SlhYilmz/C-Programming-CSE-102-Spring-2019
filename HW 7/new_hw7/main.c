/*
 * main.c - Entry point
 *
 * Student ID : 1801042676
 * Standard   : C99 (gcc -std=c99)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "inc/types.h"
#include "inc/board.h"
#include "inc/display.h"
#include "inc/property.h"
#include "inc/gameplay.h"

#define NAME_BUF_SIZE (64)

/* -----------------------------------------------------------------------
 * Internal helper – initialise a player with a name, token, and defaults.
 * --------------------------------------------------------------------- */
static void init_player(struct player* p, player_type token, char* name_buf, const char* prompt)
{
    int32_t i;

    printf("%s", prompt);
    if (scanf("%63s", name_buf) != 1)
    {
        name_buf[0] = '\0';
    }

    p->type = token;
    p->name = name_buf;
    p->current_block_id = START_BLOCK_ID;
    p->account = STARTING_MONEY;
    p->turn_to_wait = NO_WAIT_TURNS;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        p->owned_block_ids[i] = NO_BLOCK;
    }
}

/* -----------------------------------------------------------------------
 * main
 * --------------------------------------------------------------------- */
int main(void)
{
    struct block board[BOARD_SIZE];
    struct player player_one;
    struct player player_two;
    char name1[NAME_BUF_SIZE];
    char name2[NAME_BUF_SIZE];

    init_the_board(board);

    printf("=== MONOPOLY ===\n\n");
    init_player(&player_one, cap, name1, "Enter name for Player 1 (Cap): ");
    init_player(&player_two, car, name2, "Enter name for Player 2 (Car): ");

    gameplay(board, player_one, player_two);

    return EXIT_SUCCESS;
}
