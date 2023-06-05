#include <stdio.h>

float do1(float x) {
	return (-3 * x * x) / 5 + 9;
}

float do2(float x) {
		return(15 * x - 2);
}
int condition1(float x) {
	if (x >= 0)
		if (x <= 8)
			return 1;
	if (x >= 16)
		return 1;
}
int condition2(float x) {
	if (x < -1)
		return 1;
}
void main() {
	float x;
	printf("Input x : ");
	scanf_s("%f", &x);
	if (condition1(x)==1) 
		printf("%f \n", do1(x));

	if (condition2(x)==1) 
		printf("%f \n", do2(x));

	if (condition1(x) != 1)
		if (condition2(x) != 1)
			printf("There is no such \n");
} 
