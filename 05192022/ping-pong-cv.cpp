//PROBLEMA: Ping Pong
//TIPO: Paralelo
//METODO: Sincronización: Variable de Condición

#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

using namespace std;

//CONSOLA: imprimir
mutex mCout;

void p(string s) {
  mCout.lock();
    cout << s << endl;
  mCout.unlock();	
}

//MEMORIA: compartida
int Np=2;
int N =2;
condition_variable cv;
mutex m;
int x = 0;

//HILOS: funciones
void fa(int id) {                                                         p("hilo=" + to_string(id) + " -[");
  unique_lock<mutex> ul(m, defer_lock);    
  for (int i=0; i<N; i++) {
    ul.lock();                                                            p("hilo=" + to_string(id) + " -[m");
      while (x==0) {                                                      p("hilo=" + to_string(id) + " -[->m");
        cv.wait(ul);  /*NOTA: Poner el hilo a dormir y liberar el mutex*/ p("hilo=" + to_string(id) + " -[m");
      }
      x = 0;                                                              p("hilo=" + to_string(id) + " -[m         -[->o   ]-");
      cv.notify_all();
    ul.unlock();                                                          p("hilo=" + to_string(id) + " -[->m");
  }                                                                       p("hilo=" + to_string(id) + " -[->m termina");
}

void fb(int id) {                                                         p("hilo=" + to_string(id) + " -[");
  unique_lock<mutex> ul(m, defer_lock);    
  for (int i=0; i<N; i++) {
    ul.lock();                                                            p("hilo=" + to_string(id) + " -[m");
      while (x==1) {                                                      p("hilo=" + to_string(id) + " -[->m");
        cv.wait(ul);  /*NOTA: Poner el hilo a dormir y liberar el mutex*/ p("hilo=" + to_string(id) + " -[m");
      }
      x = 1;                                                              p("hilo=" + to_string(id) + " -[m         -[   o<-]-");
      cv.notify_all();
    ul.unlock();                                                          p("hilo=" + to_string(id) + " -[->m");
  }                                                                       p("hilo=" + to_string(id) + " -[->m termina");
}

int main () {                                                             p("x=0         hilo=0 -[     o]- hilo=1");
  //HILOS: creación
  thread Vh[Np];
  Vh[0] = thread(fa, 0);                                                  p("hilo="+to_string(0)+" -> Inicio");
  Vh[1] = thread(fb, 1);                                                  p("hilo="+to_string(1)+" -> Inicio");
  
  //HILOS: unir
  for (int i=0; i<Np; i++) {
    Vh[i].join();                                                         p("hilo="+to_string(i)+" <- Join()");
  }

  return 0;
}
