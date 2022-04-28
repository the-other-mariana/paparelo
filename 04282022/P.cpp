// code that shows the different ways to pass by reference using r-value concept

#include<iostream>
using namespace std;

// pass by value: pass a copy of the value as a new x var
// receives either l-values or r-values
int f(int x){
	x = 3;
	cout << "f(int x)" << endl;
	return 2*x;
}

// pass by reference: a local parameter is not being created
int f2(int &y){
	y = 3; // modify the space in memory called x
	cout << "f(int &y)" << endl;
	return 2*y;
}

// pass by reference: now with a pointer
int f(int *x){
	*x = 3;
	cout << "f(int *x)" << endl;
	return 2*(*x);
}

// pass by reference
int f3(int &&x){
	x = 3;
	cout << "f(int &&x)" << endl;
	return 2*x;
}

int main(){
	int x = 2; // l-value: x, r-value: 2
	int *p = &x;
	int &r = x; // it is a reference to x, an alias // r is not a variable, cannot &r = 2;
	int &&v = move(x); // v in itself is an l value: move(x) references to x's value 2 (constant)
	int &&v2 = 2;
	//int &&v3 = x; // error: x is not an r value // v and x are l-value but cannot be assigned
	
	cout << "==========" << endl;
	int y = f(x); 
	cout << "f(x)=" << y << endl; // 6
	cout << "x=" << x << endl; // 2
	
	cout << "==========" << endl;
	int y2 = f2(x);
	cout << "f2(x)=" << y2 << endl; // 6
	cout << "x=" << x << endl; // 3
	
	cout << "==========" << endl;
	int y3 = f(p);
	cout << "f(p)=" << y3 << endl; // 6
	cout << "x=" << x << endl; // 3
	
	cout << "==========" << endl;
	int y4 = f(v); // will enter f(int x) since v is an l value
	int y5 = f3(move(x)); // error: f(int x) and f(int &&x) can both receive an r-value, thus call it f3
	cout << "f(move(x))=" << y5 << endl; // 6
	cout << "x=" << x << endl; // 3
	
	// had we f(int &x) and f(int &&x): f(x) enters f(int &x), f(move(x)) enters f(int &&x)
	
	
	return 0;
}
