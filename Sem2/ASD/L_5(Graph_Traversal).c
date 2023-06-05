#include<windows.h>
#include<math.h>
#include<stdio.h>
#include <stdlib.h>
#include<conio.h>
#define N 12
#define PI 3.14159265

/*
Array A[N][N] == 
{0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, },
{0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, },
{0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, },
{1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, },
{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, },
{0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, },
{0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, },
{1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, },
{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, },
{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, },
{1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, },
{0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, },
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

const wchar_t ProgName[] = L"Лабораторна робота 5";

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

void drawVertex(HDC hdc, int xPos[N], int yPos[N], char* ellipseName[N], int i) {
    int dtx = 5, radius = 16;
    Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
    TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, ellipseName[i], 1);
}

void BFS(HDC hdc, int xPos[N], int yPos[N], char* ellipseName[N], int A[N][N], int start) {
    int treeMatrix[N][N] = {
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0,0 }
    };

    HPEN WitePen = CreatePen(PS_SOLID, 5, RGB(232, 246, 250));
    SelectObject(hdc, WitePen);

    int queue[N + 1] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int visited[N] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int item = 0;
    queue[item] = start;
    visited[queue[item]] = 1;
    int count = 1;

    while (count != N) {
        for (int i = 0; i < N; i++) {
            if (A[queue[item]][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                
                queue[count] = i;
                count++;
                treeMatrix[queue[item]][i] = 1;

                MoveToEx(hdc, xPos[queue[item]], yPos[queue[item]], NULL);
                LineTo(hdc, xPos[i], yPos[i]);
                drawVertex(hdc, xPos, yPos, ellipseName, queue[item]);
                drawVertex(hdc, xPos, yPos, ellipseName, i);
                _getch();

            }
        }
        item++;
    }
    printf_s("Tree Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf_s("%d ", treeMatrix[i][j]);
        }
        printf_s("\n");
    }

    printf_s("\nConnect Matrix:\n");
    for (int i = 0; i < N; i++) {
            printf_s("%d: %d\n", i + 1, queue[i] + 1);
    }
}

void DFS(HDC hdc, int xPos[N], int yPos[N], char* ellipseName[N], int A[N][N], int start) {//depth
    int treeMatrix[N][N] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0 }
    };

    HPEN WitePen = CreatePen(PS_SOLID, 5, RGB(232, 246, 250));
    SelectObject(hdc, WitePen);

    int queue[N] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int visited[N] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
    int item = 0;
    queue[item] = start;
    visited[queue[item]] = 1;
    int count = 1;
    int flag = 0;

    while (count != N) {
        for (int i = 0; i < N; i++) {
            if (A[queue[item]][i] == 1 && visited[i] == 0) {
                visited[i] = 1;

                queue[count] = i;
                count++;
                flag = 1;
                treeMatrix[queue[item]][i] = 1;

                MoveToEx(hdc, xPos[queue[item]], yPos[queue[item]], NULL);
                LineTo(hdc, xPos[i], yPos[i]);
                drawVertex(hdc, xPos, yPos, ellipseName, queue[item]);
                drawVertex(hdc, xPos, yPos, ellipseName, i);

                _getch();
                break;
            }
            else flag = 0;
        }
        if (flag == 0) item--;
        else item++;
    }

    printf_s("Tree Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf_s("%d ", treeMatrix[i][j]);
        }
        printf_s("\n");
    }

    printf_s("\nConnect Matrix:\n");
    for (int i = 0; i < N; i++) {
        printf_s("%d: %d\n", i + 1, queue[i] + 1);
    }
}


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
        L"LAB 5. Created d by Makoviy V.",
        WS_OVERLAPPEDWINDOW,
        600,
        100,
        700,
        700,
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


    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
    char* ellipseName[12] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C" };
    int xPos[N];
    int yPos[N];
    int dx = 16, dy = 16, dtx = 5;  // R of Circle vertex and bias number
    int R = 300;                    // R of Circle graph
    int step = 0;  // step of vertex by circle
    int Center1_X = 350, Center1_Y = 325;

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

    int radius = 16, divine = 1, xDif, yDif;
    float koef;

    randmatrix(1.0 - 2 * 0.01 - 0 * 0.005 - 0.15, A);

    for (int start = 0; start < N; start++) {
        for (int end = 0; end < N; end++) {

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
        if (number == 5) number = 0;
        else number++;
    }

    SelectObject(hdc, BluePen);
    for (int i = 0; i < N; i++) {
        drawVertex(hdc, xPos, yPos, ellipseName, i);
    }

    matrixSim(A, simA);

    //BFS(hdc, xPos, yPos, ellipseName, A, 1);
    DFS(hdc, xPos, yPos, ellipseName, A, 1);
        
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
