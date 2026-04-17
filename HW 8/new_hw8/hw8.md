# CSE102 Computer Programming - Homework #8

**Spring 2019** **Due Date:** 05/05/2019  
**Hand in:** A student with number 20180000001 should hand in a file named `20180000001.c`.

---

## The Monopoly 2

In this homework, you are going to enhance the Monopoly game that you implemented in the previous homework. The following features will be added:

- Playing Against Computer
- Board Implementation
- Fortune Cards

---

## Gameplay Rules for Computer

_Unless it is told, actions are the same as user actions defined in the previous homework (hw7)._

- **Dice Rolling:** When played against the computer, it rolls a dice just like a user. Dice rolling result for the computer must be printed as: `"Computer rolled the dice: N"`.
- **Unowned Property:** If computer arrives at an unowned property, it decides what to do
  based on the followings:
  _ If the price of the property is below the average cost of all properties, then computer **must** buy the property.
  _ Otherwise, the computer rolls the dice again. If the outcome is between 1 and 3, then the computer must buy the property. If the roll is between 4 and 6, the computer skips its turn.
- **Owned Property (Houses):** If the computer lands on a property it owns, it may construct up to 3 houses on that property. The number of houses it can built depends on the number of properties it owns:
  - If the computer owns **1/3 of all the properties**, it rolls a dice. If the result is between 1 and 3, then the computer constructs a house. Otherwise, it skips the current turn.
  - If computer does not have 1/3 of all his properties, it skips its turn.
- **Bankruptcy/Debt:** When computer does not have enough money to pay its rent/tax, then the bank asks it to sell some of its properties. The computer must sell starting with the highest priced property till it pays off its debt.
- **Player Type:** The Player_type for the computer is `"cap"`. Update your implementation accordingly.

---

## Board Implementation

- **Linked List:** You must convert your array-based board implementation to a linked list..
- **Expansion:** There are 4 more blocks added to the board. The total number of blocks on the board now is 24.

---

## Fortune Cards:

- Whenever a player lands on a fortune card block, player draws a card from fortune card deck (you randomly pick a fortune card). It carries out the action the card says.
- Location of fortune card blocks on board are defined in the `blocks2.csv` file.
- Block type is "fortune". You must update your block_type enumeration implementation accordingly.
- Define a struct with name `fortune_card`. Rest of the implementation is up to you.
- Fortune cards are defined below.

| Card No | Fortune Card Name | Explanation                                                                 |
| :------ | :---------------- | :-------------------------------------------------------------------------- |
| 1       | Free House        | Build a house on one of your properties for free.                           |
| 2       | Time Travel       | Roll a dice. If [1-3], move forward 2 blocks. Else, move backward 2 blocks. |
| 3       | Garnishment       | Pay 5.000 to the bank.                                                      |
| 4       | Generosity        | Give 10.000 to the opponent.                                                |
| 5       | Treasure Hunter   | Take 20.000 from the bank.                                                  |

---

## General Rules

1.  **Function Prototypes:** Do not modify given prototypes; doing so results in zero credit.
2.  **Partial Functionality:** Parts of the program not working as expected may receive zero credit even if partially functional.

**Corresponding TA:** M. Rasih ÇELENLİOĞLU (mcelenlioglu@gtu.edu.tr)
