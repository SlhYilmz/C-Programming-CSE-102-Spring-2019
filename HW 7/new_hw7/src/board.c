/*
 * board.c - Board initialisation (Part 1)
 *
 * Data source : blocks.csv
 * Internal helper make_no_owner() is not exposed via board.h because
 * nothing outside this translation unit needs to call it directly.
 */

#include <stdint.h>
#include "../inc/board.h"

/* -----------------------------------------------------------------------
 * Internal helper – constructs an empty (no-owner) player sentinel.
 * Not part of the public API.
 * --------------------------------------------------------------------- */
static struct player make_no_owner(void)
{
    struct player p;
    int32_t       i;

    p.type             = noone;
    p.current_block_id = NO_BLOCK;
    p.account          = NO_ACCOUNT_BALANCE;
    p.turn_to_wait     = NO_WAIT_TURNS;
    p.name             = NULL;

    for (i = 0; i < (int32_t)MAX_OWNED_BLOCKS; i++)
    {
        p.owned_block_ids[i] = NO_BLOCK;
    }

    return p;
}

/* -----------------------------------------------------------------------
 * Part 1 – Board Initialization [10 pts]
 *
 * For punish blocks, the turns-to-wait count is stored in `price`.
 * For tax blocks, the tax fee is stored in `price`.
 * --------------------------------------------------------------------- */
void init_the_board(struct block board[BOARD_SIZE])
{
    /* --- Block 0 : Start ------------------------------------------- */
    board[0].block_id    = 0;
    board[0].name        = "Start";
    board[0].price       = 0;
    board[0].rent        = 0;
    board[0].rent_1      = 0;
    board[0].rent_2      = 0;
    board[0].rent_3      = 0;
    board[0].house_price = 0;
    board[0].house_count = 0;
    board[0].type        = start;
    board[0].owner       = make_no_owner();

    /* --- Block 1 : Esenyurt (property) ------------------------------ */
    board[1].block_id    = 1;
    board[1].name        = "Esenyurt";
    board[1].price       = 16000;
    board[1].rent        = 800;
    board[1].rent_1      = 4000;
    board[1].rent_2      = 9000;
    board[1].rent_3      = 25000;
    board[1].house_price = 10000;
    board[1].house_count = 0;
    board[1].type        = property;
    board[1].owner       = make_no_owner();

    /* --- Block 2 : Car Park (tax) ----------------------------------- */
    board[2].block_id    = 2;
    board[2].name        = "Car Park";
    board[2].price       = 1500;
    board[2].rent        = 0;
    board[2].rent_1      = 0;
    board[2].rent_2      = 0;
    board[2].rent_3      = 0;
    board[2].house_price = 0;
    board[2].house_count = 0;
    board[2].type        = tax;
    board[2].owner       = make_no_owner();

    /* --- Block 3 : Tuzla (property) --------------------------------- */
    board[3].block_id    = 3;
    board[3].name        = "Tuzla";
    board[3].price       = 16500;
    board[3].rent        = 850;
    board[3].rent_1      = 4250;
    board[3].rent_2      = 9500;
    board[3].rent_3      = 26000;
    board[3].house_price = 12000;
    board[3].house_count = 0;
    board[3].type        = property;
    board[3].owner       = make_no_owner();

    /* --- Block 4 : Arnavutkoy (property) ---------------------------- */
    board[4].block_id    = 4;
    board[4].name        = "Arnavutkoy";
    board[4].price       = 17000;
    board[4].rent        = 875;
    board[4].rent_1      = 4500;
    board[4].rent_2      = 10000;
    board[4].rent_3      = 28000;
    board[4].house_price = 12000;
    board[4].house_count = 0;
    board[4].type        = property;
    board[4].owner       = make_no_owner();

    /* --- Block 5 : Wait 2 Turn (punish) ----------------------------- */
    board[5].block_id    = 5;
    board[5].name        = "Wait 2 Turn";
    board[5].price       = WAIT_TWO_TURNS;
    board[5].rent        = 0;
    board[5].rent_1      = 0;
    board[5].rent_2      = 0;
    board[5].rent_3      = 0;
    board[5].house_price = 0;
    board[5].house_count = 0;
    board[5].type        = punish;
    board[5].owner       = make_no_owner();

    /* --- Block 6 : Catalca (property) ------------------------------- */
    board[6].block_id    = 6;
    board[6].name        = "Catalca";
    board[6].price       = 20000;
    board[6].rent        = 1000;
    board[6].rent_1      = 5000;
    board[6].rent_2      = 12000;
    board[6].rent_3      = 30000;
    board[6].house_price = 13000;
    board[6].house_count = 0;
    board[6].type        = property;
    board[6].owner       = make_no_owner();

    /* --- Block 7 : Beykoz (property) -------------------------------- */
    board[7].block_id    = 7;
    board[7].name        = "Beykoz";
    board[7].price       = 23000;
    board[7].rent        = 1100;
    board[7].rent_1      = 5500;
    board[7].rent_2      = 12500;
    board[7].rent_3      = 33000;
    board[7].house_price = 13000;
    board[7].house_count = 0;
    board[7].type        = property;
    board[7].owner       = make_no_owner();

    /* --- Block 8 : Car Fix (tax) ------------------------------------ */
    board[8].block_id    = 8;
    board[8].name        = "Car Fix";
    board[8].price       = 1750;
    board[8].rent        = 0;
    board[8].rent_1      = 0;
    board[8].rent_2      = 0;
    board[8].rent_3      = 0;
    board[8].house_price = 0;
    board[8].house_count = 0;
    board[8].type        = tax;
    board[8].owner       = make_no_owner();

    /* --- Block 9 : Maltepe (property) ------------------------------- */
    board[9].block_id    = 9;
    board[9].name        = "Maltepe";
    board[9].price       = 30000;
    board[9].rent        = 1350;
    board[9].rent_1      = 7000;
    board[9].rent_2      = 15000;
    board[9].rent_3      = 40000;
    board[9].house_price = 15000;
    board[9].house_count = 0;
    board[9].type        = property;
    board[9].owner       = make_no_owner();

    /* --- Block 10 : Bills (tax) ------------------------------------- */
    board[10].block_id    = 10;
    board[10].name        = "Bills";
    board[10].price       = 2000;
    board[10].rent        = 0;
    board[10].rent_1      = 0;
    board[10].rent_2      = 0;
    board[10].rent_3      = 0;
    board[10].house_price = 0;
    board[10].house_count = 0;
    board[10].type        = tax;
    board[10].owner       = make_no_owner();

    /* --- Block 11 : Sisli (property) -------------------------------- */
    board[11].block_id    = 11;
    board[11].name        = "Sisli";
    board[11].price       = 33000;
    board[11].rent        = 1500;
    board[11].rent_1      = 8000;
    board[11].rent_2      = 16000;
    board[11].rent_3      = 42000;
    board[11].house_price = 16000;
    board[11].house_count = 0;
    board[11].type        = property;
    board[11].owner       = make_no_owner();

    /* --- Block 12 : Oil (tax) --------------------------------------- */
    board[12].block_id    = 12;
    board[12].name        = "Oil";
    board[12].price       = 2250;
    board[12].rent        = 0;
    board[12].rent_1      = 0;
    board[12].rent_2      = 0;
    board[12].rent_3      = 0;
    board[12].house_price = 0;
    board[12].house_count = 0;
    board[12].type        = tax;
    board[12].owner       = make_no_owner();

    /* --- Block 13 : Atasehir (property) ----------------------------- */
    board[13].block_id    = 13;
    board[13].name        = "Atasehir";
    board[13].price       = 35000;
    board[13].rent        = 1600;
    board[13].rent_1      = 8500;
    board[13].rent_2      = 17000;
    board[13].rent_3      = 45000;
    board[13].house_price = 17000;
    board[13].house_count = 0;
    board[13].type        = property;
    board[13].owner       = make_no_owner();

    /* --- Block 14 : Sariyer (property) ------------------------------ */
    board[14].block_id    = 14;
    board[14].name        = "Sariyer";
    board[14].price       = 40000;
    board[14].rent        = 1750;
    board[14].rent_1      = 9500;
    board[14].rent_2      = 19000;
    board[14].rent_3      = 48000;
    board[14].house_price = 19000;
    board[14].house_count = 0;
    board[14].type        = property;
    board[14].owner       = make_no_owner();

    /* --- Block 15 : Wait 1 Turn (punish) ---------------------------- */
    board[15].block_id    = 15;
    board[15].name        = "Wait 1 Turn";
    board[15].price       = WAIT_ONE_TURN;
    board[15].rent        = 0;
    board[15].rent_1      = 0;
    board[15].rent_2      = 0;
    board[15].rent_3      = 0;
    board[15].house_price = 0;
    board[15].house_count = 0;
    board[15].type        = punish;
    board[15].owner       = make_no_owner();

    /* --- Block 16 : Kadikoy (property) ------------------------------ */
    board[16].block_id    = 16;
    board[16].name        = "Kadikoy";
    board[16].price       = 43000;
    board[16].rent        = 1900;
    board[16].rent_1      = 11000;
    board[16].rent_2      = 21500;
    board[16].rent_3      = 55000;
    board[16].house_price = 23000;
    board[16].house_count = 0;
    board[16].type        = property;
    board[16].owner       = make_no_owner();

    /* --- Block 17 : Besiktas (property) ----------------------------- */
    board[17].block_id    = 17;
    board[17].name        = "Besiktas";
    board[17].price       = 60000;
    board[17].rent        = 2500;
    board[17].rent_1      = 15000;
    board[17].rent_2      = 28000;
    board[17].rent_3      = 60000;
    board[17].house_price = 30000;
    board[17].house_count = 0;
    board[17].type        = property;
    board[17].owner       = make_no_owner();

    /* --- Block 18 : Vocation (tax) ---------------------------------- */
    board[18].block_id    = 18;
    board[18].name        = "Vocation";
    board[18].price       = 5000;
    board[18].rent        = 0;
    board[18].rent_1      = 0;
    board[18].rent_2      = 0;
    board[18].rent_3      = 0;
    board[18].house_price = 0;
    board[18].house_count = 0;
    board[18].type        = tax;
    board[18].owner       = make_no_owner();

    /* --- Block 19 : Bebek (property) -------------------------------- */
    board[19].block_id    = 19;
    board[19].name        = "Bebek";
    board[19].price       = 70000;
    board[19].rent        = 3500;
    board[19].rent_1      = 20000;
    board[19].rent_2      = 35500;
    board[19].rent_3      = 65000;
    board[19].house_price = 35000;
    board[19].house_count = 0;
    board[19].type        = property;
    board[19].owner       = make_no_owner();
}
