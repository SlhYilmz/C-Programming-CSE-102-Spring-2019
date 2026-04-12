#include "person.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file  person.c
 * @brief Linked-list stack implementation for the Turkish Five music stack.
 *
 * The stack head pointer @c top is kept module-private.  All callers
 * interact exclusively through the public API declared in person.h.
 */

/** @brief Head of the stack; NULL when the stack is empty. */
static struct person *top = NULL;

/* ==========================================================================
 * Internal helpers (not visible outside this translation unit)
 * ========================================================================== */

/**
 * @brief Exchange every data field of two nodes in-place.
 *
 * The @c next pointers are intentionally left untouched so the list
 * topology is preserved.  Called by both sort functions.
 *
 * @param[in,out] a  First node whose data will be swapped.
 * @param[in,out] b  Second node whose data will be swapped.
 */
static void swap_data(struct person *a, struct person *b)
{
    /* Temporary buffers to hold one side of each swap. */
    char tmp_name[NAME_MAX_LEN];
    char tmp_surname[SURNAME_MAX_LEN];
    char tmp_work[MUSICAL_WORK_MAX_LEN];
    int  tmp_age;

    /* Swap name field. */
    (void)strncpy(tmp_name,    a->name,         (size_t)NAME_MAX_LEN);
    (void)strncpy(a->name,     b->name,         (size_t)NAME_MAX_LEN);
    (void)strncpy(b->name,     tmp_name,        (size_t)NAME_MAX_LEN);

    /* Swap surname field. */
    (void)strncpy(tmp_surname, a->surname,      (size_t)SURNAME_MAX_LEN);
    (void)strncpy(a->surname,  b->surname,      (size_t)SURNAME_MAX_LEN);
    (void)strncpy(b->surname,  tmp_surname,     (size_t)SURNAME_MAX_LEN);

    /* Swap musical_work field. */
    (void)strncpy(tmp_work,    a->musical_work, (size_t)MUSICAL_WORK_MAX_LEN);
    (void)strncpy(a->musical_work, b->musical_work, (size_t)MUSICAL_WORK_MAX_LEN);
    (void)strncpy(b->musical_work, tmp_work,    (size_t)MUSICAL_WORK_MAX_LEN);

    /* Swap age field. */
    tmp_age = a->age;
    a->age  = b->age;
    b->age  = tmp_age;
}

/* ==========================================================================
 * Public API implementation
 * ========================================================================== */

/**
 * @brief Report whether the stack currently holds any elements.
 *
 * @return @c true  if the stack is empty (top == NULL).
 * @return @c false if at least one node exists.
 */
bool stack_is_empty(void)
{
    return (top == NULL);
}

/**
 * @brief Print every node in the stack from top to bottom.
 *
 * Each entry is prefixed with a 1-based display index so the user can
 * see the stack ordering at a glance.  If the stack is empty a
 * diagnostic message is printed instead.
 */
void print_stack(void)
{
    const struct person *current_node  = top; /* Walker pointer; starts at the top. */
    uint32_t             display_index = 1U;  /* 1-based position shown to the user. */

    if (current_node == NULL)
    {
        printf("There is no more people left!\n\n");
    }
    else
    {
        while (current_node != NULL)
        {
            printf("%u) %s\n", (unsigned int)display_index, current_node->name);
            printf("   %s\n",   current_node->surname);
            printf("   %s\n",   current_node->musical_work);
            printf("   %d\n\n", current_node->age);

            current_node = current_node->next; /* Advance to the next node. */
            display_index++;
        }
    }
}

/**
 * @brief Allocate a new node and push it onto the top of the stack.
 *
 * String fields are copied with bounded length and explicitly
 * null-terminated to prevent buffer overruns.
 *
 * @param[in] name      First (and middle) name of the composer.
 * @param[in] surname   Family name of the composer.
 * @param[in] creation  Title of the notable musical work.
 * @param[in] age       Age of the composer at time of death.
 */
void add_node(char name[], char surname[], char creation[], int age)
{
    /* Allocate a new node on the heap. */
    struct person *new_node = (struct person *)malloc(sizeof(struct person));

    if (new_node != NULL)
    {
        /* Copy string fields with explicit length bounds and null-terminate. */
        (void)strncpy(new_node->name,         name,     (size_t)(NAME_MAX_LEN - 1U));
        new_node->name[NAME_MAX_LEN - 1U] = '\0';

        (void)strncpy(new_node->surname,      surname,  (size_t)(SURNAME_MAX_LEN - 1U));
        new_node->surname[SURNAME_MAX_LEN - 1U] = '\0';

        (void)strncpy(new_node->musical_work, creation, (size_t)(MUSICAL_WORK_MAX_LEN - 1U));
        new_node->musical_work[MUSICAL_WORK_MAX_LEN - 1U] = '\0';

        new_node->age = age;

        /* Link the new node in front of the current top (LIFO push). */
        new_node->next = top;
        top            = new_node;
    }
    else
    {
        printf("Memory allocation failed.\n");
    }
}

/**
 * @brief Pop the top node off the stack and free its memory.
 *
 * If the stack is already empty a diagnostic message is printed and
 * no memory operation is performed.
 */
void delete_node(void)
{
    /* Keep a reference to the top node before advancing the head pointer. */
    struct person *node_to_free = top;

    if (top != NULL)
    {
        top = top->next; /* Advance the stack head to the next node. */
        free(node_to_free);
    }
    else
    {
        printf("Stack is empty. Nothing to pop.\n");
    }
}

/* -----------------------------------------------------------------------
 * Comparators used by sort_stack.
 * Each returns > 0 when (a) should come after (b), matching the
 * convention of the C standard library's qsort comparator.
 * ----------------------------------------------------------------------- */

/** @brief Compare two nodes by first name (lexicographic, A -> Z). */
static int cmp_name(const struct person *a, const struct person *b)
{
    return strcmp(a->name, b->name);
}

/** @brief Compare two nodes by age (ascending). */
static int cmp_age(const struct person *a, const struct person *b)
{
    int result = 0;

    if (a->age > b->age)
    {
        result = 1;
    }
    else if (a->age < b->age)
    {
        result = -1;
    }

    return result;
}

/**
 * @brief Generic in-place bubble sort over the stack.
 *
 * Data fields are swapped between nodes (next pointers stay fixed).
 * After sorting, the updated stack is printed.
 *
 * @param[in] cmp  Comparator: returns > 0 when @p a should come after @p b.
 */
typedef int (*person_cmp_fn_t)(const struct person *a,
                               const struct person *b);

static void sort_stack(person_cmp_fn_t cmp)
{
    struct person *outer_node = NULL; /* Outer bubble-sort pass pointer. */
    struct person *inner_node = NULL; /* Inner bubble-sort pass pointer. */

    if (top == NULL)
    {
        printf("Stack is empty. Cannot sort.\n");
    }
    else
    {
        for (outer_node = top; outer_node != NULL; outer_node = outer_node->next)
        {
            for (inner_node = outer_node->next; inner_node != NULL; inner_node = inner_node->next)
            {
                if (cmp(outer_node, inner_node) > 0)
                {
                    swap_data(outer_node, inner_node);
                }
            }
        }
        print_stack();
    }
}

/** @brief Sort the stack alphabetically by first name (A -> Z) and print it. */
void sort_alphabetically(void)
{
    sort_stack(cmp_name);
}

/** @brief Sort the stack by age in increasing order and print it. */
void sort_increasingly(void)
{
    sort_stack(cmp_age);
}

/**
 * @brief Release all heap memory owned by the stack and reset it to empty.
 *
 * Safe to call on an already-empty stack; the while loop simply does
 * not execute in that case.
 */
void free_all(void)
{
    struct person *node_to_free; /* Holds the node being released each iteration. */

    while (top != NULL)
    {
        node_to_free = top;          /* Remember the current top before advancing. */
        top          = top->next;    /* Advance the head to the next node. */
        free(node_to_free);          /* Release the previous top. */
    }
}
