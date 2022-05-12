#include<iostream>
#include<mutex>
#include<thread>
#include<vector>
#include<future>

using namespace std;

// program that uses future promise

// must be one object
mutex mcout;
mutex m;

void prints(string s){
	mcout.lock();
		cout << s << endl;
	mcout.unlock();
}

// promise objects must be passed as r values
void f(promise<int> &&p){
	p.set_value(10); // put it in promise, future grabs it
}

int main(){
	promise<int> p;
	future<int> fu = p.get_future();
	thread h = thread(f,move(p));
	// main thread waits for value from the future: SYNCHRONIZATION
	int v = fu.get();
	prints("v=" + to_string(v));
	// wait for h to finish f
	h.join();
	return 0;
}
