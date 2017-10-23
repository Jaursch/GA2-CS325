#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int readN(){
	ifstream Input;
	Input.open("input.txt");
	
	char c;
	Input.get(c);

	cout << c << endl;
	int n = c - '0'; 

	Input.close();
	return n;		
} 

int main(){
	int n = readN() ; //amount of elements in array
	cout << n << endl;

} 

