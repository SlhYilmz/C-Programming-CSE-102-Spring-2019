# Copilot Instructions - C99 Algorithm Repository

## Overview

This repository is for algorithm development and verification. All code must be written with strict engineering discipline, as if targeting high-assurance software review. The rules below are non-negotiable unless explicitly overridden by the user for a specific module.

---

## 1. Language Rules (C99)

### 1.1 Standard

All code must be valid **C99**. Do not use C11 features (e.g., `_Generic`, anonymous structs) or GNU extensions (e.g., `__attribute__`, variable-length arrays in structs) unless explicitly requested.

### 1.2 Single Exit Point

Every function must have exactly **one** `return` statement, located at the very end of the function body. Early returns - even for guard clauses - are not allowed. Use a local result variable to accumulate the answer.

```c
/* CORRECT - single exit via result variable */
int32_t find_index(const int32_t *arr, int32_t size, int32_t key)
{
    int32_t result = NOT_FOUND;
    int32_t i;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            result = i;
        }
    }

    return result;
}

/* WRONG - early return is not allowed */
int32_t find_index(const int32_t *arr, int32_t size, int32_t key)
{
    for (int32_t i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            return i;   /* forbidden */
        }
    }
    return NOT_FOUND;   /* forbidden second return */
}
```

### 1.3 Fixed-Width Integer Types

Always use types from `<stdint.h>`. Never use bare `int`, `long`, `short`, or `char` for numeric purposes.

| Use this                                      | Not this                                          |
| --------------------------------------------- | ------------------------------------------------- |
| `int8_t`, `int16_t`, `int32_t`, `int64_t`     | `short`, `int`, `long`, `long long`               |
| `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` | `unsigned short`, `unsigned int`, `unsigned long` |

Use `bool` from `<stdbool.h>` for boolean variables. Do not use `int` as a boolean.

`char` is only acceptable for string literals and `printf` format strings, not for numeric storage.

### 1.4 Explicit Casts

Every type conversion must be written out explicitly at the call site. Relying on implicit promotion or truncation is not allowed, even when the conversion is "safe".

```c
uint32_t byte_count = (uint32_t)sizeof(buffer);   /* correct */
uint32_t byte_count = sizeof(buffer);             /* wrong - implicit size_t -> uint32_t */
```

### 1.5 Unsigned Literals

Suffix all unsigned integer literals with `U` and all unsigned long literals with `UL`. This applies to constants used in comparisons, initialisers, and `#define` values.

```c
#define MAX_RETRIES  (10U)
#define BASE_MASK    (0xFF00UL)

uint8_t limit = 255U;
```

### 1.6 Named Constants - No Magic Numbers

Never embed numeric literals directly in logic. Every meaningful number must be defined as a named `#define` constant. This applies to array sizes, loop bounds, bitmasks, and sentinel values.

```c
/* WRONG */
for (i = 0; i < 64; i++) { ... }

/* CORRECT */
#define BUFFER_SIZE (64U)
for (i = 0U; i < BUFFER_SIZE; i++) { ... }
```

### 1.7 Recursion

Recursive functions are **highly discouraged** because they make worst-case stack depth difficult to bound statically. Prefer an iterative implementation in all cases where one is straightforward. Recursion is acceptable only when it is demonstrably the clearest way to express the algorithm (e.g., tree traversal, divide-and-conquer) and the maximum call depth is small and documented in a comment.

```c
/* DEVIATION: Rule 1.7 - recursion used; maximum depth is log2(n) ≤ 10 for n ≤ 1024. */
```

### 1.8 Forbidden Constructs

The following are unconditionally forbidden:

- `goto`
- `malloc`, `calloc`, `realloc`, `free` - highly discouraged; use only when no static alternative exists and document the reason
- `#pragma once` - use include guards instead (see Section 2.3)

---

## 2. Formatting & Style

### 2.1 Braces - Allman Style

The opening brace of every block goes on its **own line**. Single-statement `if`, `else`, `for`, and `while` bodies must always be wrapped in braces. Never place a brace on the same line as the keyword.

```c
/* CORRECT */
if (x > 0U)
{
    result = (int32_t)x * 2;
}
else
{
    result = 0;
}

/* WRONG - K&R style, no braces on single-statement body */
if (x > 0U) {
    result = (int32_t)x * 2;
} else result = 0;
```

### 2.2 Naming Conventions

| Entity                 | Convention         | Prefix | Example                              |
| ---------------------- | ------------------ | ------ | ------------------------------------ |
| Functions              | `snake_case`       | -      | `compute_checksum()`, `find_index()` |
| Local variables        | `snake_case`       | -      | `byte_count`, `input_len`            |
| Global variables       | `snake_case`       | `g_`   | `g_system_state`, `g_frame_count`    |
| Static local variables | `snake_case`       | `s_`   | `s_call_count`, `s_last_value`       |
| Pointer variables      | `snake_case`       | `p_`   | `p_buffer`, `p_node`                 |
| `#define` constants    | `UPPER_SNAKE_CASE` | -      | `MAX_BUFFER_SIZE`, `TIMEOUT_MS`      |
| Function-like macros   | `UPPER_SNAKE_CASE` | -      | `MIN(a, b)`, `CLAMP(x, lo, hi)`      |
| Enum values            | `UPPER_SNAKE_CASE` | -      | `STATUS_OK`, `STATE_IDLE`            |
| `typedef` types        | `snake_case_t`     | -      | `node_entry_t`, `matrix_t`           |
| Enum type names        | `snake_case_t`     | -      | `status_t`, `direction_t`            |
| Source files           | `snake_case.c`     | -      | `crc_algo.c`, `ring_buffer.c`        |
| Header files           | `snake_case.h`     | -      | `crc_algo.h`, `ring_buffer.h`        |

Additional rules:

- Identifiers must not begin with an underscore.
- Abbreviations are acceptable only when universally understood (`crc`, `len`, `idx`, `buf`).
- Avoid single-letter names except for loop counters (`i`, `j`, `k`) and well-known math variables.
- Function names use a **verb-noun** structure: `compute_crc()`, `validate_input()`, `find_peak()`.

### 2.3 Header Guards

Every `.h` file must open and close with an include guard derived from the file name. `#pragma once` is not allowed.

```c
#ifndef CRC_ALGO_H
#define CRC_ALGO_H

/* public declarations */

#endif /* CRC_ALGO_H */
```

### 2.4 One Statement Per Line

Do not chain assignments or combine declarations with assignments across multiple variables on one line.

```c
/* CORRECT */
uint32_t a = 0U;
uint32_t b = 0U;

/* WRONG */
uint32_t a = 0U, b = 0U;
```

### 2.5 Explicit Boolean Comparisons

Never use a variable or return value directly as a boolean condition. Always compare it explicitly against the expected value. This makes the intent visible and prevents accidental truthy/falsy evaluation.

```c
/* CORRECT */
if (TRUE == is_ready)
{
    ...
}

if (STATUS_OK == get_status())
{
    ...
}

/* WRONG - implicit boolean conversion */
if (is_ready) { ... }
if (get_status()) { ... }
```

Note: place the constant on the **left** side of the comparison (Yoda condition). This turns an accidental assignment (`=`) into a compile-time error.

---

## 3. Robustness & Defensive Programming

### 3.1 Bounded Loops Only

Every loop must have a statically computable upper bound. Unbounded loops (`while (true)`, `for(;;)`) are not allowed unless the loop contains an explicit counter that guarantees termination, and that counter is checked in the condition.

```c
/* CORRECT - bound is statically known */
#define MAX_POLL_CYCLES (1000U)

uint32_t cycle = 0U;
bool     ready = false;

while ((cycle < MAX_POLL_CYCLES) && (!ready))
{
    ready = check_ready();
    cycle++;
}

/* WRONG - no termination guarantee */
while (!check_ready()) { }
```

### 3.2 No Recursion

Recursive functions are forbidden. All algorithms must be expressed iteratively. Stack depth must be statically determinable at compile time.

### 3.3 Initialise All Variables

Every variable must be initialised at the point of declaration. Uninitialised variables are not allowed, even if the value is overwritten before first use.

```c
/* CORRECT */
int32_t result  = 0;
uint8_t status  = 0U;
bool    is_done = false;

/* WRONG */
int32_t result;   /* uninitialised */
```

### 3.4 Validate All Inputs at Public API Boundaries

Every public function must validate its pointer arguments before dereferencing them. Null pointer dereferences must be guarded. Store the validity result in a local boolean and use it to gate all further work.

```c
bool compute_checksum(const uint8_t *data, uint32_t len, uint32_t *out)
{
    bool valid = ((data != NULL) && (out != NULL) && (len > 0U));

    if (valid)
    {
        /* safe to proceed */
    }

    return valid;
}
```

### 3.5 No Side Effects in Conditions

Boolean conditions in `if`, `while`, and `for` statements must not contain assignments or function calls with side effects. Evaluate all side-effecting calls before the condition.

```c
/* CORRECT */
status = read_sensor(&value);
if (status == STATUS_OK)
{
    process(value);
}

/* WRONG - side effect inside condition */
if (read_sensor(&value) == STATUS_OK) { ... }
```

---

## 4. Memory & Resource Discipline

### 4.1 Static Allocation Only

All buffers and data structures must be allocated statically (global or `static` local). Stack-allocated variable-length arrays are not allowed. Every array size must be a named compile-time constant.

```c
#define LOG_BUFFER_SIZE (256U)

static uint8_t log_buffer[LOG_BUFFER_SIZE];   /* correct - fixed size, static storage */
```

### 4.2 Dynamic Memory - Highly Discouraged

`malloc`, `calloc`, `realloc`, and `free` are available but **strongly discouraged**. Prefer static or stack allocation in all cases. If dynamic allocation is unavoidable, every allocation must be paired with a matching `free`, checked for `NULL` on return, and justified with a comment explaining why static allocation was not possible.

### 4.3 Stack Usage

Functions must not declare large arrays on the stack. Any buffer larger than 64 bytes must use `static` or file-scope storage. This keeps worst-case stack depth bounded and predictable.

### 4.4 Volatile for Hardware-Mapped Values

Any variable that represents a hardware register or a value that can change outside normal program flow must be declared `volatile`. Accessing such a value through a non-`volatile` pointer is not allowed.

```c
volatile uint32_t *const timer_reg = (volatile uint32_t *)TIMER_BASE_ADDR;
```

---

## 5. Deviations

If any rule in this document is intentionally violated for a specific module, the deviation must be recorded in a comment at the top of that file, stating which rule is waived and why.

```c
/* DEVIATION: Rule 4.2 - dynamic allocation used intentionally;
 * this module exists specifically to test heap-management algorithms. */
```

## 6. Testing

### 6.1 Design for Testability

Every public function must be driveable entirely through its declared interface - no side-channel inputs, no hidden global state that affects behaviour.

Design APIs so they can be driven entirely through their interface - no hidden internal state that cannot be observed or reset via the API.

Functions that depend on time, hardware registers, or I/O must accept those dependencies as parameters (dependency injection) so tests can supply controlled values:

```c
/* Testable - clock source injected */
uint32_t compute_elapsed(uint32_t start_tick, uint32_t current_tick);

/* Not testable - reads hardware directly */
uint32_t compute_elapsed(uint32_t start_tick);   /* internally calls get_hw_tick() */
```

### 6.2 File and Function Naming

- Test source files are named `test_<module>.c` (e.g., `test_crc_algo.c`).
- Each test function is named `test_<function>_<scenario>` (e.g., `test_find_index_key_not_present`).
- No shared mutable global state between tests. Every test function declares and initialises its own inputs.

### 6.3 Test Structure - Arrange / Act / Assert

Every test function follows the three-section layout below, with comments labelling each phase:

```c
static void test_compute_crc_all_zeros(void)
{
    /* Arrange */
    const uint8_t  input[]  = { 0x00U, 0x00U, 0x00U, 0x00U };
    const uint32_t expected = 0x2144DF1CUL;
    uint32_t       actual;

    /* Act */
    actual = compute_crc(input, (uint32_t)sizeof(input));

    /* Assert */
    assert(actual == expected);
}
```

Cover at least these scenarios for every function:

| Scenario         | Description                                      |
| ---------------- | ------------------------------------------------ |
| Nominal          | Typical valid input, expected output             |
| Boundary         | Input at the minimum and maximum allowed values  |
| Off-by-one       | Input just outside the boundary                  |
| Error / sentinel | Invalid input that should trigger the error path |

---

## 7. MC/DC Coverage

MC/DC (Modified Condition / Decision Coverage) requires that each individual boolean condition inside a compound expression be shown to **independently** change the overall decision outcome.

### 7.1 Rule

For every `if`, `while`, or `for` guard that contains more than one condition, produce a coverage table as a comment block directly above the related test group. The minimum number of test cases needed for a condition with N independent terms is N + 1.

### 7.2 How to Build the Table

1. List every condition in the expression as a column.
2. Add a **Decision** column for the overall result.
3. For each condition, create a pair of rows where only that condition changes and the decision flips. All other conditions are held constant.
4. Annotate each pair with an arrow comment identifying which condition it proves.

### 7.3 Example

```c
/*
 * MC/DC coverage for: if ((altitude > MIN_ALT) && (speed < MAX_SPEED))
 *
 * Test | altitude > MIN_ALT | speed < MAX_SPEED | Decision
 * -----|--------------------|-------------------|----------
 *  T1  |       true         |       true        |  true
 *  T2  |       false        |       true        |  false   <- altitude independently affects result
 *  T3  |       true         |       false       |  false   <- speed independently affects result
 *
 * Pairs: (T1, T2) prove altitude; (T1, T3) prove speed.
 */
static void test_check_flight_envelope_nominal(void) { ... }
static void test_check_flight_envelope_altitude_too_low(void) { ... }
static void test_check_flight_envelope_speed_too_high(void) { ... }
```

### 7.4 Requirement

Every compound boolean condition in the implementation must have a corresponding MC/DC table and at least the minimum covering test cases. Single-condition guards (`if (x > 0U)`) require only a true/false pair.

---
