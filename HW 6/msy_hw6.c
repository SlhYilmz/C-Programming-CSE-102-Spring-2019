#include <stdio.h>

int menu();
/*The two functions below are to use for anywhere in the code, so that I don't have to write it again and again.*/
int recursive_pow(int base, int exponent);
int digit_finder(int number);


int common(int no1, int no2);			/*Part1*/
int merger_function (int array[], int lower, int middle, int higher); /*Part2*/
int merge_sort(int array[], int lower, int higher); /*Part2*/
int function_calculator (int number);	/*Part3*/
int equal_not_equal_recursive (int number, int numberOfDigits);	/*Part4's main function*/
void check_number_equality(int number);							/*Part4's Print Function*/
int capital_string(char *arr);			/*Part5*/



int main(){
	
	menu();
	
return 0;
}

int menu(){
	
	int choice, i;
	int firstNumber, secondNumber;
	char stringArray[50];
	int arrayList[50];
	int noOfElements;
	
	
	do{	
		printf("\n***** MENU *****\n");
		printf("1. Greatest Common Divisor\n");
		printf("2. Merge sort of an array\n");
		printf("3. Function calculator\n");
		printf("4. Equal - Not Equal\n");
		printf("5. First capital letter in string\n");
		printf("6. Exit\n");
			
		printf("\nChoice: ");
		scanf("%d", &choice);
			
		switch(choice){
			case 1:{
				printf("\nFirst number: ");
				scanf("%d", &firstNumber);
				
				printf("Second number: ");
				scanf("%d", &secondNumber);
				
				printf("\nThe GCD of %d and %d is: %d\n\n", firstNumber, secondNumber, common(firstNumber, secondNumber));
				
				break;
			}
				
			case 2:{
				
				printf("Write number of elements for array, for maximum number of 50: ");
				scanf("%d", &noOfElements);
				printf("Write the elements for the array: ");
				for(i=0 ; i< noOfElements; i++){
					scanf("%d", &arrayList[i]);
					
				}
				
				merge_sort(arrayList, 0, noOfElements-1);
				
				printf("Sorted array:\n");
				for(i=0 ; i< noOfElements; i++){
					printf("%d ", arrayList[i]);
					
				}
				printf("\n");
				break;
			}
	
			case 3:{
				printf("\t| n/2 \t if n=0 (mod 2)\n");
				printf(" f(n)= <\n");
				printf("\t| 3n+1 \t if n=0 (mod 2)\n\n");
				
				printf("Write a number to calculate its values with the formula above: ");
				scanf("%d", &firstNumber);
				
				printf("\n");
				function_calculator(firstNumber);
				printf("\n");
			
				break;
			}
			
			case 4:{
				
				printf("\t| equal \t if ABCD = A^n + B^n + C^n + D^n\n");
				printf(" f(x)= <\t\t\t\t\t\t\t(n:number of digits)\n");
				printf("\t| not equal \t if ABCD != A^n + B^n + C^n + D^n\n\n");
				
				printf("Write a number to calculate its values with the formula above: ");
				scanf("%d", &firstNumber);

				check_number_equality(firstNumber);
				printf("\n");
	
				
				break;
				
			}
			
			case 5:{
				printf("Write a string, that is less than 200 characters:\n");
				scanf("%s", &stringArray);
			
				capital_string(stringArray);
				
				break;
			}
			default:{
				if(choice!=6) printf("Unsupported value. Please enter a number between 1 and 6.\n");
				else printf("Exiting...");
				break;
			}
		}	
		
	}while(choice!=6);

}



/*To find the Greatest Common Divisor of two numbers*/
int common(int no1, int no2){

	/*	This is called the Euclid's Algorithm for greatest common divisor, invented by Euclid roughly 2200 years ago.*/
	
	if (no1==0) {
		return no2;	
	}
	else {
		return common(no2%no1, no1);
	}
	
}

int function_calculator (int number) {
	
	if(number==1){
		printf("%d", number);
		return number;
	}
			
	else if(number%2==0){
		printf("%d ", number);
		return function_calculator(number/2);
	}
		
	else if(number%2==1){
		
		printf("%d ", number);
		return function_calculator(3*(number)+1);
	}

}

int capital_string(char *arr){
	
	/*Checks whether the first element of theh array is capital or not*/
	if(arr[0] > 'A' && arr[0] < 'Z'){
		printf("%c\n", arr[0]);
	}
	
	/*if first element of the array is not capital letter, then increment.*/
	else{
		return capital_string(arr+1);
	}

}

/* A recursively written power function, to not use the pow() function in math.h library.*/
int recursive_pow(int base, int exponent){
	
	if(base==0){
		if(exponent==0)
			return (-1);
		else
			return 0; 	
	}
	
	else if (exponent==0)
		return 1;
			
	else if (exponent==1)
		return (base);
		
	else if(exponent<0){
		printf("error");
	}

	else
		return (base * recursive_pow(base, exponent-1));
		
}

/*This function is for finding the number of digits in a number*/
int digit_finder(int number){
	
	int numberOfDigits = 0;
	while(number!=0) {
		numberOfDigits++;
		number=number/10;
	}
	
	return numberOfDigits;
}

/*Calculates the number if it fits the corresponding function, recursively.*/
int equal_not_equal_recursive (int number, int numberOfDigits){
	
	int subNumberOfDigits = digit_finder(number);	/*We are getting the number of digits again, so that the original one does not change.*/
	int sum = 0;
	int subNumber = 0;
	int div;
	
	/*Base condition is, whenever the number of digits has hit 1, recursive starts to return itself.*/
	if(subNumberOfDigits == 1){
		sum = sum + recursive_pow(number,numberOfDigits);
	}
	else{
		subNumber = number / 10;		/*We used another variable to not mess with the original one. Same with the line below.*/
		div = number % 10;
		sum = sum + recursive_pow(div,numberOfDigits);		/*Calculates the power of the current number.*/
		sum = sum + equal_not_equal_recursive(subNumber, numberOfDigits);	/*Recursive condition*/
	}
	return sum;
}

/*This function is for making the other function (equal_not_equal_recursive) not too crowded. It just prints the number if it is equal or not. */
void check_number_equality(int number){
	
	int numberOfDigits = digit_finder(number);
	int result = equal_not_equal_recursive(number, numberOfDigits);
	
	if(result == number){
		printf("Equal");
	}
	else{
		printf("Not Equal");
	}
	
}

int merge_sort(int array[], int lower, int higher){
	
	int middle;
	
	if (lower !=   higher){
		
		middle = (lower+higher)/2;
		
		merge_sort(array, lower, middle);
		merge_sort(array, middle+1, higher);
		
		merger_function(array, lower, middle, higher);
	}
	
}

int merger_function (int array[], int lower, int middle, int higher){
	
	int i, j;
	int left = middle-lower+1;
	int right = higher-middle;
	
	int tempArrayLeft[left], tempArrayRight[right];
	
	i=0;	/*This is for 'while loop' to start properly. Basically an initialization part. */
	j=0;	/*This is for 'while loop' to start properly. Basically an initialization part. */
	
	while(i<left){
		tempArrayLeft[i]=array[lower+i];
		i++;
	}
		
	while(j<right){
		tempArrayRight[j]=array[(middle+1)+j];
		j++;
	}
	
	
	i=0;	/*This is for 'while loops' to start properly. Basically an initialization part. */
	j=0;	/*This is for 'while loops' to start properly. Basically an initialization part. */
	
	while(i < left && j < right ){
		
		if(tempArrayLeft[i] <= tempArrayRight[j]){
			array[lower]=tempArrayLeft[i++];			
		}
		else{
			array[lower]=tempArrayRight[j++];
		}
		
		lower++;
	}
		
	/*Copies the elements in the temporary array to the original array. This is for left (lower) part.*/
	while(i < left){				
		array[lower++] = tempArrayLeft[i++];
	}
	
	/*Copies the elements in the temporary array to the original array. This is for right (upper) part.*/
	while(j < right){			
		array[lower++] = tempArrayRight[j++];
	}
}
