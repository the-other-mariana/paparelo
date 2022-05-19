//PROBLEMA: Despertador
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
int Np = 2;
condition_variable cv;
mutex m;
bool x = false;

//HILOS: funciones
void f(int id) {                                                        p("hilo=" + to_string(id) + " -[");
  unique_lock<mutex> ul(m, defer_lock);    
  ul.lock();                                                            p("hilo=" + to_string(id) + " -[m");
    while (!x) {                                                        p("hilo=" + to_string(id) + " -[->m");
      cv.wait(ul);  /*NOTA: Poner el hilo a dormir y liberar el mutex*/	p("hilo=" + to_string(id) + " -[m");
    }
  ul.unlock();                                                          p("hilo=" + to_string(id) + " -[->m termina");
}

void g() {                                                              p(string("") + "g()" + " -[");
  m.lock();                                                             p(string("") + "g()" + " -[m");
    x = true;
    cv.notify_all();                                                    p("g() -[m notifica");
    //cv.notify_one();
  m.unlock();                                                           p(string("") + "g()" + " -[->m");
}

int main () {
  //HILOS: creación
  thread Vh[Np];
  for (int i=0; i<Np; ++i) {
    Vh[i] = thread(f, i);                                               p("hilo="+to_string(i)+" -> Inicio");
  }

  this_thread::sleep_for(chrono::seconds(5));
  g();

  //HILOS: unir
  for (int i=0; i<Np; i++) {
    Vh[i].join();                                                       p("hilo="+to_string(i)+" <- Join()");
  }

  return 0;
}
