#include <stdio.h>
#include <math.h>

int capital_string(char *arr){
	
	if(arr[0] > 'A' && arr[0] < 'Z'){
		printf("%c", arr[0]);
	}
	else{
		return capital_string(arr+1);
	}

}


int main(){
	
	char array[200];
	
	printf("Write a string of characters:\n");
	scanf("%s", &array);

	capital_string(array);
	
//	printf("%s", array);
		
return 0;
}
