#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

using namespace std;

// program that uses mutex blocks for thread vector and 1 variable

// must be one object
mutex m;
int x;

void f(){
	// make each thread try to modify x 100 times
	for (int i=0; i < 100000; i++) {
		m.lock();
			x = x + 1;
		m.unlock();
	}
}

int main(){
	x = 0;
	int num_th = 10;
	vector<thread> vh;
	for (int h = 0; h < num_th; h++) {
		vh.push_back(thread(f)); // create a thread, execute f and push it
	}
	
	// wait for threads to finish f()
	for (int h = 0; h < num_th; h++) {
		vh[h].join();
	} 
	
	// we expect x=100000*num_th, w/o mutex will be less
	cout << "x=" << x << endl;
	
	return 0;
}
