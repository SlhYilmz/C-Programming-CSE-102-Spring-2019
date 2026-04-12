#include <stdio.h>


void pretty_print(int grid[][9]);
int is_valid_row(int grid[][9], int row);
int is_valid(int grid[][9]);
int is_valid_column(int grid[][9], int col);
int is_valid_block(int grid[][9], int r, int c);

void read_a_solution(int grid [][9], char * file_name);
void print_board(int grid[][9]);
void test_game(char * file_name);


int main() {
	test_game("game001.txt");
	test_game("game002.txt");
}


void pretty_print(int grid[][9]) {
	/* complete this */
}


int is_valid_row(int grid[][9], int row) {
	/* complete this */
}


int is_valid_column(int grid[][9], int col) {
	/* complete this */
}


int is_valid_block(int grid[][9], int r, int c) {
	/* complete this */
}


int is_valid(int grid[][9]) {
	/* complete this */
}


void read_a_solution(int grid [][9], char * file_name) {
	FILE * fin;
    int i, j;

	fin = fopen(file_name, "rt");
	if (fin==NULL) {
		printf("Cannot open file %s for reading the game...\n", file_name);
	}
	else {
	    for (i = 0; i < 9; i++)
	        for (j = 0; j < 9; j++)
	            fscanf(fin, "%d", &grid[i][j]);
	}
}


void print_board(int grid[][9]) {
    int i, j;

	for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("%d ", grid[i][j]);
		}
		printf("\n");
	}
}


void test_game(char * file_name) {
    int grid[9][9];
	printf("Testing game in %s.............................\n", file_name);
    read_a_solution(grid, file_name);
	pretty_print(grid);
	print_board(grid);
    if (is_valid(grid))
       printf("Valid solution\n");
    else
		printf("Invalid solution\n");
}
