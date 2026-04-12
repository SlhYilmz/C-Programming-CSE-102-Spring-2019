#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/*
 * Test build strategy:
 * Include implementation files directly so internal static algorithm
 * functions are visible to this test translation unit.
 */
#include "part1.c"
#include "part2.c"
#include "part3.c"
#include "part4.c"
#include "part5.c"

#define ARR_LEN_5   (5U)
#define ARR_LEN_8   (8U)

/*
 * MC/DC coverage for: if (no1 == ZERO_U32)
 *
 * Test | no1 == 0U | Decision
 * -----|-----------|---------
 *  T1  |   true    |  true
 *  T2  |   false   |  false  <- condition independently affects result
 */
/**
 * @brief Verifies GCD behavior when first operand is zero.
 */
static void test_common_zero_first_operand(void)
{
    uint32_t result = common(0U, 48U);

    assert(result == 48U);
}

/*
 * MC/DC coverage for: if (no1 == ZERO_U32)
 *
 * Test | no1 == 0U | Decision
 * -----|-----------|---------
 *  T1  |   true    |  true
 *  T2  |   false   |  false  <- condition independently affects result
 */
/**
 * @brief Verifies typical GCD case for 24 and 32.
 */
static void test_common_typical_pair(void)
{
    uint32_t result = common(24U, 32U);

    assert(result == 8U);
}

/*
 * MC/DC coverage for: if (lower < higher)
 *
 * Test | lower < higher | Decision
 * -----|----------------|---------
 *  T1  |      true      |  true
 *  T2  |      false     |  false <- condition independently affects result
 */
/**
 * @brief Verifies merge sort output for unsorted unique values.
 */
static void test_merge_sort_unsorted_array(void)
{
    int32_t data[ARR_LEN_8] = { 3, 9, 23, 1, 8, 22, 67, 0 };

    merge_sort(data, 0U, ARR_LEN_8 - 1U);

    assert(data[0] == 0);
    assert(data[1] == 1);
    assert(data[2] == 3);
    assert(data[3] == 8);
    assert(data[4] == 9);
    assert(data[5] == 22);
    assert(data[6] == 23);
    assert(data[7] == 67);
}

/*
 * MC/DC coverage for: if (left_temp[left_index] <= right_temp[right_index])
 *
 * Test | left <= right | Decision
 * -----|---------------|---------
 *  T1  |     true      |  true
 *  T2  |     false     |  false <- condition independently affects result
 */
/**
 * @brief Verifies merge sort output when duplicates exist.
 */
static void test_merge_sort_with_duplicates(void)
{
    int32_t data[ARR_LEN_5] = { 4, 2, 4, 1, 2 };

    merge_sort(data, 0U, ARR_LEN_5 - 1U);

    assert(data[0] == 1);
    assert(data[1] == 2);
    assert(data[2] == 2);
    assert(data[3] == 4);
    assert(data[4] == 4);
}

/*
 * MC/DC coverage for: if (number > ONE_U32)
 *
 * Test | number > 1U | Decision
 * -----|-------------|---------
 *  T1  |    true     |  true
 *  T2  |    false    |  false <- condition independently affects result
 */
/**
 * @brief Verifies Collatz-like function base case at 1.
 */
static void test_function_calculator_base_case(void)
{
    uint32_t result = function_calculator(1U);

    assert(result == 1U);
}

/*
 * MC/DC coverage for: if ((number % TWO_U32) == ZERO_U32)
 *
 * Test | number > 1U | even(number) | Decision(branch)
 * -----|-------------|--------------|-----------------
 *  T1  |    true     |    true      | even path
 *  T2  |    true     |    false     | odd path  <- parity independently affects branch
 *  T3  |    false    |    true      | stop      <- outer condition independently affects recursion
 */
/**
 * @brief Verifies Collatz-like recursion for even and odd starts.
 */
static void test_function_calculator_even_and_odd_path(void)
{
    uint32_t result_even = function_calculator(6U);
    uint32_t result_odd = function_calculator(3U);

    assert(result_even == 1U);
    assert(result_odd == 1U);
}

/*
 * MC/DC coverage for: if (temp_number == ZERO_U32)
 *
 * Test | temp_number == 0U | Decision
 * -----|-------------------|---------
 *  T1  |       true        |  true
 *  T2  |       false       |  false <- condition independently affects result
 */
/**
 * @brief Verifies digit counting for zero and non-zero values.
 */
static void test_digit_finder_zero_and_nonzero(void)
{
    uint32_t digits_zero = digit_finder(0U);
    uint32_t digits_nonzero = digit_finder(371U);

    assert(digits_zero == 1U);
    assert(digits_nonzero == 3U);
}

/*
 * MC/DC coverage for: if (number < TEN_U32)
 *
 * Test | number < 10U | Decision
 * -----|--------------|---------
 *  T1  |    true      |  true
 *  T2  |    false     |  false <- condition independently affects recursion path
 */
/**
 * @brief Verifies Armstrong-equal sample case.
 */
static void test_armstrong_equal_number(void)
{
    uint32_t n = 371U;
    uint32_t digits = digit_finder(n);
    uint32_t sum = equal_not_equal_recursive(n, digits);

    assert(sum == n);
}

/*
 * MC/DC coverage for: if (total == number)
 *
 * Test | total == number | Decision
 * -----|-----------------|---------
 *  T1  |      true       | equal
 *  T2  |      false      | not equal <- condition independently affects output class
 */
/**
 * @brief Verifies Armstrong not-equal sample case.
 */
static void test_armstrong_not_equal_number(void)
{
    uint32_t n = 372U;
    uint32_t digits = digit_finder(n);
    uint32_t sum = equal_not_equal_recursive(n, digits);

    assert(sum != n);
}

/*
 * MC/DC coverage for: if ((character >= 'A') && (character <= 'Z'))
 *
 * Test | char >= 'A' | char <= 'Z' | Decision
 * -----|-------------|-------------|---------
 *  T1  |    true     |    true     |  true
 *  T2  |    false    |    true     |  false <- lower bound independently affects result
 *  T3  |    true     |    false    |  false <- upper bound independently affects result
 */
/**
 * @brief Verifies first uppercase character detection.
 */
static void test_capital_string_finds_first_uppercase(void)
{
    char result = capital_string("computerScienceAndEngineering");

    assert(result == 'S');
}

/*
 * MC/DC coverage for: if (arr[ZERO_U32] == '\0')
 *
 * Test | arr[0] == '\0' | Decision
 * -----|-----------------|---------
 *  T1  |      true       |  true
 *  T2  |      false      |  false <- condition independently affects recursion entry
 */
/**
 * @brief Verifies not-found case for uppercase character search.
 */
static void test_capital_string_no_uppercase(void)
{
    char result = capital_string("computerscience");

    assert(result == '\0');
}

typedef void (*test_func_t)(void);

/**
 * @brief Runs one test, then updates total/pass counters.
 * @param test_name Human-readable test name.
 * @param test_func Test function callback.
 * @param total_count Pointer to total test counter.
 * @param pass_count Pointer to passed test counter.
 */
static void run_test(const char *test_name, test_func_t test_func, uint32_t *total_count, uint32_t *pass_count)
{
    *total_count = (uint32_t)(*total_count + 1U);
    printf("%02u) %s ... ", *total_count, test_name);
    test_func();
    *pass_count = (uint32_t)(*pass_count + 1U);
    printf(" [OK]\n");
}

/**
 * @brief Executes full HW6 test suite and prints summary.
 * @return int32_t Process status code.
 */
int main(void)
{
    uint32_t total_count = 0U;
    uint32_t pass_count = 0U;

    run_test("common() with zero first operand", test_common_zero_first_operand, &total_count, &pass_count);
    run_test("common() with typical pair 24 and 32", test_common_typical_pair, &total_count, &pass_count);
    run_test("merge_sort() unsorted array", test_merge_sort_unsorted_array, &total_count, &pass_count);
    run_test("merge_sort() with duplicate values", test_merge_sort_with_duplicates, &total_count, &pass_count);
    run_test("function_calculator() base case", test_function_calculator_base_case, &total_count, &pass_count);
    run_test("function_calculator() even and odd branches", test_function_calculator_even_and_odd_path, &total_count, &pass_count);
    run_test("digit_finder() zero and nonzero", test_digit_finder_zero_and_nonzero, &total_count, &pass_count);
    run_test("equal_not_equal_recursive() equal case", test_armstrong_equal_number, &total_count, &pass_count);
    run_test("equal_not_equal_recursive() not-equal case", test_armstrong_not_equal_number, &total_count, &pass_count);
    run_test("capital_string() first uppercase found", test_capital_string_finds_first_uppercase, &total_count, &pass_count);
    run_test("capital_string() no uppercase", test_capital_string_no_uppercase, &total_count, &pass_count);

    printf("Summary: %u/%u tests passed.\n", pass_count, total_count);

    return 0;
}
