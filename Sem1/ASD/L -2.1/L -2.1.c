#include <stdio.h>

void main() {
	int mat[10][10] = { {8,  5,   7,  9,   6,   7,  8,   5,  3,   4},
						{7,  4,   6,  8,   5,   6,  7,   4,  3,   3},
						{6,  3,   6,  7,   4,   5,  7,   4,  2,   3},
						{4,  2,   6,  6,   3,   4,  6,   3,  2,   2},
						{4,  1,   6,  5,   2,   3,  5,   3,  2,   -1},
						{4,  0,   6,  4,   1,   3,  4,   2,  1,   -1},
						{3, -1,   6,  4,   0,   1,  4,   1,  0,   -1},
						{2, -2,   6,  3,   0,   0,  3,   0,  0,   -1},
						{1, -2,   6,  2,   0,   0,  2,   0,  0,   -1},
						{0, -2,   6,  1,   0,   0,  1,   0,  0,   -1}
	};
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf_s("%d  ", mat[i][j]);
		}
		printf_s("\n");
	}
	printf_s("\n");
	printf_s("Search [0,5] \n \n");
	printf_s("Program 1 \n");

	for (int j = 0; j < 10; j++) {

		int average ; //cредний элемент  
		int first = 0;
		int last = 9;

		while (first < last) {
			average = first + (last - first) / 2;
			if (5 >= mat[average][j]){
				last = average;
			}
			else
				first = average + 1;
		}
		if ((0 <= mat[last][j]) && (5 >= mat[last][j])) {
			printf_s("Value is found in %d %d \n", last+1, j+1);
		}
		else
			printf_s("value is not found in column  %d \n", j+1);
		
	}

	printf_s("\nProgram 2 \n");
	for (int j = 0; j < 10; j++) {
	
		int average = 0; //cредний элемент  
		int first = 0;
		int last = 10;
		int peremena = 0;
		while (first < last) {
			average = first + (last - first) / 2;
			if (5 >= mat[average][j]) {
				if (0 <= mat[average][j] && 5 >= mat[average][j]) {
					peremena = 1;
					goto breakAll;
				}
				else
					last = average;
			}
			else
				first = average + 1;
		}
		
	breakAll: {
		if ( peremena == 0)
			printf_s("value is not found in column  %d \n", j + 1);
		else 
			printf_s("Value is found in %d %d \n", average +1 , j + 1);
		}		
	}
}
