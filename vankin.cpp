#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int readN(){
	ifstream Input;
	Input.open("input.txt");
	
	char c;
	Input.get(c);

	int n = c - '0'; 

	Input.close();
	return n;		
} 

int main(){
	int n = readN() ; //amount of elements in array
	cout << n << endl;
	
	int** Data = new int*[n];
	for(int i = 0; i<n; i++){
		Data[i] = new int[n];
	}

	//attempting to read e/ number
	ifstream Input;
	Input.open("input.txt");
       	char c[4];
	Input.ignore(256, '\n'); 
	for(int i=0; i<n; i++){
		Input.getline(c, 256, ',');
		cout << c << endl;   	
	} 
	//cout << c << endl;	

} 

