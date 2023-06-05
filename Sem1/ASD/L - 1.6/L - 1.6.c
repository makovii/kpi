#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int Mat[24][80] = {0};

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printM(int i, int j) {
	gotoxy(j, i);
	putchar('W');
}


void main() {
	
	int pi = 0;
	int pj = 0;
	int po = 0;

	while (pi != 23 || pj != 79){
		if (pi == 0 && pj == 0) {
			printM(pi, pj);
			Mat[pi][pj] = 1;
			pi++;
			po = 1;
		}
		else { 
			if (po == 0) {
				if (pi <= 23 && pj == 0) { //LEFT 
					pi--;
					pj++;
					po = 1;
				}
				else if (pj > 0 && pi == 0) { //TOP
					pj++;
					po = 2;
				}
				else if (pi <= 23 && pj == 79) { //RIGHT
					pi++;
					pj--;
					po = 2;
				}
				else if (pj > 0 && pi == 23) {// DOWN 
					pj++;
					po = 1;
				}
			}
			else if (po == 1) {
				if (pj != 79) {
					if (pi == 0) {
						po = 0;
					}
					else {
						pi--;
						pj++;
					}
				}
				else {
					pi++;
					po = 0;
				}
			}
			else if (po == 2) {
				if (pj != 0) {
					if (pi == 23) {
						po = 0;
					}
					else {
						pi++;
						pj--;
					}
				}
				else {
					pi++;
					po = 0;
				}
			}
		}
		Sleep(10);
		printM(pi, pj);
		Mat[pi][pj] = 1;

	}
	getchar();
}
