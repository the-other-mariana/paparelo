#include<iostream>
#include<thread>
#include<future>

using namespace std;

int f(int x){
	return 2*x;
}

int main(){
	int x = 2;
	future<int> fu = async(launch::async, f, x);
	int v = fu.get();
	cout << "v = " << v << endl;
	return 0;
}
