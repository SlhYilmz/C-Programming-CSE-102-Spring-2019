#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "hw6_parts.h"

#define MAX_ELEMENTS    (50U)
#define ZERO_U32        (0U)
#define ONE_U32         (1U)
#define TWO_U32         (2U)
#define SCAN_SUCCESS    (1)

/**
 * @brief Merges two sorted subarrays into one sorted range.
 * @param array Target array.
 * @param lower Start index of left range.
 * @param middle End index of left range.
 * @param higher End index of right range.
 */
static void merger_function(int32_t array[], uint32_t lower, uint32_t middle, uint32_t higher)
{
    uint32_t left_count = (middle - lower) + ONE_U32;
    uint32_t right_count = higher - middle;
    int32_t left_temp[left_count];
    int32_t right_temp[right_count];
    uint32_t left_index = ZERO_U32;
    uint32_t right_index = ZERO_U32;
    uint32_t write_index = lower;

    /* Copy left half into temporary buffer. */
    while (left_index < left_count)
    {
        left_temp[left_index] = array[lower + left_index];
        left_index++;
    }

    /* Copy right half into temporary buffer. */
    while (right_index < right_count)
    {
        right_temp[right_index] = array[(middle + ONE_U32) + right_index];
        right_index++;
    }

    left_index = ZERO_U32;
    right_index = ZERO_U32;

    /* Merge the two temporary buffers back in sorted order. */
    while ((left_index < left_count) && (right_index < right_count))
    {
        if (left_temp[left_index] <= right_temp[right_index])
        {
            array[write_index] = left_temp[left_index];
            left_index++;
        }
        else
        {
            array[write_index] = right_temp[right_index];
            right_index++;
        }

        write_index++;
    }

    /* Append any remaining elements from left buffer. */
    while (left_index < left_count)
    {
        array[write_index] = left_temp[left_index];
        write_index++;
        left_index++;
    }

    /* Append any remaining elements from right buffer. */
    while (right_index < right_count)
    {
        array[write_index] = right_temp[right_index];
        write_index++;
        right_index++;
    }
}

/**
 * @brief Recursively sorts array range using merge sort.
 * @param array Target array.
 * @param lower Start index.
 * @param higher End index.
 */
static void merge_sort(int32_t array[], uint32_t lower, uint32_t higher)
{
    if (lower < higher)
    {
        /* Split range, sort both halves, then merge. */
        uint32_t middle = (lower + higher) / TWO_U32;

        merge_sort(array, lower, middle);
        merge_sort(array, middle + ONE_U32, higher);
        merger_function(array, lower, middle, higher);
    }
}

/**
 * @brief Runs part 2 input/output flow and prints sorted list.
 */
void run_part2(void)
{
    int32_t array_list[MAX_ELEMENTS];
    uint32_t element_count = ZERO_U32;
    uint32_t index = ZERO_U32;
    int32_t scan_result = 0;

    printf("Part 2 - Recursive Sort\n");
    printf("Enter the length of the list (1..50): ");
    /* Read number of elements from user. */
    scan_result = (int32_t)scanf("%" SCNu32, &element_count);

    if (scan_result == SCAN_SUCCESS)
    {
        if ((element_count > ZERO_U32) && (element_count <= MAX_ELEMENTS))
        {
            printf("Enter the elements of list:\n");
            /* Read all list elements. */
            while (index < element_count)
            {
                scan_result = (int32_t)scanf("%" SCNd32, &array_list[index]);

                if (scan_result == SCAN_SUCCESS)
                {
                    index++;
                }
                else
                {
                    printf("Invalid element input.\n");
                    index = element_count;
                }
            }

            if (scan_result == SCAN_SUCCESS)
            {
                /* Sort and print result when all inputs are valid. */
                merge_sort(array_list, ZERO_U32, element_count - ONE_U32);
                printf("Sorted array is: ");
                index = ZERO_U32;
                while (index < element_count)
                {
                    printf("%" PRId32 " ", array_list[index]);
                    index++;
                }
                printf("\n");
            }
        }
        else
        {
            printf("Length must be between 1 and 50.\n");
        }
    }
    else
    {
        printf("Invalid length input.\n");
    }
}
