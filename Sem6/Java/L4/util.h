#ifndef UTIL_H
#define UTIL_H


#include <string>


namespace util
{
  int *fillVec(int);
  int **fillMtx(int, int);
  int setScalar();
  std::string str(int *, int);


  int* Calculation1(int, int*, int**);
  int Max(int, int*);
  int MaxFinal(int, int);
}


#endif // UTIL_H


