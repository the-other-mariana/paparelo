#include<iostream>
using namespace std;

// program that showcases how c++11 allows object creation by value or by reference (GNU C++11)
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
	
	// copy constructor 1 (reference param/pass by reference to object), const may or may not be there
	// not allowed A(A a){}
	// constructor by reference to l-value
	A(const A &a){
		this->x = a.x;
		cout << "A(const A &a)" << endl;
	}
	
	// copy constructor 2: receives pointer (l-value) to object
	A(A *a){
		this->x = a->x;
		cout << "A(A *a)" << endl;
	}
	
	// copy constructor 3
	// constructor by reference to v-value
	A(A &&a){
		this->x = a.x;
		cout << "A(A &&a)" << endl;
	}
	
	p(){
		cout << "x=" << x << endl;
	}
};

// pass an object by value
void f(A a){
	a.p();
	cout << "f(A a)" << endl;
}

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
	
	A a2 = A(2);
	A b2 = a2; // calls A(const A &a)
	f(a2); // calls A(const A &a) again (an object is sent, not a pointer)
	f(move(a)); // calls A(A &&a)
	
	return 0;
}
