#include<iostream>
#include<thread>
using namespace std;

// program that showcases threads (GNU C++11)

void f(int x){
	cout << "f(int x)" << endl;
}

int main(){
	int x = 2;
	// thread by union
	thread h = thread(f,x);
	h.join(); // wait until h finishes f in order to continue (finish the program)
	cout << "main() continues after f() finishes" << endl;
	
	// thread by separation
	thread h2 = thread(f,x);
	h2.detach(); // with this, we dont know if f() print will happen before or after main2() print
	cout << "main2()" << endl;
}
