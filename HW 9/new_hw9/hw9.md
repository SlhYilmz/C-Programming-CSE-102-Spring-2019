# CSE102-Spring 2019

## CSE102 - Computer Programming

### Homework #9

**Due Date:** 16/05/2019
**Hand in:** A student with number 20180000001 should hand in a file named `20180000001.c` for this homework and compress it into a `.zip` file.

---

### Introduction

In this homework, you must create a music stack list which has **The Turkish Five**. The Turkish Five is a name used to identify five pioneers of western classical music in Turkey. The Turkish Five composers are listed below in the table.

| Name (char[]) | Surname (char[]) | Musical_Work (char[]) | Age (int) |
| :------------ | :--------------- | :-------------------- | :-------- |
| Cemal Reşit   | Rey              | Lüküs Hayat           | 80        |
| Ahmed Adnan   | Saygun           | Yunus Emre            | 83        |
| Ulvi Cemal    | Erkin            | Keloğlan              | 66        |
| Hasan Ferit   | Alnar            | Sarı Zeybek           | 72        |
| Necil Kazım   | Akses            | İkinci Senfoni        | 90        |

---

### Data Structures

Create a stack that is implemented with a linked list. You must define `struct person` like:

```c
struct person {
    char name[];
    char surname[];
    char musical_Work[];
    int age;
    struct person *next;
} *top;
```

---

### Menu Operations

In your program, you have to create a menu which has the following operations:

#### 1. Add a Person to the Stack

Take person's information with `scanf`, create a node, and add the node to the stack using the function:
`addNode(char name[], char surname [], char creation [], int age)`

#### 2. Pop a Person from the Stack

Delete the last node of the stack. Create `deleteNode(...)` to pop a node.

#### 3. Sort in Alphabetical Order

Write a method `Sort_Alphabetically(...)` to order the names of the people in the stack alphabetically. Use the `print_stack(...)` method to show the sorted stack.

#### 4. Sort Age in Increasing Order

Write a method `Sort_Increasingly(...)` that sorts ages of people in the stack in increasing order. Use the `print_stack(...)` method to show the sorted stack.

#### 5. Exit menu

Quit menu.

---

### Example Output

_(User entered values are written in bold.)_

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Select your Choice: **1** \
Name: **Cemal Reşit** \
Surname: **Rey** \
Creation: **Lukus Hayat** \
Age: **80** 

1. Cemal Reşit \
   Rey \
   Lukus Hayat \
   80 

Select your Choice: **1** \
Name: **Ahmed Adnan** \
Surname: **Saygun** \
Creation: **Yunus Emre** \
Age: **83** 

1) Ahmed Adnan \
   Saygun \
   Yunus Emre \
   83 

2) Cemal Reşit \
   Rey \
   Lukus Hayat \
  80

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Name: **Ulvi Cemal** \
Surname: **Erkin** \
Creation: **Keloğlan** \
Age: **66**

1) Ulvi Cemal \
   Erkin \
   Keloğlan \
   66

2) Ahmed Adnan \
   Saygun \
   Yunus Emre \
   83

3) Cemal Reşit \
   Rey \
   Lukus Hayat \
   80

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Select your Choice: **1** \
Name: **Hasan Ferit** \
Surname: **Alnar** \
Creation: **Sarı Zeybek** \
Age: **72**


1) Hasan Ferit \
   Alnar \
   Sarı Zeybek \
   72

2) Ulvi Cemal \
   Erkin \
   Keloğlan \
   66

3) Ahmed Adnan \
   Saygun \
   Yunus Emre \
   83

4) Cemal Reşit \
   Rey \
   Lukus Hayat \
   80

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Select your Choice: **2** 

1) Ulvi Cemal \
   Erkin \
   Keloğlan \
   66

2) Ahmed Adnan \
   Saygun \
   Yunus Emre \
   83

3) Cemal Reşit \
   Rey \
   Lukus Hayat \
   80

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Select your Choice: **3**

Ahmed Adnan \
Saygun \
Yunus Emre \
83

Cemal Reşit \
Rey \
Lukus Hayat \
80

Ulvi Cemal \
Erkin \
Keloğlan \
66

************ MENU ************ \
1- Add a Person to the Stack \
2- Pop a Person from the Stack \
3- Sort Alphabetical Order \
4- Sort Age in Increasing Order \
5- Exit menu\
\********************************

Select your Choice: **4**

Ulvi Cemal \
Erkin \
Keloğlan \
66

Cemal Reşit \
Rey \
Lukus Hayat \
80

Ahmed Adnan \
Saygun \
Yunus Emre \
83

### General Rules

1. Unless otherwise noted, the given function prototypes should not be modified. If you do so, you will get zero credit for that part of the assignment.
2. Note that if any part of your program is not working as expected, then you can get zero credit for the related part, even it partially works for some cases.
3. Upload your `.c` file on to Moodle to deliver your homework.
4. You can ask any question about the homework via Moodle Forum. Please do not post answers and part of the answers. Those post revealing solutions to the entire or a part of the assignment will be treated as cheating.
5. Solutions including cheating will get -100. Cheating means that a solution is copied from another source (from the internet or another student) without substantial contribution of your own. Changing variable or function names or re-ordering portions of the code does not constitute as substantial work. In the case of copying between two submissions, there will be no distinction as to who the source is. They will both get -100.

Corresponding TA: M. Ferda ABBASOĞLU (ferdaabbasoglu@gtu.edu.tr) 