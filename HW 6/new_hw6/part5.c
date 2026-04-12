#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "hw6_parts.h"

#define ZERO_U32        (0U)
#define ONE_U32         (1U)
#define SCAN_SUCCESS    (1)
#define BUFFER_SIZE     (256U)

/**
 * @brief Checks whether a character is an uppercase English letter.
 * @param character Input character.
 * @return bool true if uppercase, otherwise false.
 */
static bool is_uppercase(char character)
{
    bool result = false;

    if ((character >= 'A') && (character <= 'Z'))
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

/**
 * @brief Recursively finds first uppercase character in string.
 * @param arr Null-terminated input string.
 * @return char First uppercase letter, or '\0' when not found.
 */
static char capital_string(const char *arr)
{
    char result = '\0';

    /* Base case: end of string means not found. */
    if (arr[ZERO_U32] == '\0')
    {
        result = '\0';
    }
    else
    {
        /* Return current character or recurse on next one. */
        if (is_uppercase(arr[ZERO_U32]) == true)
        {
            result = arr[ZERO_U32];
        }
        else
        {
            result = capital_string(arr + ONE_U32);
        }
    }

    return result;
}

/**
 * @brief Runs part 5 input/output flow for first capital letter search.
 */
void run_part5(void)
{
    char input_buffer[BUFFER_SIZE];
    int32_t scan_result = 0;
    char found = '\0';

    printf("Part 5 - First Capital Letter\n");
    printf("Input string (without spaces): ");
    /* Read a single token string with bounded width. */
    scan_result = (int32_t)scanf("%255s", input_buffer);

    if (scan_result == SCAN_SUCCESS)
    {
        /* Evaluate recursive uppercase search and print result. */
        found = capital_string(input_buffer);

        if (found != '\0')
        {
            printf("%c\n", found);
        }
        else
        {
            printf("No capital letter found.\n");
        }
    }
    else
    {
        printf("Invalid string input.\n");
    }
}
