#ifndef PERSON_H
#define PERSON_H

#include <stdint.h>
#include <stdbool.h>

/** @defgroup sizes  String buffer sizes
 *  Maximum character counts for each text field, including the null terminator.
 *  @{ */
#define NAME_MAX_LEN          (32U)  /**< Max bytes for a composer's first/middle name. */
#define SURNAME_MAX_LEN       (32U)  /**< Max bytes for a composer's family name.       */
#define MUSICAL_WORK_MAX_LEN  (64U)  /**< Max bytes for the title of the musical work.  */
/** @} */

/**
 * @brief One node in the music stack.
 *
 * The @c top pointer that references the head of the stack is kept
 * private inside person.c; callers must not access it directly.
 */
struct person
{
    char name[NAME_MAX_LEN];                 /**< First (and middle) name.   */
    char surname[SURNAME_MAX_LEN];           /**< Family name.               */
    char musical_work[MUSICAL_WORK_MAX_LEN]; /**< Title of notable work.  */
    int age;                             /**< Age at time of death.      */
    struct person *next;                     /**< Link to the node below.    */
};

/* ==========================================================================
 * Public API
 * ========================================================================== */

/**
 * @brief Push a new person onto the top of the stack.
 *
 * @param[in] name      First (and middle) name of the composer.
 * @param[in] surname   Family name of the composer.
 * @param[in] creation  Title of the notable musical work.
 * @param[in] age       Age of the composer at time of death.
 */
void add_node(char name[], char surname[], char creation[], int age);

/**
 * @brief Pop the top person from the stack and free the node.
 *
 * Prints a diagnostic message if the stack is already empty.
 */
void delete_node(void);

/**
 * @brief Print every element of the stack from top to bottom.
 *
 * Each entry is shown with a 1-based index, name, surname,
 * musical work, and age.
 */
void print_stack(void);

/**
 * @brief Sort the stack alphabetically by first name (A -> Z) then print it.
 */
void sort_alphabetically(void);

/**
 * @brief Sort the stack by age in increasing order then print it.
 */
void sort_increasingly(void);

/**
 * @brief Report whether the stack is empty.
 *
 * @return @c true  if the stack contains no elements.
 * @return @c false otherwise.
 */
bool stack_is_empty(void);

/**
 * @brief Release all heap memory owned by the stack and reset it to empty.
 *
 * Safe to call on an already-empty stack.
 */
void free_all(void);

#endif /* PERSON_H */
