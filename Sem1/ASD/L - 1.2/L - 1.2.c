#include <stdio.h>
#include <math.h>
//Первая программа
double option1(int n) {
	double S = 0;
	int count1 = 0;
	double power = 1;
	for (int i = 1; i <= n; i++) {
		power *= 4;
		count1++;
		double znam = 0, ches = 1;

		for (int j = 1; j <= i; j++) {
			ches *= (j + cos(j));
			count1 += 3;
		}
		znam = (power - i);
		count1++;
		S += (ches / znam);
		count1 += 2;
		
	}
	printf("count1 : %d \n", count1);
	return S;
}
// Вторая программа
double option2(int n) {
	double S = 0;
	int count2 = 0;
	double power2 = 1;
	double ches2 = 1, znam2 = 0;
	int i ;
	for (i = 1; i <= n; i++) {
		power2 *= 4;
		count2++;
		ches2 *= (i + cos(i));
		count2 += 3;
		znam2 = (power2 - i);
		count2++;
		S += (ches2 / znam2);
		count2 += 2;
	}
	printf("count2 : %d \n", count2);
	return S;
}
void main() {
	int n;
	printf_s("Input n: ");
	scanf_s("%d", &n);
	double res1 = option1(n);
	printf_s("Answer option1 :  %.7f \n",res1);
	printf_s("\n");
	double res2 = option2(n);
	printf_s("Answer option2 :  %.7f \n", res2);
}
