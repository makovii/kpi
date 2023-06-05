#include <stdio.h>
#include <time.h>
#include <conio.h>

void shell(float mat[8][8], int n) {// Shell Algoritm
	for (int i = 0; i < n; i++) { 
		int step = n / 2;
		for (int j = 0; j < n + 1; j++) {
			for (int count = 0; count < j; count++) {
				int index = count;
				float value = mat[i][count];
				while ((index >= step) && (mat[i][index - step] > value)) {
					mat[i][index] = mat[i][index - step];
					index -= step;
				}

				mat[i][index] = value;
			}
			if (step > 1)
				step /= 2;
		}
	}
}

void print(float mat[8][8], int n) {// Output
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf_s("%.2f ", mat[i][j]);
		}
		printf_s("\n");
	}
}
void main() {
	float mat[8][8];
	int n = 8;

	printf_s("1. Before sorting\n");
	for (int i = 0; i < n; i++) { // Random filling
		for (int j = 0; j < n; j++) {
			mat[i][j] = (100 + (rand() % 1000)) * 0.01;
			printf_s("%.2f ", mat[i][j]);
		}
		printf_s("\n");
	}
	printf_s("\nAfter sorting:\n");
	shell(mat, n); // sorting
	print(mat, n); // output

	printf_s("\n2. Before sorting\n");
	for (int i = 0; i < n; i++) { // Ordered array from low to high
		for (int j = 0; j < n; j++) {
			mat[i][j] = (i) + (j);
			printf_s("%.2f ", mat[i][j]);
		}
		printf_s("\n");
	}
	printf_s("\nAfter sorting:\n");
	shell(mat, n); // sorting
	print(mat, n); // output

	printf_s("\n3. Before sorting\n"); // Ordered array from high to low
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] = (8 - i)+(8 - j);
			printf_s("%.2f ", mat[i][j]);
		}
		printf_s("\n");
	}
	printf_s("\nAfter sorting:\n");
	shell(mat, n); // sorting
	print(mat, n); // output
}

