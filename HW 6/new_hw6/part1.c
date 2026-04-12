#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "hw6_parts.h"

#define ZERO_U32        (0U)
#define ONE_U32         (1U)
#define TWO_U32         (2U)
#define SCAN_SUCCESS    (1)

/**
 * @brief Recursively computes GCD using Euclid's algorithm.
 * @param no1 First number.
 * @param no2 Second number.
 * @return uint32_t Greatest common divisor.
 */
static uint32_t common(uint32_t no1, uint32_t no2)
{
    uint32_t result = ZERO_U32;

    /* Base case: GCD(0, x) = x. */
    if (no1 == ZERO_U32)
    {
        result = no2;
    }
    else
    {
        /* Recursive reduction step: GCD(a, b) = GCD(b % a, a). */
        result = common((uint32_t)(no2 % no1), no1);
    }

    return result;
}

/**
 * @brief Prints prime-factor multiplication form of the given product.
 * @param value Product value to represent as multiplication expression.
 */
static void print_common_factor_product(uint32_t value)
{
    uint32_t remaining = value;
    uint32_t divisor = TWO_U32;
    uint32_t factor_count = ZERO_U32;

    if (value <= ONE_U32)
    {
        printf("%" PRIu32 " = %" PRIu32 "\n", value, value);
    }
    else
    {
        /* Print repeated prime factors in multiplication format. */
        while ((remaining > ONE_U32) && ((divisor * divisor) <= remaining))
        {
            while ((remaining % divisor) == ZERO_U32)
            {
                if (factor_count > ZERO_U32)
                {
                    printf("*");
                }

                printf("%" PRIu32, divisor);
                remaining = (uint32_t)(remaining / divisor);
                factor_count++;
            }

            divisor++;
        }

        /* Any remaining value greater than 1 is also a prime factor. */
        if (remaining > ONE_U32)
        {
            if (factor_count > ZERO_U32)
            {
                printf("*");
            }

            printf("%" PRIu32, remaining);
        }

        printf(" = %" PRIu32 "\n", value);
    }
}

/**
 * @brief Runs part 1 input/output flow and prints common factors product.
 */
void run_part1(void)
{
    uint32_t first_number = ZERO_U32;
    uint32_t second_number = ZERO_U32;
    uint32_t gcd_result = ZERO_U32;
    int32_t scan_result = 0;

    printf("Part 1 - Common Factors\n");
    printf("First number: ");
    /* Read first operand. */
    scan_result = (int32_t)scanf("%" SCNu32, &first_number);

    if (scan_result == SCAN_SUCCESS)
    {
        printf("Second number: ");
        /* Read second operand. */
        scan_result = (int32_t)scanf("%" SCNu32, &second_number);

        if (scan_result == SCAN_SUCCESS)
        {
            /* Compute common product and print factorized format. */
            gcd_result = common(first_number, second_number);
            print_common_factor_product(gcd_result);
        }
        else
        {
            printf("Invalid second number input.\n");
        }
    }
    else
    {
        printf("Invalid first number input.\n");
    }
}
