/**
 * @file types.h
 * @brief Shared constants, enumerations, and data structures for the Monopoly game.
 */

#ifndef TYPES_H
#define TYPES_H

/* -----------------------------------------------------------------------
 * Named constants
 * --------------------------------------------------------------------- */

#define BOARD_SIZE         (24)      /**< Number of squares on the board. */
#define MAX_OWNED_BLOCKS   (12)      /**< Max properties one player can own. */
#define STARTING_MONEY     (150000)  /**< Each player's starting balance ($). */
#define PASS_START_BONUS   (10000)   /**< Cash awarded for passing Start. */
#define MAX_HOUSES         (3)       /**< Max houses buildable on one property. */
#define SELL_REFUND_RATIO  (2)       /**< Bank refunds price / SELL_REFUND_RATIO on sale. */
#define WAIT_TWO_TURNS     (2)       /**< Turns-to-skip value for a "Wait 2" punish block. */
#define WAIT_ONE_TURN      (1)       /**< Turns-to-skip value for a "Wait 1" punish block. */
#define NO_BLOCK           (-1)      /**< Sentinel for an empty slot in owned_block_ids. */
#define START_BLOCK_ID     (0)       /**< Board index of the starting square. */
#define NO_WAIT_TURNS      (0)       /**< Initial / reset value for player::turn_to_wait. */
#define NO_ACCOUNT_BALANCE (0)       /**< Account balance used in an unowned-block sentinel player. */

/* -----------------------------------------------------------------------
 * Enumerated types
 * --------------------------------------------------------------------- */

/**
 * @brief Functional category of a board square.
 *
 * Determines how a landing event is handled and how @c block::price is
 * interpreted (purchase price / tax fee / turns-to-skip / unused).
 */
typedef enum block_type
{
    start,    /**< Starting square; awards @c PASS_START_BONUS on pass-through. */
    property, /**< Purchasable real-estate square. */
    tax,      /**< Deducts a fixed fee (@c price) from the landing player. */
    punish,   /**< Skips the landing player for @c price opponent turns. */
    fortune   /**< Fortune card square; player draws a random fortune card. */
} block_type;

/**
 * @brief Token type of a player; @c noone doubles as an "unowned" sentinel.
 */
typedef enum player_type
{
    noone, /**< No player / block is unowned. */
    cap,   /**< Cap token. */
    car    /**< Car token. */
} player_type;

/* -----------------------------------------------------------------------
 * Data structures
 * --------------------------------------------------------------------- */

/**
 * @brief State of one player (or an unowned-block sentinel when type == noone).
 */
struct player
{
    player_type type;                      /**< Token; @c noone means unowned when used inside @c block::owner. */
    int current_block_id;                  /**< Current board position (index into board[]). */
    int owned_block_ids[MAX_OWNED_BLOCKS]; /**< Owned property indices; empty slots hold @c NO_BLOCK. */
    int account;                           /**< Current cash balance ($). */
    int turn_to_wait;                      /**< Remaining turns to sit out from a punish block. */
    char* name;                            /**< Player display name (caller-managed). */
};

/**
 * @brief A single square on the board.
 *
 * @c price meaning by type: @c property → buy price; @c tax → fee; @c punish → turns to skip; @c start → 0.
 */
struct block
{
    int block_id;        /**< Board position index (0 - BOARD_SIZE-1). */
    char* name;          /**< Label displayed on the square. */
    int price;           /**< Buy price / tax fee / turns-to-skip (see struct note). */
    int rent;            /**< Rent with 0 houses. */
    int rent_1;          /**< Rent with 1 house. */
    int rent_2;          /**< Rent with 2 houses. */
    int rent_3;          /**< Rent with 3 houses. */
    int house_price;     /**< Cost to build one house ($). */
    int house_count;     /**< Houses currently built (0 - MAX_HOUSES). */
    struct player owner; /**< Owning player; @c owner.type == @c noone means unowned. */
    block_type type;     /**< Functional category of this square. */
    struct block* next;  /**< Next square in the linked list; NULL for the last node. */
};

#endif /* TYPES_H */
