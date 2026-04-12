#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "hw6_parts.h"

#define MENU_MIN        (1U)
#define MENU_MAX        (5U)
#define EXIT_CHOICE     (0U)
#define SCAN_SUCCESS    (1)

/**
 * @brief Consumes remaining characters from input buffer after invalid scanf.
 */
static void discard_invalid_input(void)
{
    int32_t current_char = 0;
    bool done = false;

    while (done == false)
    {
        /* Read one character at a time until end of line or stream. */
        current_char = (int32_t)getchar();

        if ((current_char == '\n') || (current_char == EOF))
        {
            done = true;
        }
    }
}

/**
 * @brief Prints available homework menu operations.
 */
static void print_menu(void)
{
    printf("\n***** MENU *****\n");
    printf("1. Common Factors\n");
    printf("2. Recursive Sort\n");
    printf("3. Collatz-like Sequence\n");
    printf("4. Armstrong Numbers\n");
    printf("5. First Capital Letter\n");
    printf("0. Exit\n");
}

/**
 * @brief Program entry point for selecting and running homework parts.
 * @return int32_t Process status code.
 */
int main(void)
{
    uint32_t choice = EXIT_CHOICE;
    int32_t scan_result = 0;
    bool keep_running = true;
    int32_t status = 0;

    while (keep_running == true)
    {
        /* Show menu and read user choice. */
        print_menu();
        printf("Choice: ");
        scan_result = (int32_t)scanf("%u", &choice);

        if (scan_result == SCAN_SUCCESS)
        {
            /* Exit is handled before range-based part selection. */
            if (choice == EXIT_CHOICE)
            {
                keep_running = false;
                printf("Exiting...\n");
            }
            else if ((choice >= MENU_MIN) && (choice <= MENU_MAX))
            {
                /* Dispatch to selected homework part. */
                if (choice == 1U)
                {
                    run_part1();
                }
                else if (choice == 2U)
                {
                    run_part2();
                }
                else if (choice == 3U)
                {
                    run_part3();
                }
                else if (choice == 4U)
                {
                    run_part4();
                }
                else
                {
                    run_part5();
                }
            }
            else
            {
                printf("Unsupported value. Please enter 0..5.\n");
            }
        }
        else
        {
            /* Keep running, but clear invalid token from input stream. */
            printf("Invalid menu input. Please enter a number between 0 and 5.\n");
            discard_invalid_input();
        }
    }

    return status;
}
