# Copilot Instructions — Verification-Focused Algorithm Repository (C99)

## Purpose

This repository exists solely for algorithm development, prototyping, and verification.
It is not production software, but it must be written with strict engineering discipline suitable for high-assurance verification work.

---

## Verification Alignment

Although this project is not certification software, all work must follow rigorous verification discipline.

### MC/DC — Modified Condition / Decision Coverage

Every boolean condition in the algorithm must be independently shown to affect the decision outcome.

**Example:**

```c
if ((x > 0U) && (y < MAX_VALUE))
```

Test cases must demonstrate:

- `x` affects the result independently (hold `y` true, vary `x`)
- `y` affects the result independently (hold `x` true, vary `y`)

When generating test cases, always produce the full MC/DC matrix as a comment block above each test function.

---

## Code Style — C99

### Language Standard

All code must be valid C99. Do not use C11 or GNU extensions unless explicitly requested.

---

### Single Exit Point

Functions must have exactly **one** `return` statement, placed at the end.

**Correct:**

```c
int32_t foo(uint8_t x)
{
    int32_t result = -1;

    if (x > 0U)
    {
        result = (int32_t)x * 2;
    }

    return result;
}
```

**Incorrect — multiple returns:**

```c
int32_t foo(uint8_t x)
{
    if (x == 0U)
    {
        return -1;        /* early return: not allowed */
    }

    return (int32_t)x * 2;
}
```

---

### Integer Types

Use fixed-width integers from `<stdint.h>` whenever possible.

| Allowed    | Discouraged |
|------------|-------------|
| `uint8_t`  | `int`       |
| `uint16_t` | `long`      |
| `uint32_t` | `short`     |
| `int8_t`   | `char` (numeric use) |
| `int16_t`  |             |
| `int32_t`  |             |
| `int64_t` / `uint64_t` (when range requires it) | |

Use `bool` from `<stdbool.h>` for boolean variables. Do not use `int` as a boolean.

---

### Explicit Casting

Implicit numeric conversions are not allowed. Every type change must be made visible at the call site.

**Correct:**

```c
result = (uint32_t)value;
```

**Incorrect:**

```c
result = value;   /* implicit conversion: not allowed */
```

---

### Unsigned Literals

Suffix all unsigned integer literals with `U`. Suffix all unsigned long literals with `UL`.

```c
uint8_t limit = 255U;
uint32_t mask = 0xFFFF0000UL;
```

---

### Braces and Formatting

- Opening brace on its own line (Allman style).
- Always use braces, even for single-statement `if`/`else`/`for`/`while` bodies.
- One statement per line.

```c
if (x > 0U)
{
    result = (int32_t)x;
}
```

---

### Naming Conventions

| Entity         | Convention              | Example              |
|----------------|-------------------------|----------------------|
| Functions       | `snake_case`            | `compute_crc()`      |
| Variables       | `snake_case`            | `byte_count`         |
| Constants/Macros| `UPPER_SNAKE_CASE`      | `MAX_BUFFER_SIZE`    |
| Types (typedef) | `snake_case_t`          | `matrix_entry_t`     |
| File names      | `snake_case.c` / `.h`   | `crc_algo.c`         |

---

### Magic Numbers

Do not use numeric literals inline. Every constant must be named.

```c
#define MAX_ITERATIONS  (100U)

for (uint32_t i = 0U; i < MAX_ITERATIONS; i++)
```

---

### Header Guards

Every `.h` file must use include guards (not `#pragma once`).

```c
#ifndef CRC_ALGO_H
#define CRC_ALGO_H

/* declarations */

#endif /* CRC_ALGO_H */
```

---

## Testing Philosophy

Code here exists to verify algorithms against High-Level Requirements (HLRs).

### Testability Requirements

- Every public API **must** be independently testable.
- Design APIs so they can be driven entirely through their interface — no hidden internal state that cannot be observed or reset via the API.
- Functions that depend on time, I/O, or hardware must accept those dependencies as parameters (dependency injection), not access them directly.

### Test File Conventions

- Test files are named `test_<module>.c`.
- Each test function is named `test_<function>_<scenario>`.
- Tests must not share mutable global state; each test resets its own inputs.

### Test Function Structure

```c
static void test_compute_crc_nominal(void)
{
    /* Arrange */
    const uint8_t  input[]   = { 0x01U, 0x02U, 0x03U };
    const uint32_t expected  = 0xABCD1234UL;
    uint32_t       actual;

    /* Act */
    actual = compute_crc(input, (uint32_t)sizeof(input));

    /* Assert */
    assert(actual == expected);
}
```

### MC/DC Test Comment Block

Prepend every test group with an MC/DC coverage table:

```c
/*
 * MC/DC coverage for: if ((x > 0U) && (y < MAX_VALUE))
 *
 * Test | x > 0U | y < MAX_VALUE | Decision
 * -----|--------|---------------|----------
 *  T1  |  true  |     true      |  true
 *  T2  |  false |     true      |  false   <- x independently affects result
 *  T3  |  true  |     false     |  false   <- y independently affects result
 */
```

---

## What Copilot Must NOT Generate

- Multiple `return` statements in a single function.
- Bare `int`, `long`, `short`, or `unsigned` without a fixed-width typedef.
- Implicit casts between integer types.
- Numeric literals without context (use named constants).
- `goto` statements.
- Dynamic memory allocation (`malloc`, `calloc`, `realloc`, `free`) unless the module under test explicitly exercises a dynamic-memory algorithm.
- `#pragma once` in place of include guards.
