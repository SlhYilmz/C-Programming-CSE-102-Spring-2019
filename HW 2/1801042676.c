#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define computerWin 1
#define humanWin 2

void menu ();
int random_number_generator(int lower_bound, int upper_bound);
int make_a_guess (int trial, int min, int max);
void show_scores(int score_human, int score_program);
void draw_hourglass (int height);
void draw_mountain_road (int length, int max_radius);

int main (){
	menu();
return 0;	
}

void menu (){
	int choice;
	int computerWinCounter=0, humanWinCounter=0, result;
	
	do{	
		printf("\n***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw hourglass\n");
		printf("3. Draw mountain road\n");
		printf("4. Exit\n");
			
		printf("\nChoice: ");
		scanf(" %d", &choice);
			
		switch(choice){
			case 1:{
				
				int trial, min, max;
				
				result = make_a_guess(trial, min, max);	//This function returns the winner of the game. So that I can use while storing the data.
				
					if (result == computerWin){
						computerWinCounter++;
					}
					else if (result == humanWin){
						humanWinCounter++;
					}
					
					show_scores(humanWinCounter, computerWinCounter);	//Prints the (stored) winner of the game.
				
				break;
			}
				
			case 2:{
				int height;
				
				draw_hourglass (height);
				break;
			}
	
			case 3:{
				int length, max_radius;
				draw_mountain_road(length, max_radius);
			
				break;
			}
			
			case 4:{
				break;
				
			}
			default:{
				printf("Unsupported value. Try again.\n");
				break;
			}
		}	
		
	}while(choice!=4);
		
}

//Just a standart random number generator, so we can call it in other functions.
int random_number_generator(int lower_bound, int upper_bound){
	
	int randomNumber;
	
	srand(time(NULL));
	randomNumber = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
	
	return randomNumber;
}

int make_a_guess (int trial, int min, int max){
		
	trial=10;	//Trial is predefined here. You can change it to any positive value you want.
	min=1;		//Min and max values are also predefined, as it says in the homework.
	max=1024;
	int guess;

	int distance;
	int upperBound=max , lowerBound=min;
	
	int luckyNumber = random_number_generator(lowerBound, upperBound);	//This gets a random number as the Lucky Number.
		
//	printf("Lucky number: %d\n", luckyNumber);	//This is for seeing what the lucky number is.
	printf("\n");
	
//This do-while loop gets the value from the user until it is right, or number of trials are finished.	
	do{
		printf("(Trial: %d) ", trial);
		printf("Make a guess between %d and %d: ", min, max);
		scanf("%d", &guess);
		
		//This if statement controls whether the written number is in the interval or not. If it is not, then it goes back to the loop with continue statement.
		if ( guess>max || guess<min ){
			printf("Value not in the interval. Try Again.\n\n");
			distance=1;	//I set the distance to something else other than '0', so the loop can continue.
			continue;
			
		}
		//This else part changes the max or min values according to the values that user entered.
		else{
			if(luckyNumber>guess){
				min = guess;
				distance = abs(luckyNumber-min);
			}	
			else if(luckyNumber<guess){
				max=guess;
				distance = abs(luckyNumber-max);
				
			}
			else if(luckyNumber==guess){
				printf("You win!\n");
				break;
			}
 
		}		
			
			//These if's check the distance and lowers the trial number by 1 at a time.
			if(distance>=512 && distance<1024){
				printf("Distance is 10\n\n");
				trial--;
			}
			else if (distance>=256 && distance<511){
				printf("Distance is 9\n\n");
				trial--;
			}
			else if (distance>=128 && distance<255){
				printf("Distance is 8\n\n");
				trial--;
			} 
			else if (distance>=64 && distance<127){
				printf("Distance is 7\n\n");
				trial--;
			}
			else if (distance>=32 && distance<63){
				printf("Distance is 6\n\n");
				trial--;
			} 
			else if (distance>=16 && distance<31){
				printf("Distance is 5\n\n");
				trial--;
			} 
			else if (distance>=8 && distance<15){
				printf("Distance is 4\n\n");
				trial--;
			} 
			else if (distance>=4 && distance<7){
				printf("Distance is 3\n\n");
				trial--;
			} 
			else if (distance>=2 && distance<3){
				printf("Distance is 2\n\n");
				trial--;
			} 
			else if (distance==1){
				printf("Distance is 1\n\n");
				trial--;
			} 
			else if (distance==0){
				printf("Distance is 0\n\n");
				trial--;
			}
			
	}while(distance!=0 && trial!=0);
	
	//when there is no more trial left, you lose. So this 'if' returns a value of which we calculate the number of wins whether it is user or the computer.
	//We use this returned value in the menu, with 'show_scores' function.
	if (trial==0){
		printf("You lost!\n");
		return computerWin;
	}
	else if (trial!=0){
		return humanWin;
	}
	
}

//Using the values that we obtained from 'make_a_guess' function and the menu, this function prints those said values.
void show_scores(int score_human, int score_program){
	printf("Your Score: %d, Computer Score: %d\n", score_human, score_program);
}

void draw_hourglass (int height){
	
	int i, j;
	printf("Enter and odd number for height: ");
	scanf("%d", &height);
	
	while(height%2==0){
		printf("You've entered an even number. Please enter an odd number: ");
		scanf("%d", &height);
	}
	if(height%2==1){
		
		for(i=height/2+1; i>=1; i--){
		
			for(j=i ; j<height-j ; j++){	//I substracted 'j' from the height, so that hourglass is aligned to the left. 	
			    printf(" ");
			}
			
			for(j= 1; j<=(2*i-1) ; j++){
			    printf("*");
			}
			
			printf("\n");		//After incrementing 'i', we need to go one line down. This is for that.
		}

		for(i=2; i<=height/2+1; i++){	//I start with 2 instead of 1, because there has to be only one star in the middle.
			
			for(j=i ; j<height-j ; j++){
			    printf(" ");
			}
			
			for(j=1 ; j<=(2*i-1) ; j++){
			    printf("*");
			}
			printf("\n");
		}	
	}
}

void draw_mountain_road (int length, int max_radius){

	int radius;	
	int lowBound=0;
	int count, i, j;
	
	printf("Enter max radius for mountains: ");
	scanf("%d", &max_radius);
	
	printf("Enter length for mountains: ");
	scanf("%d", &length);
	
	radius = random_number_generator(lowBound, max_radius);
//	printf("%d\n", radius);
	
	for(count=1 ; count<=length ; count++){
		
		//This if starts the road in the way wanted, by checking if it is odd or not.
		if(count%2==1){
			for(i=1; i<=radius; i++){
				for(j=i ; j<radius ; j++){
				    printf(" ");
				}
				printf("/");
				printf("\n");
			}
			
			printf("|\n");
			
			for(i=radius; i>=1; i--){
				for(j=i ; j<radius ; j++){
				    printf(" ");
				}
				printf("\\");
				printf("\n");
			}
			continue;			
		}
		
		else if(count%2==0){
			for(i=radius; i>=1; i--){
				for(j=i ; j<radius ; j++){
				    printf(" ");
				}
				printf("\\");
				printf("\n");
			}
			for(i=1 ; i<=radius; i++){
				printf(" ");
				}
				
			printf("|\n");
				
			for(i=1; i<=radius; i++){
				for(j=i ; j<radius ; j++){
				    printf(" ");
				}
				printf("/");
				printf("\n");
			}
		}	
					
	}	
	
}	

