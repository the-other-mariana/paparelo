#include<iostream>
using namespace std;

class A {
	public:
		int x;
		
	// main constructor
	A(){
		cout << "A()" << endl;
		this->x = 0;
	}
	
	A(int x){
		cout << "A(int x)" << endl;
		this->x = x; // local parameter x = global x
	}
	
	p(){
		cout << "x=" << x << endl;
	}
};

int main(){
	
	// create an object by value
	A a = A(2); // () calls main constructor
	// A a(); // other way
	A b = a; // a copy of object a
	a.p(); // 2
	b.p(); // 2
	a.x = 10;
	a.p(); // 10 // 
	b.p(); // 2
	
	// create an object by reference
	A *ar = new A(4); // () calls main constructor
	A *br = ar; // br and ar point to the same object
	ar->p(); // -> is for pointers, . is for variables // 4
	br->p(); // 4
	ar->x = 10;
	ar->p(); // 10
	br->p(); // 10
	
	return 0;
}
