/*What is the output of following program ?*/

#include <stdio.h>
double someWeirdStuff(int *b, double a);
int main(void)
{
	int a = 4;/*careful a maybe unitinialized, in exam note that "a has a junk value, assuming as it is 0" or something.*/
	printf("A is %05d\n",a);
	printf("%.9f\n",someWeirdStuff(&a,4));
}

double someWeirdStuff(int *b, double a)
{
	int result; 
	result = *b + a++;
	printf("a is: %f, b is %5d and result is %d\n", a, *b, result);
	++(*b);
	a++;
	result++;
	printf("%5.2f %d %8d\n", a, *b, result);
	printf("%10s %f %d %d\n","finally",a, *b, result );
	return result++;
}
