#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void draw_mountain_road (int length, int max_radius);

int random_number_generator(int lower_bound, int upper_bound){
	
	int luckyNumber;
	
	
	srand(time(NULL));
	luckyNumber = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
	
	return luckyNumber;
}

int main(){
	
	int length, max_radius;
	
	draw_mountain_road (length, max_radius);
	
return 0;
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
	printf("%d\n", radius);
	
	for(count=1 ; count<=length ; count++){
		
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
		/*
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
		}	*/
					
	}	
	
	



			
			

			
}
