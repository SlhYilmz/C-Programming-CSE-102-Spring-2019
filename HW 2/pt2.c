#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int random_random_generator(int lower_bound, int upper_bound){
	
	int luckyNumber;
	
	
	srand(time(NULL));
	luckyNumber = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
	
	return luckyNumber;
}

int make_a_guess (int trial, int min, int max){
	int computerWinNumber=0;
	int humanWinNumber=0;
	
	trial=10;
	min=1;
	max=1024;
	int guess;
	
	int distance;
	int upperBound=1024 , lowerBound=1;
	
	// #define upperBound 1024
	// #define lowerBound 1
	// #define trial 10
	// UNUTMA
	int luckyNumber = random_random_generator(lowerBound, upperBound);
	
		
	printf("Lucky number: %d\n", luckyNumber);
	printf("\n");
	
	
	do{
		printf("(Trial: %d) ", trial);
		printf("Make a guess between %d and %d: ", min, max);
		scanf("%d", &guess);
		
		if ( guess>max || guess<min ){
			printf("Value not in the interval. Try Again.\n\n");
			distance=1;	//for the loop to go again.
			continue;
			
		}
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
			
		//	printf("%d\n", distance);

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
		}		
		
	}while(distance!=0 && trial!=0);
	
	if (trial==0){
		computerWinNumber++;
		show_scores(humanWinNumber, computerWinNumber);
	}
	else if (trial!=0){
		humanWinNumber++;
		show_scores(humanWinNumber, computerWinNumber);
		
	}
	
	
	
	
	
}


void show_scores(int score_human, int score_program){
	printf("Your Score: %d, Computer Score: %d", score_human, score_program);
}


int main(){

	int trial, min, max;
	make_a_guess(trial, min, max);
	
return 0;
}
