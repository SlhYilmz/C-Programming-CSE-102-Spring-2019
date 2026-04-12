#include "person.h"

#include <stdio.h>
#include <stdint.h>

/* -----------------------------------------------------------------------
 * Menu choice constants
 * ----------------------------------------------------------------------- */
#define MENU_ADD_PERSON  (1)
#define MENU_POP_PERSON  (2)
#define MENU_SORT_ALPHA  (3)
#define MENU_SORT_AGE    (4)
#define MENU_EXIT        (5)

/*
 * scanf format strings — widths are NAME_MAX_LEN-1, SURNAME_MAX_LEN-1,
 * and MUSICAL_WORK_MAX_LEN-1 respectively (31, 31, 63).
 * The leading space skips any leftover whitespace / newline in the buffer.
 */
#define SCANF_NAME_FMT          " %31[^\n]"
#define SCANF_SURNAME_FMT       " %31[^\n]"
#define SCANF_MUSICAL_WORK_FMT  " %63[^\n]"

/* -----------------------------------------------------------------------
 * menu — interactive loop; drives the stack via the person.h API.
 * ----------------------------------------------------------------------- */
static void menu(void)
{
    int  choice;
    int  scan_age;
    char name[NAME_MAX_LEN];
    char surname[SURNAME_MAX_LEN];
    char musical_work[MUSICAL_WORK_MAX_LEN];

    do
    {
        printf("\n************ MENU ************\n");
        printf("1- Add a Person to the Stack\n");
        printf("2- Pop a Person from the Stack\n");
        printf("3- Sort Alphabetical Order\n");
        printf("4- Sort Age in Increasing Order\n");
        printf("5- Exit menu\n");
        printf("******************************\n");
        printf("Select your Choice: ");
        (void)scanf("%d", &choice);

        switch (choice)
        {
            case MENU_ADD_PERSON:
            {
                printf("Name: ");
                (void)scanf(SCANF_NAME_FMT, name);
                printf("Surname: ");
                (void)scanf(SCANF_SURNAME_FMT, surname);
                printf("Creation: ");
                (void)scanf(SCANF_MUSICAL_WORK_FMT, musical_work);
                printf("Age: ");
                (void)scanf("%d", &scan_age);
                add_node(name, surname, musical_work, (int32_t)scan_age);
                print_stack();
                break;
            }
            case MENU_POP_PERSON:
            {
                delete_node();
                print_stack();
                break;
            }
            case MENU_SORT_ALPHA:
            {
                sort_alphabetically();
                break;
            }
            case MENU_SORT_AGE:
            {
                sort_increasingly();
                break;
            }
            case MENU_EXIT:
            {
                free_all();
                printf("Exiting...\n");
                break;
            }
            default:
            {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }
    while (choice != MENU_EXIT);
}

int main(void)
{
    menu();
    return 0;
}
