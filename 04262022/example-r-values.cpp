#include<iostream>
using namespace std;

int f(int x){
	return 2*x;
}

int main(){
	int x = 2;
	cout << "x (l value): " << x << endl;
	
	// this is an error, and we cant access 2 mem address: r value
	//cout << "&2 (r value): " << &2 << endl; 
	// this is an error, the function itself is an r value
	//cout << "f(x): " << &f(x) << endl; 
	
	int &&v = 5; // ref to r value (2 doesnt have a mem address) 
	// (2 is the r value, v is an l value)
	cout << "v (l value), 5 (r value): " << v << endl; // 5
	cout << "&v (l value): " << &v << endl; // v mem address
	
	//int &&v2 = x; // error: x is an l value, the way you can do this, is using move(x)
	// move(x) accesses the r value to which x points to
	int &&v2 = move(x); 
	//both v2 and x point to the mem space where 2 is (same mem address)
	cout << "&v2: " << &v2 << endl; // 0x6ffdf8
	cout << "&x: " << &x << endl; // 0x6ffdf8
	
	x = 11;
	cout << "v2: " << v2 << endl; // 11
	
	// references to an l-value
	int &r = x;
	cout << &r << endl; // 0x6ffdf8
	//int &&v3 = r; error: r is like x, a name to the same mem space
	
	return 0;
}
