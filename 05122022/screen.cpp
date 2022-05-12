#include<iostream>
#include<mutex>
#include<thread>
#include<vector>

using namespace std;

// program that uses mutex blocks for thread vector and 1 variable

// must be one object
mutex mcout;
mutex m;
int x;

void p(string s){
	// screen is a shared resource: we need block
	mcout.lock();
		cout << s << endl; // we still cannot control which thread arrives first
	mcout.unlock();
}

void f(int h){
	p("thread=" + to_string(h));
}

int main(){
	x = 0;
	int num_th = 10;
	vector<thread> vh;
	for (int h = 0; h < num_th; h++) {
		vh.push_back(thread(f, h)); // create a thread, execute f and push it
	}
	
	// wait for threads to finish f()
	for (int h = 0; h < num_th; h++) {
		vh[h].join();
	} 
	
	return 0;
}
