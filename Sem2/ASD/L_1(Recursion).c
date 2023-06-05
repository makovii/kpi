#include <stdio.h>
#define length 5


float recursion1(int number, float F, int i, float sum) {
	
	if (i < length +1) {
		sum += F;
		printf_s("%d: %f\n", i, F);
		i++;
		F = (F * number * number) / (4 * i * i + 2 * i);
		recursion1(number, F, i, sum);
	}
	else return printf_s("Sum is: %f\n",sum);
}

float recursion2(int number, float F, int i, float* sum) {
	if (i < length) {
		i++;
		F = recursion2(number, F, i, sum);
		F = (F * number * number) / (4 * (length + 2 - i) * (length + 2 - i) + 2 * (length + 2 - i));
	}
	
	*sum += F;
	if (*sum == F) {
		printf_s("1: %f\n", F);
	}
	else {
		printf_s("%d: %f\n", length + 2 - i, F);
	}
	return F;
}

float recursion3(int number, float F, int i, float sum) {
	if (i < length) {
		i++;
		F = (F * number * number) / (4 * i * i + 2 * i);
		if (i == length) {
			sum += F;
			printf_s("%d: %f\n", i, F);
			return sum;
		}
		sum = recursion3(number, F, (i), sum);
	}
	sum += F;
	printf_s("%d: %f\n", i, F);
	if (i == 2) {
		i--;
		F = number;
		sum += F;
		printf_s("%d: %f\nSum: %f\n", i, F, sum);
	}
	return sum;
}

float cycle(number) {
	float F;
	F = number;
	float sum = F;

	printf_s("\nCycle:\n");
	printf_s("1: %f\n", F);

	for (int i = 2; i < length + 1; i++) {
		
		F = (F * number * number) / (4 * i * i + 2 * i);
		printf_s("%d: %f\n", i, F);
		sum = sum + F;
	}
	printf_s("Sum is: %f", sum);
}

void main() {
	int number ;

	printf_s("Send me number: ");
	scanf_s("%d", &number);

	float F = number;
	int count1 = 1;
	float sum = 0;
	printf_s("Recursion 1:\n");
	recursion1(number, F, count1, sum);

	printf_s("\nRecursion 2:\n");
	recursion2(number, F, count1, &sum);
	printf_s("Sum is: %f\n", sum);

	sum = 0;
	printf_s("\nRecursion 3:\n");
	recursion3(number, F, count1, sum);

	cycle(number);
};
