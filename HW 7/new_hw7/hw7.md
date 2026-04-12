# CSE102 - Computer Programming: Homework #7

## 1. Introduction
In this assignment, you are asked to develop a well-known board game named **Monopoly**. 

Monopoly is a real-estate board game for two players, in which the goal is to remain financially solvent while forcing opponents into bankruptcy by buying and developing pieces of property. 

### Board Mechanics
* The square board is divided into 6 equal divisions per side, forming 20 small rectangles representing properties, punishments, and taxes.
* At the start, each player is given a fixed amount of money.
* Players move around the board by throwing a dice.
* Unowned property can be bought; owned property requires rent payment to the owner.
* The game continues until a player goes bankrupt. Bankruptcy results in elimination. The last player remaining wins.

### Core Rules
* The game is played by two users, both controlled by a person.
* Players start from the **Start** block.
* Each player rolls one dice per turn.
* Upon arriving at an unowned property, the user can buy it and construct up to 3 houses.
* Houses can only be built when a player lands on their own property.
* Rent changes according to the number of houses constructed.
* Tax blocks require paying a tax fee.
* Punishment blocks (e.g., "Wait 2 turns") prevent the user from rolling the dice for a specified number of opponent turns.
* If a user cannot pay rent/tax, they must sell properties. If they still cannot pay after selling everything, they lose.
* Passing through the **Start** block rewards the player with $10,000.

---

## 2. Data Structures
You are strongly expected to use the following structures:

### `struct player`
* `player_type type`: Enumerated type (`noone`, `cap`, `car`).
* `int current_block_id`: Player location as block id.
* `int owned_block_ids[11]`: IDs of properties owned by the user.
* `int account`: Current money.
* `int turn_to_wait`: Number of punishment turns remaining.
* `char * name`: Player name.

### `struct block`
* `int block_id`: ID of the block.
* `char * name`: Text shown on the top of the block.
* `int price`: Price of property, tax fee, or number of punishment turns.
* `int rent`: Default rent (no houses).
* `int rent_1`: Rent with one house.
* `int rent_2`: Rent with two houses.
* `int rent_3`: Rent with three houses.
* `int house_price`: Price of building a house.
* `int house_count`: Number of houses currently built.
* `struct player owner`: The owner of the block.
* `block_type type`: Enumerated type (`start`, `property`, `tax`, `punish`).

---

## 3. Assignment Parts

### Part 1: Board Initialization [10pts]
Write a function that initializes the board with blocks using information from `blocks.xlsx`. Do not read the file programmatically; manually prepare the board data based on the Excel file.
```c
void init_the_board(struct block board[20]);
```

### Part 2: Show Board [20pts]
Write a function that prints the board. Each block consists of three lines: text/name, price, and current players.
```c
void show_board(struct block board[20], struct player player_one, struct player player_two);
```

### Part 3: Show Property Deeds [10pts]
Write a function that lists properties and allows the user to select one to see its detailed deed (Rent, Rent 1H, Rent 2H, Rent 3H, House Price).
```c
void show_properties(struct block board[20]);
```

### Part 4: Buy Property [15pts]
Write a function that allows a user to buy the property they are currently standing on. It must handle all checks (ownership, location, sufficient funds) and ask if they wish to build houses.
```c
void buy_property(struct block* current_block, struct player* current_player);
```

### Part 5: Sell Property [15pts]
Write a function that allows a user to sell owned properties back to the bank for half the original price (including houses).
```c
void sell_property(struct block board[20], struct player* current_player);
```

### Part 6: Gameplay [40pts]
Write the main game loop that facilitates the two-player game. It should include a menu for each turn:
1. Roll the dice
2. Show my account
3. Show my properties
4. Show property deeds
5. Buy Property
6. Buy house
7. Sell property

```c
void gameplay(struct block board[20], struct player player_one, struct player player_two);
```

---

## 4. General Rules
1. Obey the function prototypes exactly.
2. The program must be developed on Linux and compiled with **gcc**.