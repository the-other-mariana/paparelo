#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

using namespace std;

// program that uses lock_guard blocks for thread vector and 1 variable

// must be one object
mutex m;
int x;

void f(){
	// make each thread try to modify x 100 times
	for (int i=0; i < 10000; i++) {
		{ lock_guard<mutex> lg(m); // grabs the mutex here or waits in this line until available
			x = x + 1;
		}// releases mutex m in each iteration
	}
}

int main(){
	x = 0;
	vector<thread> vh;
	thread h1 = thread(f);
	thread h2 = thread(f);
	
	// wait for threads to finish f()
	h1.join();
	h2.join();
	
	// we expect x=20000, w/o mutex will be less
	cout << "x=" << x << endl;
	
	return 0;
}
