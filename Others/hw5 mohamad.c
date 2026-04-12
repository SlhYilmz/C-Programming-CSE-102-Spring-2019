#include<stdio.h>
#include<stdlib.h>

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
	while(*ch_iter != '\n' && *ch_iter != 13 ) {
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

void string_len(int length[15][2],int coord[DICT_SIZE][4]){
    int i;
    for(i=0;i<15;i++){
        length[i][0]=coord[i][2]-coord[i][0];
        length[i][1]=coord[i][3]-coord[i][1];
    }
    return;
}
void print_rand(char letters[15][15]){
    int i,j;
    for(i=0;i<DICT_SIZE;i++){
        for(j=0;j<DICT_SIZE;j++){
            letters[i][j]=(rand()%(123-97))+97;
        }
    }
}

void get_words(char *dict[], int coord[DICT_SIZE][4],char letters[15][15], int length[15][2]){
    int i,j;
        print_rand(letters);
     for(i=0;i<DICT_SIZE;i++){
        if(length[i][0]!=0 && length[i][1]==0){
            for(j=0;j<=length[i][0];j++){
                letters[coord[i][0]][coord[i][1]+j]=dict[i][j];
            }
        }
        else if(length[i][0]==0 && length[i][1]!=0){
            for(j=0;j<=length[i][0];j++){
                letters[coord[i][0]+j][coord[i][1]]=dict[i][j];
            }
        }
        else if(length[i][0]!=0 && length[i][1]!=0){
            for(j=0;j<=length[i][0];j++){
                letters[coord[i][0]+j][coord[i][1]+j]=dict[i][j];
            }
        }
     }
}


void print_puzzle(char letters[15][15]){
    int i,j;
        for(i=0;i<15;i++){
            for(j=0;j<0;j++){
                printf("%c",letters[i][j]);
            }
            printf("\n");
        }
}

void compare_strings(char *dict[DICT_SIZE],int coord[DICT_SIZE][4],char letters[15][15], int length[15][2]){
    char guess[20];
    char exit[20]={"exit game"};
    int flag=0, x,y,j,i,k=0,counter=0;

    printf("enter the word you guessed or type exit game to exit: ");
    scanf("%s",guess);
    for(i=0;guess[i]!=0;i++){
        if(exit[i]==guess[i]){
            counter++;
        }
    }
    if(counter>=9){
        printf("\n\nthank you for playing!!!\n\n");
        return;
    }
    else{
        printf("enter coordinates of the word: ");
        scanf("%d %d",&x,&y);

        for(i=0;i<15;i++){
            if(coord[i][0]==x && coord[i][1]==y && coord[i][1]!= coord[i][3]){
                for(j=0;guess!=0;j++){
                    letters[x][y+j]=dict[i][j]-32;
                }
            }
            else if(coord[i][0]==x && coord[i][1]==y && coord[i][0]!= coord[i][2]){
                for(j=0;guess[j]!=0;j++){
                    if(guess[j] == dict[i][j]){
                        letters[x+j][y]=dict[i][j]-32;
                    }
                }
            }
            else if(coord[i][0]==x && coord[i][1]==y && coord[i][1]!= coord[i][3] && coord[i][0]!=coord[i][2]){
                for(j=0;guess!=0;j++){
                    if(guess[j] == dict[i][j]){
                        letters[x+j][y+j]=dict[i][j]-32;
                    }
                }
            }
            else if(coord[i][2]==x && coord[i][3]==y && coord[i][1]!= coord[i][3]){
                for(j=length[i][1];j>=0;j--){
                    if(guess[j] == dict[i][j]){
                        letters[x][y-k]=dict[i][j]-32;
                        k++;
                    }
                }
                k=0;
            }
            else if(coord[i][2]==x && coord[i][3]==y && coord[i][0]!= coord[i][2]){
                for(j=length[i][1];j>=0;j--){
                    if(guess[j] == dict[i][j]){
                        letters[x-k][y]=dict[i][j]-32;
                        k++;
                    }
                }
                k=0;
            }
            else if(coord[i][2]==x && coord[i][3]==y && coord[i][0]!= coord[i][2] && coord[i][1]!= coord[i][3]){
                for(j=length[i][1];j>=0;j--){
                    if(guess[j] == dict[i][j]){
                        letters[x-k][y-k]=dict[i][j]-32;
                        k++;
                    }
                }
            }
        }
        print_puzzle(letters);
        for(i=0;i<15;i++){
            for(j=0;j<15;j++){
                if(letters[i][j]<123 && letters[i][j]>97){
                    flag=1;
                }
            }
        }
        if(flag==1){
            return compare_strings(dict,coord,letters,length);
        }
        else{
            return;
        }
    }
}
int main(){
    char letters[15][15];
    int length[15][2];
	char *dict[DICT_SIZE];
    int i,j,m=0,flag=0,coord[DICT_SIZE][4];
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
	//print_coord(coord);
	//print_dictionary(dict);
    string_len(length,coord);
    get_words(dict,coord,letters,length);
    print_puzzle(letters);
	compare_strings(dict, coord, letters, length);
    printf("thank you for playing\n\n");

	// WRITE HERE...

	return 0;
}






