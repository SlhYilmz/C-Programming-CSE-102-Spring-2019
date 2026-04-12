#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void draw_baklava_shape(){
	int height;
	int i, j;
	
	printf("\nWrite the height of the baklava: ");
	scanf("%d", &height);
	
	while(height==0 || height<0){
		printf("You can't draw a baklava with this length value. Try again with a proper one: ");
		scanf("%d", &height);
	}
	
	if(height>0){
		printf("\n");
		for(i=1 ; i<=height ; i++){
			for(j=i; j<height ; j++){
				printf(" ");
			}
			printf("/");
			
			
			for(j=2; j<=(i*2)-1 ; j++){
				printf("*");
			}	
			printf("\\\n");
		}
		
		for(i=height ; i>=1 ; i--){
			for(j=i; j<height ; j++){
				printf(" ");
			}
			printf("\\");
		
			for(j=2; j<=(i*2)-1 ; j++){
				printf("*");
			}	
			printf("/\n");
		}	
	}	
}

int main(){
draw_baklava_shape();
	
return 0;
}
