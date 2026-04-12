#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18


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
	while(*ch_iter != '\n') {
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

char randomCharacterCreator(){

    char character = 'a' + (rand() % 26);
    return character;
}

void place_characters_to_grid(char *dict[], int coord[DICT_SIZE][4],char gridLetters[][DICT_SIZE]){
	
	int i, j;
	int y_coor, x_coor;
	
	
    for(i=0 ; i < DICT_SIZE ; i++){
        for(j=0 ; j < DICT_SIZE ; j++){
			gridLetters[i][j] = ' ';//randomCharacterCreator();
        }
    }

	
    for(i=0 ; i < 15 ; i++){
    	
    	y_coor = coord[i][2] - coord [i][0];
    	x_coor = coord[i][3] - coord [i][1];
    	
    	if(x_coor!=0 && y_coor==0){
    		for(j=0 ; j<=x_coor ; j++){
    			gridLetters[coord[i][0] ][ coord[i][1]+j] = dict[i][j];
			}
			
		}
		else if(x_coor==0 && y_coor!=0){
    		for(j=0 ; j<=y_coor ; j++){
    			gridLetters[coord[i][0] + j][coord[i][1]] = dict[i][j];
			}
		}
		else if(x_coor!=0 && y_coor!=0){
    		for(j=0 ; j<=x_coor ; j++){
    			gridLetters[coord[i][0] +j ][ coord[i][1]+j] = dict[i][j];
			}
		}
		
	}

}

void print_grid(char gridLetters[][DICT_SIZE]){
	
	int i, j;
	
    for(i=0 ; i < DICT_SIZE ; i++){
        for(j=0 ; j < DICT_SIZE ; j++){
            printf("%c ",gridLetters[i][j]);
        }
    	printf("\n");
    }

}


void word_compare(char gridLetters[][DICT_SIZE], int coord[DICT_SIZE][4]){
	
	char word[100];
	int column, row;
	
	do{
		printf("Enter the word: ");
		scanf("%s", &word);
		printf("\nEnter the coordinates: ");
		scanf("%d %d", &column, &row);
		
	}while(column!=0);
	int i, j, k ;
	for(i=0 ; i<DICT_SIZE ; i++){
		for(j=0 ; j< DICT_SIZE ; j++){
			
			if(coord[i][0]==i && coord[i][1]==j){
				for(k=0 ; word[k] != '\0'; k++){
					
					
					
				}
				
			}
			
		}
		
	}
	
	
}


int main(){
	
	char *dict[DICT_SIZE]; // 0- kelimeler 1 ,2,3
    int coord[DICT_SIZE][4];    // 0 - serum numarasý, (x1, y1, x2, y2)
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

	
	char gridLetters[DICT_SIZE][DICT_SIZE];
	
	print_dictionary(dict);
	
	place_characters_to_grid(dict, coord, gridLetters);
	print_grid(gridLetters);
	game();
	
	return 0;
}






