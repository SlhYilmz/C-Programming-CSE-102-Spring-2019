#include <stdio.h>
 
int main() {
	
    int space, rows, star=0;
    printf("Enter the number of rows for pyramid\n");
    scanf("%d",&rows);
    
	int i;
	 
    for(i = 1; i <= rows; i++) {
	
        for(space = 1; space <= rows-(i); space++) { //Boþluk basýyor
			if(space == 1 && i == 1)
				continue;
			else
				printf("     ");
        }
	
	if(i == 1)
		printf("   ");
        
	    while(star != (2*i - 1)) { // 2*i-1 formülüyle piramit þekli basma 
	
			if(star == 0 || star == 2*i-2){ //ilk ve son yýldýz için kontrol		
				printf("*");
	        }
			else{

	        		printf("     ");
			}
	    	star++;
	    }
	    star=0;
	    printf("\n");
    }
     

  int space2, star2;
  
  //bu alt kýsým üstün tam tersi, þimdilik bloke ettim ki önce bi üstü tamamlayayým
  
   /*for(i = rows-1 ; i >= 1 ; i--) { //Tam tersi 
    
        for(space2 = 0; space2 <= rows-i; space2++) { //Printing spaces
           printf("\t");
        }
       
        while(star2 != (2*i - 1)) { 
			if(star2 == 0 || star2==2*i-2){ 
	            printf("x");
	        }
			else{
	        	printf("\t");
			} 
        star2++;
        }
        star2 = 0; 
        printf("\n");
    }*/
    return 0;
}
