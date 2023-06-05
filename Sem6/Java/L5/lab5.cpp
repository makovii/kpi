/*
ПЗВПКС
Лабораторна робота 5, Варіант 6
Завдання:
  A = Z*MS*e + D*(MX*MS))
Введення – виведення:
  T1 = -
  T2 = MX, A
  T3 = Z,D
  T4 = -
  T5 = -
  T6 = -
  T7 = -
  T8 = MS,e

Маковій Віктор, ІП-05
Дата 28.05.2023
*/

using namespace std;

#pragma region Includes
#include <iostream>
#include <string>
#include <mpi.h>
#include <chrono>
#include "matrix.h"
#include <vector>
#pragma endregion

#pragma region Constants
const int N = 800;
const int P = 8;
const int H = N / P;
const int INPUT = 1;

const int TAG1 = 1;
const int TAG2 = 2;
const int TAG3 = 3;
const int TAG4 = 4;
const int TAG5 = 5;
const int TAG6 = 6;
const int TAG7 = 7;
const int TAG8 = 8;
const int TAG9 = 9;
const int TAG10 = 10;
const int TAG11 = 11;
const int TAG12 = 12;
const int TAG13 = 13;
const int TAG14 = 14;

#pragma endregion

int A[N];

void operation1(int Z[], int D[], int MS[][N], int MX[][N], int e, int start)
{
  int end = start + H;
  int part1 = 0;
  int part2 = 0;
  for (int i = start; i < end; i++)
  {
    part2 = 0;
    for (int j = 0; j < N; j++)
    {
      part2 += Z[j] * MS[i][j] * e;
      part1 = 0;
      for (int k = 0; k < N; k++)
      {
        part1 += D[j] * (MX[i][j] * MS[i][j]);
      }
    }
    A[i] = part2 + part1;
  }

  // return A;
}


int main(int argc, char **argv)
{
  // Declare new datatype for matrix
  MPI_Datatype row_type;
  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  int Z[N];
  int D[N];
  int MS[N][N];
  int MX[N][N];
  int e;

  MPI_Comm graph_cart;
  MPI_Comm graph_comm;
  int nnodes = 8; /* number of nodes */
  int index[8] = { 1, 3, 5, 7, 9, 11, 13, 14 }; /* index definition */
  int edges[15] = { 1, 0, 2, 1, 3, 2, 4, 3, 5, 4, 6, 5, 7 , 6 }; /* edges definition */
  int reorder = 1; /* allows processes reordered for efficiency */
  MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, reorder, &graph_comm);


  const int NUM_DIMS = 1;
  int periods[NUM_DIMS]{ 0 };
  int dims[NUM_DIMS]{ 8 };
  reorder = 0;
  MPI_Dims_create(nnodes, NUM_DIMS, dims);
  MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &graph_cart);


  // rank of the calling process
  int t_id;
  MPI_Comm_rank(MPI_COMM_WORLD, &t_id);

  if (t_id == 0)
  { // T1
    printf("T1 start\n");

    // Прийняти від T2
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 1, TAG14, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&(MS[0][0]), H * N, MPI_INT, 1, TAG14, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 1, TAG14, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 1, TAG14, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 1, TAG14, graph_cart, MPI_STATUS_IGNORE);

    printf("START CALCULATION t1\n");
    operation1(Z, D, MS, MX, e, 0);

    MPI_Send(&A[0], H, MPI_INT, 1, TAG1, graph_cart);
    printf("T1 end\n");
  }
  else if (t_id == 1)
  { // T2
    printf("T2 start\n");
    auto startTime = chrono::high_resolution_clock::now();

    // Введення MX
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        MX[i][j] = INPUT;
      }
    }

    // Надіслати MX в T1
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 0, TAG14, graph_cart);

    // Надіслати MX в T3
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 2, TAG2, graph_cart);

    printf("SEND INPUT t2\n");

    // Прийняти від T3
    int partsT2 = H * 2;
    MPI_Recv(&(MS[0][0]), partsT2 * N, MPI_INT, 2, TAG13, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 2, TAG13, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 2, TAG13, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 2, TAG13, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t2 from t3\n");

    // Надіслати MX, MS, e, Z, D в T1
    MPI_Send(&(MS[0][0]), H * N, MPI_INT, 0, TAG14, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 0, TAG14, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 0, TAG14, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 0, TAG14, graph_cart);

    printf("START CALCULATION t2\n");

    operation1(Z, D, MS, MX, e, H * 1);

    // Прийняти A
    MPI_Recv(&A[0], H, MPI_INT, 0, TAG1, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&A[H * 2], H * 6, MPI_INT, 2, TAG13, graph_cart, MPI_STATUS_IGNORE);

    // Виведення результатів

    printf("Results:\n");
      for (int i = 0; i < N; i++)
      {
        cout << A[i] << " ";
      }
    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - startTime);
    cout << "T2 end"
         << endl;
    cout << "Lab finished in " << duration.count() << " ms, N = " << N << endl;
  }
  else if (t_id == 2)
  { // T3
    printf("T3 start\n");

    // Введення Z, D
    for (int i = 0; i < N; i++)
    {
      Z[i] = INPUT;
      D[i] = INPUT;
    }
    // Прийняти від T2
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 1, TAG2, graph_cart, MPI_STATUS_IGNORE);

    // Надіслати MX, Z, D в T4
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 3, TAG3, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 3, TAG3, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 3, TAG3, graph_cart);

    // Прийняти від T4
    MPI_Recv(&(MS[0][0]), H * 3 * N, MPI_INT, 3, TAG12, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 3, TAG12, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t3 from t4\n");

    // Надіслати в T2
    MPI_Send(&(MS[0][0]), H * 2 * N, MPI_INT, 1, TAG13, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 1, TAG13, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 1, TAG13, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 1, TAG13, graph_cart);

    printf("START CALCULATION t3\n");
    operation1(Z, D, MS, MX, e, H * 2);

    // // Прийняти A від T4
    MPI_Recv(&A[H * 3], H * 5, MPI_INT, 3, TAG12, graph_cart, MPI_STATUS_IGNORE);
    // Надіслати A в T2
    MPI_Send(&A[H*2], H * 6, MPI_INT, 1, TAG13, graph_cart);

    printf("T3 end\n");
  }
  else if (t_id == 3)
  { // T4
    printf("T4 start\n");

    // Прийняти від T3
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 2, TAG3, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 2, TAG3, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 2, TAG3, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t4 from t3\n");

    // Надіслати MX в T5
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 4, TAG4, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 4, TAG4, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 4, TAG4, graph_cart);

   // Прийняти від T5
    MPI_Recv(&(MS[0][0]), H * 4 * N, MPI_INT, 4, TAG11, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 4, TAG11, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t4 from t5\n");

    // Надіслати в T3
    MPI_Send(&(MS[0][0]), H * 3 * N, MPI_INT, 2, TAG12, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 2, TAG12, graph_cart);
    

    printf("START CALCULATION t4\n");

    operation1(Z, D, MS, MX, e, H * 3);

    // // Прийняти A від T5
    MPI_Recv(&A[H * 4], H * 4, MPI_INT, 4, TAG11, graph_cart, MPI_STATUS_IGNORE);
    // Надіслати A в T3
    MPI_Send(&A[H * 3], H * 5, MPI_INT, 2, TAG12, graph_cart);

    printf("T4 end\n");
  }
  else if (t_id == 4)
  { // T5
    printf("T5 start\n");

    // Прийняти від T6
    MPI_Recv(&(MS[0][0]), H * 5 * N, MPI_INT, 5, TAG10, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 5, TAG10, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t5 from t6\n");

    // Прийняти від T4
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 3, TAG4, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 3, TAG4, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 3, TAG4, graph_cart, MPI_STATUS_IGNORE);

    // Надіслати в T4
    MPI_Send(&(MS[0][0]), H * 4 * N, MPI_INT, 3, TAG11, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 3, TAG11, graph_cart);

    // Надіслати MX в T6
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 5, TAG5, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 5, TAG5, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 5, TAG5, graph_cart);


    printf("RECV INPUT in t5 from t4\n");

    printf("START CALCULATION t5\n");

    operation1(Z, D, MS, MX, e, H * 4);

    // Прийняти A від T6
    MPI_Recv(&A[H * 5], H * 3, MPI_INT, 5, TAG10, graph_cart, MPI_STATUS_IGNORE);
    // Надіслати A в T4
    MPI_Send(&A[H * 4], H * 4, MPI_INT, 3, TAG11, graph_cart);

    printf("T5 end\n");
  }
  else if (t_id == 5)
  { // T6
    printf("T6 start\n");
    // Прийняти від T7
    MPI_Recv(&(MS[0][0]), H * 6 * N, MPI_INT, 6, TAG9, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 6, TAG9, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t6 from t7\n");

    // Надіслати в T5
    MPI_Send(&(MS[0][0]), H * 5 * N, MPI_INT, 4, TAG10, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 4, TAG10, graph_cart);

    // Прийняти від T5
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 4, TAG5, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 4, TAG5, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 4, TAG5, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t6 from t5\n");

    // Надіслати MX в T7
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 6, TAG6, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 6, TAG6, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 6, TAG6, graph_cart);

    printf("START CALCULATION t6\n");

    operation1(Z, D, MS, MX, e, H * 5);

    // Прийняти A від T7
    MPI_Recv(&A[H * 6], H * 2, MPI_INT, 6, TAG9, graph_cart, MPI_STATUS_IGNORE);
    // Надіслати A в T5
    MPI_Send(&A[H * 5], H * 3, MPI_INT, 4, TAG10, graph_cart);

    printf("T6 end\n");
  }
  else if (t_id == 6)
  { // T7
    printf("T7 start\n");

    // Прийняти від T8
    MPI_Recv(&(MS[0][0]), H * 7 * N, MPI_INT, 7, TAG8, graph_cart, MPI_STATUS_IGNORE);
    int e;
    MPI_Recv(&e, 1, MPI_INT, 7, TAG8, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT in t7 from t8\n");

    // Надіслати в T6
    MPI_Send(&(MS[0][0]), H * 6 * N, MPI_INT, 5, TAG9, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 5, TAG9, graph_cart);

    // Прийняти від T6
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 5, TAG6, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 5, TAG6, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 5, TAG6, graph_cart, MPI_STATUS_IGNORE);

    printf("RECV INPUT t7 from t6\n");

    // Надіслати MX в T8
    MPI_Send(&(MX[0][0]), N * N, MPI_INT, 7, TAG7, graph_cart);
    MPI_Send(&Z[0], N, MPI_INT, 7, TAG7, graph_cart);
    MPI_Send(&D[0], N, MPI_INT, 7, TAG7, graph_cart);

    printf("START CALCULATION t7\n");

    operation1(Z, D, MS, MX, e, H * 6);

    // // Прийняти A від T8
    MPI_Recv(&A[H * 7], H * 1, MPI_INT, 7, TAG8, graph_cart, MPI_STATUS_IGNORE);
    // Надіслати A в T6
    MPI_Send(&A[H * 6], H * 2, MPI_INT, 5, TAG9, graph_cart);

    printf("T7 end\n");
  }
  else if (t_id == 7)
  { // T8
    printf("T8 start\n");

    // Введення MS, e
    e = INPUT;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        MS[i][j] = INPUT;
      }
    }

    // Надіслати в T7
    MPI_Send(&(MS[0][0]), H * 7 * N, MPI_INT, 6, TAG8, graph_cart);
    MPI_Send(&e, 1, MPI_INT, 6, TAG8, graph_cart);

    printf("SEND INPUT t8\n");

    // Прийняти від T7
    MPI_Recv(&(MX[0][0]), N * N, MPI_INT, 6, TAG7, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&Z[0], N, MPI_INT, 6, TAG7, graph_cart, MPI_STATUS_IGNORE);
    MPI_Recv(&D[0], N, MPI_INT, 6, TAG7, graph_cart, MPI_STATUS_IGNORE);

    printf("START CALCULATION t8\n");

    operation1(Z, D, MS, MX, e, H * 7);

    // Надіслати A в T7
    MPI_Send(&A[H * 7], H * 1, MPI_INT, 6, TAG8, graph_cart);

    printf("T8 end\n");
  }

  MPI_Finalize();
}
