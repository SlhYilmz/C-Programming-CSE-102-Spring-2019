#include <stdio.h>

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

/*calculates the number of digits of the entered number.*/
int digit_finder(int number){
	
	int numberOfDigits = 0;
	while(number!=0) {
		numberOfDigits++;
		number=number/10;
	}
	
	return numberOfDigits;
}

int equal_not_equal (int number, int numberOfDigits) {
		
	int numberTemp, result=0;
	numberTemp = number;
		
	while(numberTemp != 0){
		result =  result + recursive_pow(numberTemp%10, numberOfDigits) ;
		numberTemp = numberTemp / 10 ;
	}
		
	printf("%d\n", result);
		
	if(result==number){
		printf("equal");	
	}
	else{
		printf("not equal");	
	}

}

void check_number_equality(int number){
	int numberOfDigits = digit_finder(number);
	int result = equal_not_equal_recursive(number,numberOfDigits);
	if(result == number){
		printf("Equal");
	}
	else{
		printf("Not Equal");
	}
	
}

int equal_not_equal_recursive (int number, int numberOfDigits){
	
	int subNumberOfDigits = digit_finder(number);
	int sum = 0;
	int subNumber = 0;
	int div;
	if(subNumberOfDigits == 1){
		sum = sum + recursive_pow(number,numberOfDigits);
	}
	else{
		subNumber = number / 10;
		div = number % 10;
		sum = sum + recursive_pow(div,numberOfDigits);		
		sum = sum + equal_not_equal_recursive(subNumber, numberOfDigits);
	}
	return sum;
	
	
}


int main(){
	
	int firstNumber, numberOfDigits;

	printf("Write a number to calculate its values with the formula above: ");
	scanf("%d", &firstNumber);

	check_number_equality(firstNumber);
	printf("\n");
	
	
return 0;
}
