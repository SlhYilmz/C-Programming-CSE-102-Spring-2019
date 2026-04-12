#include <stdio.h>
double someWeirdStuff(int *b, double a);
int main(void)
{
	int a = 4;
	printf("A is %05d\n",a);
	printf("%5.2f\n",someWeirdStuff(&a,4));
}

double someWeirdStuff(int *b, double a)
{
	int result; 
	result = *b + a++;
	printf("a is: %f, b is %5d and result is %d\n", a, *b, result);
	++(*b);
	a++;
	result++;
	printf("%.5d %5.2f %8d\n", a, *b, result);
	printf("%10s %d %d %d\n","finally",a, *b, result );
	return result++;
}