/*
ПЗ ВПКС
Лабораторна робота 4, Варіант 3
Завдання:
A = max(C*MD) * E*(MA*MB)*d + x*C
T1 = E, d
T2 = MB
T3 = C,MA,A, x
T4 = MD

Маковій Віктор ІП-05
Дата 09.05.2023
*/

#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <limits>

#include "lab4.h"
#include "util.cpp"

using namespace std;

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char *argv[])
{
  std::cout << "-- Start" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  int threadId;

  int d, z, x;
  int *E, *C, *Z, *A;
  int **MB, **MA, **MD;
  z = INT_MIN;


  int *Zh1, *Zh2, *Zh3, *Zh4;
  int z1, z2, z3, z4;

  int copy_z, copy_d, copy_x;
  int *copy_C;
  int **copy_MA;

  A = new int[N];
  Z = new int[N];
  int part = 0;


  omp_set_num_threads(4);


  #pragma omp parallel default(shared) private(threadId, copy_C, copy_z, copy_d, copy_x, copy_MA, part)
  {
    threadId = omp_get_thread_num();


    #pragma omp critical(io)
    std::cout << "Thread " << threadId << " started" << std::endl;


    // Input
    switch (threadId)
    {
      case 0:
        // Input E, d
        E = util::fillVec(N);
        d = util::setScalar();
        break;
      case 1:
        // Input MB
        MB = util::fillMtx(N, N);
        break;
      case 2:
        // Input C,MA
        C = util::fillVec(N);
        MA = util::fillMtx(N, N);
        x = util::setScalar();
        break;
      case 3:
        // Input MD
        MD = util::fillMtx(N, N);
        break;
      default:
        break; // noop
    }

    #pragma omp barrier // Очікування на завершення вводу даних


    #pragma omp critical(CS1) // КД1 - Копіювання C
    {
      copy_C = C;
    }

    // Обчислення 1-3  Zh = C*MDh
    switch (threadId)
    {
      case 0:
        Zh1 = util::Calculation1(0, copy_C, MD);  // Обчислення 1
        z1 = util::Max(0, Zh1);  // Обчислення 2
        #pragma omp critical(CS2) // КД2 - max
        {
          z = util::MaxFinal(z, z1);  // Обчислення 3
        }
        break;
      case 1:
        Zh2 = util::Calculation1(H, copy_C, MD);  // Обчислення 1
        z2 = util::Max(H, Zh2);  // Обчислення 2  
        #pragma omp critical(CS2) // КД2 - max
        {
          z = util::MaxFinal(z, z2);  // Обчислення 3
        }
        break;
      case 2:
        Zh3 = util::Calculation1(H * 2, copy_C, MD);  // Обчислення 1
        z3 = util::Max(H * 2, Zh3);  // Обчислення 2
        #pragma omp critical(CS2) // КД2 - max
        {
          z = util::MaxFinal(z, z3);  // Обчислення 3
        }
        break;
      case 3:
        Zh4 = util::Calculation1(H * 3, copy_C, MD);  // Обчислення 1
        z4 = util::Max(H * 3, Zh4);  // Обчислення 2
        #pragma omp critical(CS2) // КД2 - max
        {
          z = util::MaxFinal(z, z4);  // Обчислення 3
        }
        break;
      default:
        break; // noop
    }

    #pragma omp barrier

    #pragma omp critical(CS3) // CS3 - Копіювання z
    {
      copy_z = z;
    }
    #pragma omp critical(CS4) // CS3 - Копіювання MA
    {
      copy_MA = MA;
    }
    #pragma omp critical(CS5) // CS3 - Копіювання d
    {
      copy_d = d;
    }
    #pragma omp critical(CS6) // CS3 - Копіювання x
    {
      copy_x = x;
    }


    // Обчислення 4  Ah = z*E*(MA*MBh)*d + x*Ch
    #pragma omp for
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        part = 0;
        for (int k = 0; k < N; k++)
        {
          part += copy_z * E[j] * (copy_MA[i][j] * MB[i][j]) * copy_d;
        }
      }
      A[i] = copy_x * C[i] + part;
    }
    


    #pragma omp barrier // Очікування обчислення A


    if (threadId == 3)
    {
      #pragma omp critical(io)
      {
        if (N == 4)
        {
          std::cout << util::str(A, N) << std::endl;
        }
        std::cout << "N = " << N << std::endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Time of calculation: " << duration.count() << std::endl;
      }
    }

    #pragma omp critical(io)
    {
      std::cout << "Thread " << threadId << " finished" << std::endl;
    }
  }

  for (int i = 0; i < N; ++i)
  {
    delete[] MB[i];
    delete[] MA[i];
    delete[] MD[i];
  }
  delete[] Z;
  delete[] C;
  delete[] E;
  delete[] A;
  delete[] MB;
  delete[] MA;
  delete[] MD;


  std::cout << "-- Finish" << std::endl;
}
