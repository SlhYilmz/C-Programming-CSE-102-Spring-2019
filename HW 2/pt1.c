#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void menu ();


int main(){
	menu ();
	
return 0;
}

void menu (){
	
	int choice;
	
	do{	
		printf("\n***** MENU *****\n");
		printf("1. Play Lucky Number\n");
		printf("2. Draw hourglass\n");
		printf("3. Draw mountain road\n");
		printf("4. Exit\n");
			
		printf("\nChoice: ");
		scanf("%d", &choice);
	//	printf("\n");
		
			
		switch(choice){
			case 1:{
				printf("Lucky Number\n");
				break;
			}
				
			case 2:{
				printf("Draw hourglass\n");
			//	draw_hourglass (int height);
				break;
			}
	
			case 3:{
				printf("Draw mountain road\n");
			//	draw_mountain_road (int length, int max_radius)
				break;
			}
			
			case 4:{
				break;
				
			}
			default:{
				printf("Unsupported value\n");
				break;
			}
		}	
		
	}while(choice!=4);
		
}
	
	
	
	

