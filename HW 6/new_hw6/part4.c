#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include "hw6_parts.h"

#define ZERO_U32        (0U)
#define ONE_U32         (1U)
#define TEN_U32         (10U)
#define SCAN_SUCCESS    (1)

/**
 * @brief Computes power recursively for non-negative exponent.
 * @param base Base value.
 * @param exponent Exponent value.
 * @return uint32_t base^exponent.
 */
static uint32_t recursive_pow(uint32_t base, uint32_t exponent)
{
    uint32_t result = ONE_U32;

    /* Base case: any number power 0 is 1. */
    if (exponent == ZERO_U32)
    {
        result = ONE_U32;
    }
    else
    {
        /* Recursive multiplication for remaining exponent. */
        result = (uint32_t)(base * recursive_pow(base, (uint32_t)(exponent - ONE_U32)));
    }

    return result;
}

/**
 * @brief Finds decimal digit count for a non-negative number.
 * @param number Input number.
 * @return uint32_t Number of decimal digits.
 */
static uint32_t digit_finder(uint32_t number)
{
    uint32_t result = ZERO_U32;
    uint32_t temp_number = number;

    /* Zero has one digit by definition in this workflow. */
    if (temp_number == ZERO_U32)
    {
        result = ONE_U32;
    }
    else
    {
        /* Count digits by repeated division by 10. */
        while (temp_number > ZERO_U32)
        {
            result++;
            temp_number = (uint32_t)(temp_number / TEN_U32);
        }
    }

    return result;
}

/**
 * @brief Recursively computes sum of digits raised to digit count.
 * @param number Current sub-number.
 * @param number_of_digits Original number's digit count.
 * @return uint32_t Sum of powered digits.
 */
static uint32_t equal_not_equal_recursive(uint32_t number, uint32_t number_of_digits)
{
    uint32_t result = ZERO_U32;

    /* Base case: one digit remains. */
    if (number < TEN_U32)
    {
        result = recursive_pow(number, number_of_digits);
    }
    else
    {
        /* Split current digit and recurse on remaining prefix. */
        uint32_t lower_digit = (uint32_t)(number % TEN_U32);
        uint32_t remaining = (uint32_t)(number / TEN_U32);

        result = (uint32_t)(recursive_pow(lower_digit, number_of_digits) + equal_not_equal_recursive(remaining, number_of_digits));
    }

    return result;
}

/**
 * @brief Prints whether number satisfies Armstrong equality.
 * @param number Input number.
 */
static void check_number_equality(uint32_t number)
{
    uint32_t number_of_digits = digit_finder(number);
    uint32_t total = equal_not_equal_recursive(number, number_of_digits);
    bool is_equal = false;

    /* Compare powered-digit sum against original input. */
    if (total == number)
    {
        is_equal = true;
    }
    else
    {
        is_equal = false;
    }

    if (is_equal == true)
    {
        printf("Equal\n");
    }
    else
    {
        printf("Not Equal\n");
    }
}

/**
 * @brief Runs part 4 input/output flow for Armstrong check.
 */
void run_part4(void)
{
    uint32_t number = ZERO_U32;
    int32_t scan_result = 0;

    printf("Part 4 - Armstrong Numbers\n");
    printf("Input: ");
    /* Read number to validate against Armstrong rule. */
    scan_result = (int32_t)scanf("%" SCNu32, &number);

    if (scan_result == SCAN_SUCCESS)
    {
        check_number_equality(number);
    }
    else
    {
        printf("Invalid input number.\n");
    }
}
