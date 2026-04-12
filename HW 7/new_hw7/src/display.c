/*
 * display.c - Board and property display (Parts 2 & 3)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../inc/display.h"

/* -----------------------------------------------------------------------
 * Module-private constants
 * --------------------------------------------------------------------- */

#define CELL_W              (13)  /* printable content chars per board cell        */
#define BOARD_COLS          (6)   /* columns in the board grid                     */
#define LINE_W              (91)  /* BOARD_COLS*(CELL_W+2)+1 = 6*15+1              */
#define SIDE_MID_W          (4 * (CELL_W + 2) - 1)  /* merged inner span for side rows (59) */
#define DEED_INNER          (32)  /* printable chars between pipes in deed card    */
#define DEED_LABEL_W        (14)  /* left-aligned label column width in deed rows  */
#define DEED_NUM_W          (6)   /* right-aligned field width for numeric values  */
#define PROP_EXIT_SELECTION (0)   /* selection value that exits show_properties    */
#define INVALID_SCAN_RESULT (-1)  /* sentinel assigned to selection when scanf fails */

/* -----------------------------------------------------------------------
 * Internal helpers - board cell formatters
 * --------------------------------------------------------------------- */

/** Fills @p buf (CELL_W+1 bytes) with the block name, or "" if @p b is NULL. */
static void cell_name(char *buf, const struct block *b)
{
    if (b != NULL)
    {
        snprintf(buf, (size_t)(CELL_W + 1), "%s", b->name);
    }
    else
    {
        buf[0] = '\0';
    }
}

/** Fills @p buf with "PRICE$" for property/tax blocks, "" otherwise. */
static void cell_price(char *buf, const struct block *b)
{
    if ((b != NULL) && ((b->type == property) || (b->type == tax)))
    {
        snprintf(buf, (size_t)(CELL_W + 1), "%d$", b->price);
    }
    else
    {
        buf[0] = '\0';
    }
}

/** Fills @p buf with the token labels of players currently standing on @p b. */
static void cell_players(char *buf, const struct block *b,
                         const struct player *p1, const struct player *p2)
{
    const char *t1 = NULL;
    const char *t2 = NULL;

    buf[0] = '\0';

    if (b != NULL)
    {
        if ((p1 != NULL) && (p1->type != noone) && (p1->current_block_id == b->block_id))
        {
            t1 = (p1->type == cap) ? "Cap" : "Car";
        }
        if ((p2 != NULL) && (p2->type != noone) && (p2->current_block_id == b->block_id))
        {
            t2 = (p2->type == cap) ? "Cap" : "Car";
        }

        if ((t1 != NULL) && (t2 != NULL))
        {
            snprintf(buf, (size_t)(CELL_W + 1), "%s %s", t1, t2);
        }
        else if (t1 != NULL)
        {
            snprintf(buf, (size_t)(CELL_W + 1), "%s", t1);
        }
        else if (t2 != NULL)
        {
            snprintf(buf, (size_t)(CELL_W + 1), "%s", t2);
        }
    }
}

/* -----------------------------------------------------------------------
 * Internal helpers - row/separator printers
 * --------------------------------------------------------------------- */

/** Prints a full-width horizontal separator (LINE_W dashes). */
static void print_separator(void)
{
    int32_t i;
    for (i = 0; i < (int32_t)LINE_W; i++)
    {
        printf("-");
    }
    printf("\n");
}

/**
 * Prints a partial separator for rows between two side cells.
 * Dashes appear only under the left and right cells; the inner span is blank.
 * Left block  = CELL_W + 3 dashes  ( | + space + CELL_W content + | )
 * Middle gap  = SIDE_MID_W spaces
 * Right block = CELL_W + 3 dashes
 */
static void print_side_separator(void)
{
    int32_t i;
    for (i = 0; i < (int32_t)(CELL_W + 3); i++) { printf("-"); }
    for (i = 0; i < (int32_t)SIDE_MID_W;   i++) { printf(" "); }
    for (i = 0; i < (int32_t)(CELL_W + 3); i++) { printf("-"); }
    printf("\n");
}

/**
 * Prints 3 lines (name / price / players) for a full row of BOARD_COLS blocks.
 */
static void print_row(const struct block * const row[],
                      const struct player *p1, const struct player *p2)
{
    char    buf[CELL_W + 1];
    int32_t col;

    for (col = 0; col < (int32_t)BOARD_COLS; col++)
    {
        cell_name(buf, row[col]);
        printf("| %-*s", CELL_W, buf);
    }
    printf("|\n");

    for (col = 0; col < (int32_t)BOARD_COLS; col++)
    {
        cell_price(buf, row[col]);
        printf("| %-*s", CELL_W, buf);
    }
    printf("|\n");

    for (col = 0; col < (int32_t)BOARD_COLS; col++)
    {
        cell_players(buf, row[col], p1, p2);
        printf("| %-*s", CELL_W, buf);
    }
    printf("|\n");
}

/**
 * Prints 3 lines for a side row: two outer cells with a merged blank centre.
 * The 4 inner columns are collapsed into one empty span (no pipe separators).
 */
static void print_side_row(const struct block *left, const struct block *right,
                            const struct player *p1, const struct player *p2)
{
    char name_l[CELL_W + 1],    name_r[CELL_W + 1];
    char price_l[CELL_W + 1],   price_r[CELL_W + 1];
    char players_l[CELL_W + 1], players_r[CELL_W + 1];

    cell_name(name_l, left);         cell_name(name_r, right);
    cell_price(price_l, left);       cell_price(price_r, right);
    cell_players(players_l, left, p1, p2);
    cell_players(players_r, right, p1, p2);

    printf("| %-*s|%-*s| %-*s|\n", CELL_W, name_l,    SIDE_MID_W, "", CELL_W, name_r);
    printf("| %-*s|%-*s| %-*s|\n", CELL_W, price_l,   SIDE_MID_W, "", CELL_W, price_r);
    printf("| %-*s|%-*s| %-*s|\n", CELL_W, players_l, SIDE_MID_W, "", CELL_W, players_r);
}

/* -----------------------------------------------------------------------
 * Internal helper - property deed card
 * --------------------------------------------------------------------- */

/** Prints a formatted deed card for a property block. */
static void print_deed(const struct block *b)
{
    char    buf[DEED_INNER + 1];
    int32_t i;
    int32_t name_len;
    int32_t pad_left;

    /* outer top border */
    for (i = 0; i < (int32_t)(DEED_INNER + 2); i++) { printf("-"); }
    printf("\n");

    /* centred title */
    name_len = (int32_t)strlen(b->name);
    pad_left = (int32_t)((DEED_INNER - name_len) / 2);
    snprintf(buf, sizeof(buf), "%*s%s", pad_left, "", b->name);
    printf("|%-*s|\n", DEED_INNER, buf);

    /* title underline */
    printf("|");
    for (i = 0; i < (int32_t)DEED_INNER; i++) { printf("-"); }
    printf("|\n");

    /* rent rows */
    snprintf(buf, sizeof(buf), "  %-*s %*d$", DEED_LABEL_W, "Rent",        DEED_NUM_W, b->rent);
    printf("|%-*s|\n", DEED_INNER, buf);

    snprintf(buf, sizeof(buf), "  %-*s %*d$", DEED_LABEL_W, "Rent 1 H",    DEED_NUM_W, b->rent_1);
    printf("|%-*s|\n", DEED_INNER, buf);

    snprintf(buf, sizeof(buf), "  %-*s %*d$", DEED_LABEL_W, "Rent 2 H",    DEED_NUM_W, b->rent_2);
    printf("|%-*s|\n", DEED_INNER, buf);

    snprintf(buf, sizeof(buf), "  %-*s %*d$", DEED_LABEL_W, "Rent 3 H",    DEED_NUM_W, b->rent_3);
    printf("|%-*s|\n", DEED_INNER, buf);

    /* mid separator */
    printf("|");
    for (i = 0; i < (int32_t)DEED_INNER; i++) { printf("-"); }
    printf("|\n");

    /* house price */
    snprintf(buf, sizeof(buf), "  %-*s %*d$", DEED_LABEL_W, "House Price",  DEED_NUM_W, b->house_price);
    printf("|%-*s|\n", DEED_INNER, buf);

    /* bottom border */
    printf("|");
    for (i = 0; i < (int32_t)DEED_INNER; i++) { printf("-"); }
    printf("|\n");
}

/* -----------------------------------------------------------------------
 * Part 2 – show_board [20 pts]
 *
 * Board layout (block indices):
 *   Top row  (L→R): 0  1  2  3  4  5
 *   Right col(T→B): 6  7  8  9
 *   Bot row  (R→L): 10 11 12 13 14 15
 *   Left col (B→T): 16 17 18 19
 * --------------------------------------------------------------------- */
void show_board(struct block board[BOARD_SIZE],
                struct player player_one,
                struct player player_two)
{
    const struct player *p1 = &player_one;
    const struct player *p2 = &player_two;
    const struct block  *row[BOARD_COLS];
    int32_t              i;

    /* --- top row: blocks 0-5 --- */
    for (i = 0; i < (int32_t)BOARD_COLS; i++) { row[i] = &board[i]; }
    print_separator();
    print_row(row, p1, p2);

    /* --- side rows: left col 19→16, right col 6→9, inner merged --- */
    print_separator();
    print_side_row(&board[19], &board[6], p1, p2);

    print_side_separator();
    print_side_row(&board[18], &board[7], p1, p2);

    print_side_separator();
    print_side_row(&board[17], &board[8], p1, p2);

    print_side_separator();
    print_side_row(&board[16], &board[9], p1, p2);

    /* --- bottom row: blocks 15→10 (right to left) --- */
    print_separator();
    row[0] = &board[15]; row[1] = &board[14]; row[2] = &board[13];
    row[3] = &board[12]; row[4] = &board[11]; row[5] = &board[10];
    print_row(row, p1, p2);
    print_separator();
}

/* -----------------------------------------------------------------------
 * Part 3 – show_properties [10 pts]
 * --------------------------------------------------------------------- */
void show_properties(struct block board[BOARD_SIZE])
{
    int     selection;
    int32_t i;
    bool    valid;
    bool    done;

    done = false;

    do
    {
        printf("\nPlease select a property to see details:\n");
        for (i = 0; i < (int32_t)BOARD_SIZE; i++)
        {
            if (board[i].type == property)
            {
                printf("%2d - %s\n", board[i].block_id, board[i].name);
            }
        }
        printf(" 0 - Exit\n\nSelection: ");

        if (scanf("%d", &selection) != 1)
        {
            while (getchar() != '\n') { ; } /* flush bad input */
            selection = INVALID_SCAN_RESULT;
        }

        if (selection == PROP_EXIT_SELECTION)
        {
            done = true;
        }
        else
        {
            valid = false;
            for (i = 0; i < (int32_t)BOARD_SIZE; i++)
            {
                if ((board[i].block_id == selection) && (board[i].type == property))
                {
                    valid = true;
                    print_deed(&board[i]);
                }
            }
            if (!valid)
            {
                printf("Not a valid property. Please try again.\n");
            }
        }
    } while (!done);
}
