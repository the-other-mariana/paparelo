#include<iostream>
using namespace std;

// program that showcases anonymous functions (often used in threads) (GNU C++11)

int main(){
	int a = 10;
	int b = 20; 
	cout << "b=" << b << endl; // 20
	//auto f = [&](int x){} // see/modify a and b by reference
	//auto f = [=](int x){} // see/modify a and b by value
	//auto f = [a](int x){ return b;} // only see/mod a by value (error, no b)
	// definition of a function (NOT excution)
	auto f = [&](int x)->int{
		// if we modify it, coming back from f, b will be changed (reference)
		b = 30;
		return b;
	};
	cout << "f(2)=" << f(2) << endl; // 30 // this IS the execution
	cout << "b=" << b << endl; // 30
	return 0;
}
