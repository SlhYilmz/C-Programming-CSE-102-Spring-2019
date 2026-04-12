This document outlines Homework #6 for the Spring 2019 CSE102 Computer Programming course, focusing on recursive function implementation for mathematical sequences, sorting algorithms, and string processing.

---

**Spring 2019**
**CSE102-Computer Programming**
**Due Date:** 13/04/2019
**Homework #6**

**Hand in:** A student with number 20180000001 should hand in a file named 20180000001.c for this homework.

---

### 1) Common Factors
Write a code which should perform the following operations. It has to take two numbers from user and find multipliers of numbers with a `common()` function.

For example:
* Factors of 24 {2,2,2,3}
* Factors of 32 {2,2,2,2,2}

Then calculate the common factors recursively which are {2,2,2} and function has to return $2*2*2$.

---

### 2) Recursive Sort
Write a code which should perform the following operations. User should enter the length of list and list elements like the list. You can take the list of numbers in the main function. 

**Example:**
Enter the length of the list: 10
Enter the elements of list:
3, 9, 23, 1, 8, 22, 67, 0, 16, 52

Then you should create a function that takes the numbers and show the new list with increasing order. Function has to divide the list into two lists recursively until it can no more be divided. After that it combines all elements with increasing order.

**Output:**
Sorted array is: 0 1 3 8 9 16 22 23 52 67.

---

### 3) Collatz-like Sequence
Write a code which should perform the following operations. User should enter an input number. Then create a function which will calculate the output numbers recursively using following formula:

$$f(n) = \begin{cases} n/2 & \text{if } n \equiv 0 \pmod 2 \\ 3n+1 & \text{if } n \equiv 1 \pmod 2 \end{cases}$$

**Example:**
* **Input:** 45
* **Output:** 45 136 68 34 17 52 26 13 40 20 10 5 16 8 4 2 1

---

### 4) Armstrong Numbers
Write a code which should perform the following operations. User should enter a number and the code has to check if the number fits the formula or not. Create a function which is checking the input number recursively. Function should give results "equal" or "Not Equal". 

**Formula:**
$N = \text{number of digit}$
* **equal:** $ZXCV = Z^N + X^N + C^N + V^N$
* **not equal:** $ZXCV \ne Z^N + X^N + C^N + V^N$

**Example:**
* Input=371 -> Output: Equal
* Input=372 -> Output: Not Equal

---

### 5) First Capital Letter
Write a code which should perform the following operations. User should enter a string without space and code should find the first capital letter in the string. You have to write a function which finds the letter recursively.

* **Input:** computer ScienceAndEnginnering
* **Output:** S

---

### General Rules
1.  Obey and don't broke the function prototypes that are shown on each part, if any, otherwise, you will get zero from the related part.
2.  You can use the functions that I wrote.
3.  Note that if any part of your program is not working as expected, then you can get zero from the related part, even it's working in some way.
4.  Upload your .c file on to Moodle to deliver your homework.
5.  You can ask any question about the homework via Moodle Forum. Corresponding TA: ferdaabbasoglu@gtu.edu.tr