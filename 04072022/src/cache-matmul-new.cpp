#include <iostream>
#include <cstdint>
#include <vector>
#include "hpc_helpers.hpp"

using namespace std;

int main() {

  int n = 1<<13;  //=2^10
  
  TIMERSTART(Inicializacion)
    vector<float> A(n*n);     // A(n x n)
    vector<float> Y(n);       // Y(n x 1) = Matriz columna
    vector<float> X(n);       // X(n x 1) = Matriz columna
  TIMERSTOP(Inicializacion)

  TIMERSTART(AxX)  
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
        Y[i] = A[i*n+j]*X[j];
      }
    }
  TIMERSTOP(AxX)
    
  TIMERSTART(AxX_2)  
    for (int j=0; j<n; j++) {
 	    for (int i=0; i<n; i++) {
        Y[i] = A[i*n+j]*X[j];
      }
    }
  TIMERSTOP(AxX_2)
  
  return 0;
}
