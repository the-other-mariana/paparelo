#include <iostream>
#include <cstdint>
#include <thread>
#include "hpc_helpers.hpp"

using namespace std;

struct S {
	int x;
	int y;
};

int N = 1<<30;
volatile S s;
	
void f() {
	for (int i=0; i<N; i++) {
		s.x++;
		s.y++;
	}
}

void f1() {
	for (int i=0; i<N; i++) {
		s.x++;                               //Asignación directa en s.x provoca False Sharing
	}
}

void f2() {
	for (int i=0; i<N; i++) {
		s.y++;                               //Asignación directa en s.y provoca False Sharing
	}
}

void f3() {
	int tmp = s.x;                         //Uso de variable temporal tmp para evitar False Sharing
	for (int i=0; i<N; i++) {
		tmp++;
	}
	s.x = tmp;
}

void f4() {
  int tmp = s.x;                         //Uso de variable temporal tmp para evitar False Sharing
	for (int i=0; i<N; i++) {
		tmp++;
	}
  s.x = tmp;
}

int main() {
  TIMERSTART(1_procesador)
    s.x = 0;
    s.y = 0;
    f();
  TIMERSTOP(1_procesador)

  TIMERSTART(np_procesador_ConFalseSharing)
    s.x = 0;
    s.y = 0;
    thread h1 = thread(f1);
    thread h2 = thread(f2);
    h1.join();
    h2.join();
  TIMERSTOP(np_procesador_ConFalseSharing)
  
  TIMERSTART(np_procesador_SinFalseSharing)
    //FALSE SHARING: se evita usando variables temporales
    s.x = 0;
    s.y = 0;
    thread h3 = thread(f3);
    thread h4 = thread(f4);
    h3.join();
    h4.join();
  TIMERSTOP(np_procesador_SinFalseSharing)

  return 0;
}
