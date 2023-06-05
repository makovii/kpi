#include<windows.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#define N 12
#define PI 3.14159265
/*
 First A = 
{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, },
{ 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
{ 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, },
{ 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, },
{ 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, },
{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, },
{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, },
{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{ 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, },
*/

/*
First simA = 
{ 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, },
{    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, },
{       0, 0, 1, 0, 1, 1, 1, 1, 0, 0, },
{          0, 1, 1, 0, 1, 0, 0, 0, 0, },
{             0, 1, 1, 1, 0, 0, 0, 1, },
{                1, 1, 1, 1, 1, 0, 1, },
{                   1, 1, 1, 0, 0, 0, },
{                      1, 1, 1, 0, 1, },
{                         0, 1, 0, 1, },
{                            0, 0, 0, },
{                               0, 0, },
{                                  1, },
*/

/*
Second A =
{0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, },
{0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, },
{0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, },
{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, },
{0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, },
{0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, },
{1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, },
{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, },
{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
{0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, },
*/

/*
Second simA =
{0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, },
{0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, },
{1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, },
{1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, },
{0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, },
{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, },
{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, },
{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, },
{0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, },
*/

/*
Way 2 of A = 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, },
{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
{0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, },
{1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, },
{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, },
{0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, },
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const wchar_t ProgName[] = L"Лабораторна робота 4";

int A[N][N];
int simA[N][N];

//MATRIX GENERATION
void randmatrix(float k, int* matrix[N][N]) {
    srand(0520);
    float num;
    int element;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = (rand() / (float)RAND_MAX * 2) * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
        }
    }
}
void matrixSim(int A[N][N], int* B[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            //B[i][j] = 0;
            if (A[i][j] == 1) {
                B[j][i] = 1;
                B[i][j] = 1;
            }
        }
    }
}
void arrow(int px, int py, int dx, int dy, HDC hdc) {
    int lx, ly = py, rx = px, ry;
    if (dx == 0) return;
    else lx = px + (dx / abs(dx)) * 15;
    if (dy == 0) {
        ly = py - 15;
        ry = py + 15;
        lx = px + (15 * dx / abs(dx));
        rx = lx;
    }
    else ry = py + (dy / abs(dy)) * 15;
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void powMatrix1(int A[N][N], int simA[N][N]) {
    int countDeg2[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int countDeg1_input[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int countDeg1_out[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] == 1) {
                countDeg1_out[i]++;
                countDeg1_input[j]++;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (simA[i][j] == 1) {
                countDeg2[i]++;
                countDeg2[j]++;
            }
        }
    }
    printf_s("Matrix pow\n");
    printf_s("deg1+  deg1-  deg2\n");
    int true1 = 1;
    int true2 = 1;
    for (int i = 0; i < N; i++) {
        printf_s("%d     %d      %d", countDeg1_out[i], countDeg1_input[i], countDeg2[i]);
        printf_s("\n");
        for (int j = 0; j < N; j++) {
            if (countDeg1_input[i] != countDeg1_input[j]) true1 = 0;
            if (countDeg2[i] != countDeg2[j]) true2 = 0;
        }
    }
}

//void wayMatrix(int startA[N][N], int endA[N][N]) {
//    printf_s("Task 4.3\n");
//    printf_s("2 Way\n");
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            if (startA[i][j] == 1) {
//                for (int k = 0; k < N; k++) {
//                    if (A[j][k] == 1) printf_s("%d->%d->%d  ", i+1, j+1, k+1);
//                }
//            }
//        }
//        printf_s("\n");
//    }
//    printf_s("\n");
//    printf_s("3 Way\n");
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//            if (startA[i][j] == 1) {
//                for (int count1 = 0; count1 < N; count1++) {
//                    if (startA[i][count1] == 1) {
//                        for (int count2 = 0; count2 < N; count2++) {
//                            if (startA[i][count2] == 1) printf_s("%d->%d->%d->%d  ", i+1, j+1, count1+1, count2+1);
//                        }
//                    }
//                }
//            }
//        }
//        printf_s("\n");
//    }
//}
void drawgraph(HDC hdc, int startA[N][N], int components[N][N]) {
    int R = 250;                    // R of Circle graph
    int step = 0;  // step of vertex by circle
    int Center1_X = 900, Center1_Y = 300;

    int xPos[N];
    int yPos[N];
    int drawVert[N] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

    for (int vertex = 0; vertex < N; vertex++) {
        xPos[vertex] = Center1_X + R * cos(step * PI / 180);
        yPos[vertex] = Center1_Y - R * sin(step * PI / 180);
        step += 360 / N;
    }

    char* ellipseName[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C" };
    int dtx = 5, radius = 16, end, xDif, yDif, dx, dy, koef;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (components[i][j] == 0) continue;
            for (int count = 0; count < N; count++) {
                if (startA[j][count]) {
                    for (int count2 = 0; count2 < N; count2++) {
                        if (components[count2][count]) {
                            MoveToEx(hdc, xPos[i], yPos[i], NULL);
                            LineTo(hdc, xPos[count2], yPos[count2]);
                            xDif = xPos[i] - xPos[count2];
                            yDif = yPos[i] - yPos[count2];
                            if (xDif == 0 && yDif == 0) {
                                dx = 0;
                                dy = 0;
                            }
                            else {
                                koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                                dx = xDif / koef;
                                dy = yDif / koef;
                            }
                            arrow(xPos[count2] + dx, yPos[count2] + dy, dx, dy, hdc);
                        }
                    }
                }
            }
            drawVert[i] = 1;
        }
    }
    for (int i = 0; i < N; i++) {
        if (drawVert[i]) {
            Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
            TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, ellipseName[i], 1);
        }
    }
}

void powMatrix(HDC hdc, int A[N][N], int startA[N][N], int reachA[N][N], int length) {
    int num, counter = 1, countery = 1;
    char text[15];
    int newA[N][N];
    int connA[N][N] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };
    int components[N][N] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int usedVerticles[N] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

    //multiply matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = 0;
            for (int count = 0; count < N; count++) {
                num += A[i][count] * startA[count][j];
            }
            newA[i][j] = num;
            reachA[i][j] += num;
        }
    }
    //all tasks operations
    if (length == 2) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                //print ways of 2
                //if (startA[i][j] == 1) {
                //    for (int count = 0; count < N; count++) {
                //        if (startA[j][count] == 1) {
                //            //printf_s("%d->%d->%d  ", i + 1, j + 1, count + 1);
                //                counter++;
                //                if ((float)counter / 17 > 1) {
                //                    countery++;
                //                    counter = 1;
                //                }
                //        }
                //    }
                //}

                //print ways of 3
                //printf_s("\n");
                if (startA[i][j] == 1) {
                    for (int count = 0; count < N; count++) {
                        if (startA[j][count] == 1) {
                            for (int count2 = 0; count2 < N; count2++) {
                                if (startA[count][count2] == 1) {
                                    printf_s("%d->%d->%d->%d  ", i + 1, j + 1, count + 1, count2 + 1);
                                    counter++;
                                    if ((float)counter / 17 > 1) {
                                        countery++;
                                        counter = 1;
                                    }
                                }
                            }
                        }
                    }
                }

                //reach matrix
                reachA[i][j] += startA[i][j];
                if (reachA[i][j] >= 1) reachA[i][j] = 1;
                else {
                    connA[i][j] = 0;
                    connA[j][i] = 0;
                }
                //print reach matrix
                //printf_s("%d ", reachA[i][j]);

            }
            //printf_s("\n");
        }

        //print connection matrix
        //printf_s("Connection Matrix\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                //printf_s("%d ", connA[i][j]);

            }
            //printf_s("\n");
        }
        countery = 1;
        //find components
        //printf_s("Components connection\n");
        for (int count = 0; count < N; count++) {
            counter = 1;
            for (int i = 0; i < N; i++) {
                if (usedVerticles[i] == 1) continue;
                for (int j = 0; j < N; j++) {
                    if (connA[count][j] != connA[i][j]) break;
                    if (j == N - 1) {
                        usedVerticles[i] = 1;
                        components[countery][i] = 1;
                        //printf_s("Comp%d ", countery);
                        //printf_s("%d ", i+1);
                        //printf_s("\n");
                        counter++;
                    }
                }
            }
            if (components[countery][0] || components[countery][1] || components[countery][2] ||
                components[countery][3] || components[countery][4] || components[countery][5] ||
                components[countery][6] || components[countery][7] || components[countery][8] ||
                components[countery][9] || components[countery][10] || components[countery][11]) countery++;
        }
    }

    if (length > 2) powMatrix(hdc, newA, startA, reachA, length - 1);
    drawgraph(hdc, startA, components);
}


//=========================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = COLOR_BTNFACE + 13;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName,
        L"LAB 4. Created d by Makoviy V.",
        WS_OVERLAPPEDWINDOW,
        70,
        70,
        1250,
        650,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;         // дескриптор проекту
    PAINTSTRUCT ps;  // екземпляр структуры
    // For Console
    AllocConsole();
    HANDLE stdHandle;
    int hConsole;
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    int diagonalA[N][N] = {
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    };

    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        char* ellipseName[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C" };
        int xPos[N];
        int yPos[N];
        int dx = 16, dy = 16, dtx = 5;  // R of Circle vertex and bias number
        int R = 250;                    // R of Circle graph
        int step = 0;  // step of vertex by circle
        int Center1_X = 300, Center1_Y = 300;

        HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN GreenPen = CreatePen(PS_SOLID, 1, RGB(41, 106, 72));
        HPEN Dark_BluePen = CreatePen(PS_SOLID, 1, RGB(41, 106, 250));
        HPEN Light_PurplePen = CreatePen(PS_SOLID, 1, RGB(232, 106, 250));
        HPEN WitePen = CreatePen(PS_SOLID, 1, RGB(232, 246, 250));
        HPEN REDPen = CreatePen(PS_SOLID, 1, RGB(250, 17, 37));

        //vertex 
        for (int vertex = 0; vertex < N; vertex++) {
            xPos[vertex] = Center1_X + R * cos(step * PI / 180);
            yPos[vertex] = Center1_Y - R * sin(step * PI / 180);
            step += 360 / N;
        }
        int Pen[6] = { BlackPen, GreenPen, Dark_BluePen, Light_PurplePen, WitePen, REDPen };
        int number = 0;

        //=========================================================
        int Switch = 1;

        int radius = 16, divine = 1, xDif, yDif;
        float koef;

        //Task 4
        if (Switch == 2) {

            randmatrix(1.0 - 2 * 0.005 - 0 * 0.005 - 0.27, A);
            int way2A[N][N];
            int way3A[N][N];
            for (int start = 0; start < N; start++) {
                for (int end = 0; end < N; end++) {
                    //printf_s("%d, ", A[start][end]);

                    SelectObject(hdc, Pen[number]);

                    if (A[start][end] == 1) {
                        xDif = xPos[start] - xPos[end];
                        yDif = yPos[start] - yPos[end];
                        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                        dx = xDif / koef;
                        dy = yDif / koef;
                        if (start == end) {
                            MoveToEx(hdc, xPos[end], yPos[end], NULL);
                            LineTo(hdc, xPos[end] + 40, yPos[end] + 10);
                            LineTo(hdc, xPos[end] + 40, yPos[end] + 40);
                            LineTo(hdc, xPos[end] + 10, yPos[end] + 40);
                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + 2, yPos[end] + 13, 2, 13, hdc);
                        }
                        else if (A[start][end] == 1 && A[end][start] == 1) {
                            MoveToEx(hdc, xPos[start], yPos[start], NULL);
                            LineTo(hdc, xPos[end] + xDif / 2 + (6 * divine), yPos[end] + yDif / 4 + (6 * divine));
                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + dx, yPos[end] + dy, dx, dy, hdc);
                            divine = -divine;
                        }
                        else {
                            MoveToEx(hdc, xPos[start], yPos[start], NULL);
                            if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                                LineTo(hdc, xPos[end] + xDif / 2, yPos[end] - 35);
                                dx = xDif / 2 / koef;
                                dy = (yDif - 35) / koef;
                            }
                            else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                                LineTo(hdc, xPos[end] + xDif / 2, yPos[end] + yDif / 1);
                                dx = xDif / 2 / koef;
                                dy = yDif / koef;
                            }

                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + dx, yPos[end] + dy, dx, dy, hdc);
                        }
                    }
                }
                //printf_s("},\n{");
                if (number == 5) number = 0;
                else number++;
            }

            SelectObject(hdc, BluePen);
            for (int i = 0; i < N; i++) {
                Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
                TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, ellipseName[i], 1);

            }
            matrixSim(A, simA);

            //Task 4.1
            //for (int i = 0; i < N; i++) {
            //    for (int j = 0; j < N; j++) {
            //        printf_s("%d, ", simA[i][j]);
            //    }
            //    printf_s("},\n{");
            //}

            // Task 4.2
            //printf_s("Task 4.2\n");
            powMatrix(hdc, A, A, diagonalA, N - 1);

            // Task 4.3
            //wayMatrix(A, A);


        }

        //====================================================
        if (Switch == 1) {

            randmatrix(1.0 - 2 * 0.01 - 0 * 0.01 - 0.3, A);
            int countDeg2[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            int countDeg1_input[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            int countDeg1_out[N] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            for (int start = 0; start < N; start++) {
                for (int end = 0; end < N; end++) {
                    //printf_s("%d, ", A[start][end]);

                    SelectObject(hdc, Pen[number]);

                    if (A[start][end] == 1) {
                        countDeg1_out[start]++;    // for deg of 1 graph out
                        countDeg1_input[end]++;    // for deg of 1 graph input
                        xDif = xPos[start] - xPos[end];
                        yDif = yPos[start] - yPos[end];
                        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                        dx = xDif / koef;
                        dy = yDif / koef;
                        if (start == end) {
                            MoveToEx(hdc, xPos[end], yPos[end], NULL);
                            LineTo(hdc, xPos[end] + 40, yPos[end] + 10);
                            LineTo(hdc, xPos[end] + 40, yPos[end] + 40);
                            LineTo(hdc, xPos[end] + 10, yPos[end] + 40);
                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + 2, yPos[end] + 13, 2, 13, hdc);
                        }
                        else if (A[start][end] == 1 && A[end][start] == 1) {
                            MoveToEx(hdc, xPos[start], yPos[start], NULL);
                            LineTo(hdc, xPos[end] + xDif / 2 + (6 * divine), yPos[end] + yDif / 4 + (6 * divine));
                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + dx, yPos[end] + dy, dx, dy, hdc);
                            divine = -divine;
                        }
                        else {
                            MoveToEx(hdc, xPos[start], yPos[start], NULL);
                            if (yDif == 0 && abs(xDif) > 300 && end <= 3) {
                                LineTo(hdc, xPos[end] + xDif / 2, yPos[end] - 35);
                                dx = xDif / 2 / koef;
                                dy = (yDif - 35) / koef;
                            }
                            else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                                LineTo(hdc, xPos[end] + xDif / 2, yPos[end] + yDif / 1);
                                dx = xDif / 2 / koef;
                                dy = yDif / koef;
                            }

                            LineTo(hdc, xPos[end], yPos[end]);
                            arrow(xPos[end] + dx, yPos[end] + dy, dx, dy, hdc);
                        }
                    }
                }
                //printf_s("},\n{");
                if (number == 5) number = 0;
                else number++;

            }
            SelectObject(hdc, BluePen);
            for (int i = 0; i < N; i++) {
                Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
                TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, ellipseName[i], 1);

            }

            //printf_s("\n");
            //=========================================================

            matrixSim(A, simA);

            int xPos1[12];
            int yPos1[12];
            int startCoordx1 = 20;
            int startCoordy1 = 560;

            int R2 = 250;
            int step1 = 0;
            int Center2_X = 900, Center2_Y = 300;
            for (int vertex = 0; vertex < N; vertex++) {
                xPos1[vertex] = Center2_X + R2 * cos(step1 * PI / 180);
                yPos1[vertex] = Center2_Y - R2 * sin(step1 * PI / 180);
                step1 += 360 / N;
            }

            int dtx1 = 5, radius1 = 16, divine1 = 1, dx1, dy1, xDif1, yDif1;
            float koef1;

            SelectObject(hdc, BlackPen);

            for (int start = 0; start < N; start++) {
                for (int end = start; end < N; end++) {
                    //printf_s("%d, ", simA[start][end]);
                    if (simA[start][end] == 1) {
                        countDeg2[start]++; // For deg of 2 graph
                        countDeg2[end]++; // For deg of 2 graph
                        xDif1 = xPos1[start] - xPos1[end];
                        yDif1 = yPos1[start] - yPos1[end];
                        koef1 = sqrt(xDif1 * xDif1 + yDif1 * yDif1) / radius1;
                        dx1 = xDif1 / koef1;
                        dy1 = yDif1 / koef1;
                        if (start == end) {
                            MoveToEx(hdc, xPos1[end], yPos1[end], NULL);
                            LineTo(hdc, xPos1[end] + 40, yPos1[end] + 10);
                            LineTo(hdc, xPos1[end] + 40, yPos1[end] + 40);
                            LineTo(hdc, xPos1[end] + 10, yPos1[end] + 40);
                            LineTo(hdc, xPos1[end], yPos1[end]);
                            //if (simA[start][start] == 1) countDeg2[start]++; // For deg of 2 graph

                        }
                        else if (simA[start][end] == 1) {
                            MoveToEx(hdc, xPos1[start], yPos1[start], NULL);
                            LineTo(hdc, xPos1[end], yPos1[end]);
                            divine1 = -divine1;
                        }
                    }
                }
                //printf_s("},\n{");
            }

            SelectObject(hdc, BluePen);
            for (int i = 0; i < N; i++) {
                Ellipse(hdc, xPos1[i] - radius1, yPos1[i] - radius1, xPos1[i] + radius1, yPos1[i] + radius1);
                TextOut(hdc, xPos1[i] - dtx1, yPos1[i] - 8, ellipseName[i], 1);
            }

            // Task 2
            printf_s("Task 2\n");

            powMatrix1(A, simA);
            printf_s("\n");

            //Task3
            printf_s("Task3\n");
            for (int i = 0; i < N; i++) {
                if ((countDeg1_input[i] + countDeg1_out[i]) == 0) printf_s("vertex %d of the directed graph is isolated\n", i + 1);
                else if (countDeg1_input[i] + countDeg1_out[i] == 1) printf_s("vertex %d directed graph dangling\n", i + 1);

                if (countDeg2[i] == 0) printf_s("vertex %d of the undirected graph is isolated\n", i + 1);
                else if (countDeg2[i] == 1) printf_s("vertex %d undirected graph dangling\n", i + 1);
            }

        }

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));

        return 0;
        FreeConsole();
    }
}
