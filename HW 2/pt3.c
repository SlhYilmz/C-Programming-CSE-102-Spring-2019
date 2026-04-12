#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void draw_hourglass (int height);


int main(){
	
	int height;
	
	draw_hourglass (height);
	
return 0;
}


void draw_hourglass (int height){
	
	int i, j;
	printf("Enter Odd value for height: ");
	scanf("%d", &height);
	

		
		while(height%2==0){
			printf("You've entered an even number. Please enter an odd number: ");
			scanf("%d", &height);
			
		}
		if(height%2==1){
		
			for(i=height/2+1; i>=1; i--){
			
				for(j=i ; j<height-j ; j++){
				    printf(" ");
				}
				
				for(j= 1; j<=(2*i-1) ; j++){
				    printf("*");
				}
				
				printf("\n");
			}
	
	
			for(i=2; i<=height/2+1; i++){
				
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
	
	
	
	

