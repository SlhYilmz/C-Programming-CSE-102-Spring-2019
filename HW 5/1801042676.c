#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18
#define NUMBER_OF_WORDS 15


/*
	I couldn't do all the things wanted, so there are some unfinished parts in this code. 
	For instance it can't find the words if they're in reversed order, or you put the end points (x2,y2) as the chosen coordinates.
	But it can find and make them Uppercase if thry are in the right order.
 */
int get_line_size(char *line);
void copy_string(char *source, char *destination);
void remove_newline(char *line);
void print_dictionary(char *dict[]);
void print_coord(int coord[DICT_SIZE][4]);
char randomCharacterCreator();
void place_characters_to_grid(char *dict[], int coord[DICT_SIZE][4],char gridLetters[][DICT_SIZE]);
void print_grid(char gridLetters[][DICT_SIZE] );
void word_compare (char gridLetters[][DICT_SIZE], int coord[DICT_SIZE][4], char *dict[] );

int main(){
	
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	while(fgets(line, LINE_LEN, fp) != NULL) {
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
//	print_dictionary(dict);
//	print_coord(coord);
	
	
	char gridLetters[DICT_SIZE][DICT_SIZE];
	
	place_characters_to_grid(dict, coord, gridLetters);
	print_grid(gridLetters);
	word_compare(gridLetters,coord, dict);
	
	return 0;
}

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
    char *ch_iter = line;
    // go until you see new line
    while(*ch_iter != '\n' && *ch_iter != 13) {
        ch_iter++; // next char
    }
    *ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

/**************************************/

//Creates a random letter.
char randomCharacterCreator(){

    char character = 'a' + (rand() % 26);
    return character;
}


void place_characters_to_grid(char *dict[], int coord[DICT_SIZE][4], char gridLetters[][DICT_SIZE]){
	
	int i, j;
	int y_coor, x_coor;
	
	
    for(i=0 ; i < DICT_SIZE ; i++){
        for(j=0 ; j < DICT_SIZE ; j++){
			gridLetters[i][j] =  randomCharacterCreator();
        }
    }

	
    for(i=0 ; i < 15 ; i++){
    	
    	y_coor = coord[i][2] - coord [i][0];			/*By substracting the y values, we can control where the word sits in the grid.*/
    	x_coor = coord[i][3] - coord [i][1];			
    	
    	//horizontal							
    	if(x_coor!=0 && y_coor==0){				/*If there is no change in y-axis, it has to be horizontal. You put what exists in the dict array to the gridLetters, so that you can use it elsewhere.*/
    		for(j=0 ; j<=x_coor ; j++){
    			gridLetters[coord[i][0] ][ coord[i][1]+j] = dict[i][j];
			}
			
		}
		//vertical		
		else if(x_coor==0 && y_coor!=0){		/*If there is no change in x-axis, it has to be vertical.*/
    		for(j=0 ; j<=y_coor ; j++){
    			gridLetters[coord[i][0] + j][coord[i][1]] = dict[i][j];
			}
		}
		//diagonal
		else if(x_coor!=0 && y_coor!=0){			/*If there is a change in x-axis and y-axis, it has to be diagonal.*/
    		for(j=0 ; j<=x_coor ; j++){
    			gridLetters[coord[i][0] + j ][ coord[i][1] + j] = dict[i][j];
			}
		}
		
	}

}

void print_grid(char gridLetters[][DICT_SIZE] ){
	
	int i, j;
	
    for(i=0 ; i < DICT_SIZE ; i++){
        for(j=0 ; j < DICT_SIZE ; j++){
            printf("%c ",gridLetters[i][j]);
        }
    	printf("\n");
    }

}


void word_compare (char gridLetters[][DICT_SIZE], int coord[DICT_SIZE][4], char *dict[] ) {
	
	int i, j, k;
	char word[100];
	char exit[10]={"exit game"};
	int column, row;
	int count=0;
	int exitFlag=0;
	
	
	do{
	
		printf("Enter the word: ");
		scanf("%s", word);
		printf("\nEnter the coordinates: ");
		scanf("%d %d", &row, &column);

	
		for(i=0 ; i<DICT_SIZE ; i++){
		
			//from left to right (in the way of number 6 in numerical numbers)
			if(coord[i][0]==row && coord[i][1]==column && coord[i][1]!=coord[i][3] && coord[i][0]==coord[i][2]){
				
				for(k=0 ; word[k] != '\0'; k++){
					
					if(word[k]==dict[i][k]){
					
						gridLetters[ coord[i][0] ][ coord[i][1]+k ]=dict[i][k]-32;
						count++;	
					}
				
				}
					
			}
						
			//from top to bottom (in the way of number 2 in numerical numbers)
			else if(coord[i][0]==row && coord[i][1]==column && coord[i][0]!=coord[i][2] && coord[i][1]==coord[i][3]) {
				
				for(k=0 ; word[k] != '\0'; k++){
					
					if(word[k]==dict[i][k]){
						
						gridLetters[coord[i][0]+k ][ coord[i][1]]=dict[i][k]-32;
						count++;	
						
					}
				
				}
					
			}
			//diagonal (in the way of number 3 in numerical numbers)
			else if(coord[i][0]==row && coord[i][1]==column && coord[i][1]!=coord[i][3] && coord[i][0]!=coord[i][2]){
				
				for(k=0 ; word[k] != '\0'; k++){
					
					if(word[k]==dict[i][k]){
						
						gridLetters[ coord[i][0]+k ][ coord[i][1]+k ]=dict[i][k]-32;
						count++;	
						
					}
				
				}
					
			}
		
		}
	
		print_grid(gridLetters);
	
	}while(count!=NUMBER_OF_WORDS);
}

