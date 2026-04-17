/*
 * board.c - Board initialisation (Part 1 / HW8 linked-list version)
 *
 * Data source : blocks2.csv  (24 blocks)
 * Each node is heap-allocated; caller frees with free_board().
 */

#include <stdint.h>
#include <stdlib.h>
#include "../inc/board.h"

/* -----------------------------------------------------------------------
 * Module-private constants
 * --------------------------------------------------------------------- */
#define NULL_SENTINEL (0) /**< Literal 0 used only when initialising pointer to NULL. */

/* -----------------------------------------------------------------------
 * Internal helper - constructs an empty (no-owner) player sentinel.
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
 * Internal helper - allocates one zeroed block node on the heap.
 * Returns NULL if malloc fails.
 * --------------------------------------------------------------------- */
static struct block* alloc_block(int id,
                                 char* name,
                                 int price,
                                 int rent,
                                 int r1,
                                 int r2,
                                 int r3,
                                 int hprice,
                                 block_type type)
{
    struct block* b = (struct block*)malloc(sizeof(struct block));
    if (b == NULL)
    {
        return NULL;
    }

    b->block_id    = id;
    b->name        = name;
    b->price       = price;
    b->rent        = rent;
    b->rent_1      = r1;
    b->rent_2      = r2;
    b->rent_3      = r3;
    b->house_price = hprice;
    b->house_count = NULL_SENTINEL;
    b->type        = type;
    b->owner       = make_no_owner();
    b->next        = NULL;

    return b;
}

/* -----------------------------------------------------------------------
 * Part 1 - Board Initialization
 *
 * Allocates 24 nodes from blocks2.csv, links them, returns head.
 * Returns NULL on allocation failure (any node).
 * --------------------------------------------------------------------- */
struct block* init_the_board(void)
{
    struct block* nodes[BOARD_SIZE];
    int32_t i;

    /*                      id  name            price   rent    r1      r2      r3      hprice  type    */
    nodes[0]  = alloc_block(0,  "Start",        0,      0,      0,      0,      0,      0,      start);
    nodes[1]  = alloc_block(1,  "Esenyurt",     16000,  800,    4000,   9000,   25000,  10000,  property);
    nodes[2]  = alloc_block(2,  "Car Park",     1500,   0,      0,      0,      0,      0,      tax);
    nodes[3]  = alloc_block(3,  "Fortune Card", 0,      0,      0,      0,      0,      0,      fortune);
    nodes[4]  = alloc_block(4,  "Tuzla",        16500,  850,    4250,   9500,   26000,  12000,  property);
    nodes[5]  = alloc_block(5,  "Arnavutkoy",   17000,  875,    4500,   10000,  28000,  12000,  property);
    nodes[6]  = alloc_block(6,  "Wait 2 Turn",  WAIT_TWO_TURNS, 0, 0,  0,      0,      0,      punish);
    nodes[7]  = alloc_block(7,  "Catalca",      20000,  1000,   5000,   12000,  30000,  13000,  property);
    nodes[8]  = alloc_block(8,  "Beykoz",       23000,  1100,   5500,   12500,  33000,  13000,  property);
    nodes[9]  = alloc_block(9,  "Fortune Card", 0,      0,      0,      0,      0,      0,      fortune);
    nodes[10] = alloc_block(10, "Car Fix",      1750,   0,      0,      0,      0,      0,      tax);
    nodes[11] = alloc_block(11, "Maltepe",      30000,  1350,   7000,   15000,  40000,  15000,  property);
    nodes[12] = alloc_block(12, "Bills",        2000,   0,      0,      0,      0,      0,      tax);
    nodes[13] = alloc_block(13, "Sisli",        33000,  1500,   8000,   16000,  42000,  16000,  property);
    nodes[14] = alloc_block(14, "Oil",          2250,   0,      0,      0,      0,      0,      tax);
    nodes[15] = alloc_block(15, "Fortune Card", 0,      0,      0,      0,      0,      0,      fortune);
    nodes[16] = alloc_block(16, "Atasehir",     35000,  1600,   8500,   17000,  45000,  17000,  property);
    nodes[17] = alloc_block(17, "Sariyer",      40000,  1750,   9500,   19000,  48000,  19000,  property);
    nodes[18] = alloc_block(18, "Wait 1 Turn",  WAIT_ONE_TURN, 0, 0,   0,      0,      0,      punish);
    nodes[19] = alloc_block(19, "Kadikoy",      43000,  1900,   11000,  21500,  55000,  23000,  property);
    nodes[20] = alloc_block(20, "Besiktas",     60000,  2500,   15000,  28000,  60000,  30000,  property);
    nodes[21] = alloc_block(21, "Fortune Card", 0,      0,      0,      0,      0,      0,      fortune);
    nodes[22] = alloc_block(22, "Vocation",     5000,   0,      0,      0,      0,      0,      tax);
    nodes[23] = alloc_block(23, "Bebek",        70000,  3500,   20000,  35500,  65000,  35000,  property);

    /* Check for allocation failures and free any that succeeded */
    for (i = 0; i < (int32_t)BOARD_SIZE; i++)
    {
        if (nodes[i] == NULL)
        {
            int32_t j;
            for (j = 0; j < i; j++)
            {
                free(nodes[j]);
            }
            return NULL;
        }
    }

    /* Link the nodes into a singly-linked list */
    for (i = 0; i < (int32_t)BOARD_SIZE - 1; i++)
    {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[BOARD_SIZE - 1]->next = NULL;

    return nodes[0];
}

/* -----------------------------------------------------------------------
 * free_board - releases every node allocated by init_the_board().
 * --------------------------------------------------------------------- */
void free_board(struct block* head)
{
    struct block* current = head;
    struct block* next_node;

    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
