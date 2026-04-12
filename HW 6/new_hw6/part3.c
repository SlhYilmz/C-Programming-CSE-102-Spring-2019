#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "hw6_parts.h"

#define ZERO_U32        (0U)
#define ONE_U32         (1U)
#define TWO_U32         (2U)
#define THREE_U32       (3U)
#define SCAN_SUCCESS    (1)

/**
 * @brief Recursively prints and evaluates Collatz-like sequence.
 * @param number Current value in sequence.
 * @return uint32_t Final value (expected 1 for valid positive input).
 */
static uint32_t function_calculator(uint32_t number)
{
    uint32_t result = number;

    /* Print current term before recursive step. */
    printf("%" PRIu32, number);

    if (number > ONE_U32)
    {
        /* Even numbers are halved; odd numbers map to 3n + 1. */
        if ((number % TWO_U32) == ZERO_U32)
        {
            printf(" ");
            result = function_calculator((uint32_t)(number / TWO_U32));
        }
        else
        {
            printf(" ");
            result = function_calculator((uint32_t)((THREE_U32 * number) + ONE_U32));
        }
    }

    return result;
}

/**
 * @brief Runs part 3 input/output flow for Collatz-like sequence.
 */
void run_part3(void)
{
    uint32_t number = ZERO_U32;
    int32_t scan_result = 0;

    printf("Part 3 - Collatz-like Sequence\n");
    printf("Input: ");
    /* Read sequence start number. */
    scan_result = (int32_t)scanf("%" SCNu32, &number);

    if (scan_result == SCAN_SUCCESS)
    {
        if (number > ZERO_U32)
        {
            /* Execute recursive sequence and terminate line output. */
            function_calculator(number);
            printf("\n");
        }
        else
        {
            printf("Input must be greater than 0.\n");
        }
    }
    else
    {
        printf("Invalid input number.\n");
    }
}
