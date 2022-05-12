#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

// program that uses mutex blocks for 2 threads and 1 variable

// must be one object
mutex m;
int x;

void f(){
	// make each thread try to modify x 100 times
	for (int i=0; i < 10000; i++) {
		// block the critical section
		m.lock(); // the1st thread grabs the mutex, and the other will wait until mutex is available
			// critical section
			x = x + 1;
		m.unlock(); // releases mutex, and the other thread that is waiting grabs it
	}
}

int main(){
	x = 0;
	thread h1 = thread(f);
	thread h2 = thread(f);
	
	// wait for threads to finish f()
	h1.join();
	h2.join();
	
	// we expect x=20000, w/o mutex will be less
	cout << "x=" << x << endl;
	
	return 0;
}
