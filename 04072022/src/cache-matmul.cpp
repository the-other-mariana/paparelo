#include <iostream>
#include <cstdint>
#include <vector>
#include "hpc_helpers.hpp"

using namespace std;

// 04072022: program that multiplies 2 matrices: x times y

int main() {

  int n = 1<<10;  //=2^10 // 1 in binary but carried 10 places to the left: 2^10
  int m = 1<<10;  //=2^10
  int l = 1<<10;  //=2^10

  // measure how long it taks to generate these matrices:
  TIMERSTART(Inicializacion)
    vector<float>  A(n*l);     // matrix A = A(n x l) in 1D vector form, since RAM will transform everything to 1D arrays // r x c
    vector<float>  B(l*m);     // B(l x m)
    vector<float> Bt(m*l);     // Bt(m x l) = B transposed
    vector<float>  C(n*m);     // C(n x m) = stores A x B result
  TIMERSTOP(Inicializacion)

  // 1st experiment: AxB
  TIMERSTART(AxB)
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        float x = 0;
        for (int k=0; k<l; k++) {
 		  	  x = x + A[i*l+k]*B[k*m+j]; // index transformation: from mtx to line coordinates
 	  	  }
        C[i*m+j] = x; // save result of the cell into C: C is another linear vector
      }
    }
  TIMERSTOP(AxB)
	
  // solution: AxBt, to reduce the amount of copied blocks to cache = less RAM access
  TIMERSTART(Bt_AxBt)
    // calculate B transposed
    TIMERSTART(Bt)
    for (int i=0; i<l; i++) {
      for (int j=0; j<m; j++) {
        Bt[j*l+i] = B[i*m+j];
      }
    }
    TIMERSTOP(Bt)
    // calculate AxBt
    TIMERSTART(AxBt)
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        float x = 0;
        for (int k=0; k<l; k++) {
          x = x + A[i*l+k]*Bt[j*l+k];
        }
        C[i*m+j] = x;
      }
    }
    TIMERSTOP(AxBt)
  TIMERSTOP(Bt_AxBt)
  
  return 0;
}
