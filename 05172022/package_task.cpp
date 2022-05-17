#include<iostream>
#include<thread>
#include<future>

using namespace std;

int f(int x){
	return 2*x;
}

int main(){
	int x = 2;
	// signature of the function: int(int)
	packaged_task<int(int)> t(f);
	future<int> fu = t.get_future();
	thread h = thread(move(t), x);
	// the thread is created and starts to execute here
	
	int v = fu.get(); // here the main thread waits for the value
	h.join();
	cout << "v = " << v << endl;
	return 0;
}
