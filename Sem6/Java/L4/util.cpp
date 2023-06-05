#include "util.h"
#include "lab4.h"


int *util::fillVec(int size)
{
  int *v = new int[size];
  for (int i = 0; i < size; ++i)
    v[i] = 1;
  return v;
}


int **util::fillMtx(int rows, int cols)
{
  int **m = new int *[rows];
  for (int r = 0; r < rows; ++r)
    m[r] = fillVec(cols);
  return m;
}


int util::setScalar() { return 1; }


std::string util::str(int *matrix, int rows)
{
  std::string s = "[";
  for (int r = 0; r < rows; ++r)
  {
    s.append(" ").append(std::to_string(matrix[r])).append(" ");
  }
  s.append("]");
  return s;
}


int *util::Calculation1(int start, int *C, int **MD)
{
  int end = start + H;
  int *result = new int[N];
  #pragma for
  for (int i = start; i < end; i++) {
    int part = 0;
    for (int j = 0; j < N; j++) {
      part += C[j] * MD[i][j];
    }
    result[i] = part;
  }
  return result;
}

int util::Max(int start, int *Z)
{
  int end = start + H;
  int result;
  #pragma for
  for (int i = start; i < end; i++) {
    if (Z[i] > result)
    {
      result = Z[i];
    }
  }
  return result;
}

int util::MaxFinal(int z, int purport)
{
  if (z > purport) return z;
  else return purport;
}
