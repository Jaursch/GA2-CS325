#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int readN(){
	ifstream Input;
	Input.open("input1.txt");
	
	char c;
	Input.get(c);

	int n = c - '0'; 

	Input.close();
	return n;		
}

void readOut(int maxScore){
	ofstream Output;
	Output.open("output.txt");
	if(Output.is_open() ){
		Output << maxScore;
	}else{
		cout << "not open" << endl; 
	} 	
} 

int main(){
	int n = readN() ; //amount of elements in array
	int maxScore = 0;
	cout << n << endl;
	
	int** Data = new int*[n];
	for(int i = 0; i<n; i++){
		Data[i] = new int[n];
	}

	//attempting to read e/ number
	ifstream Input;
	Input.open("input1.txt");
       	char c[4];
	Input.ignore(256, '\n'); //ignores till second line  
	for(int j=0; j<n; j++){
		for(int i = 0; i<n-1; i++){ //gets all but last ele.
			Input.getline(c, 256, ',');
			Data[j][i] = atoi(c);	
		}Input.getline(c, 10, '\n'); //get last ele.
      		Data[j][n-1] = atoi(c); 
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << Data[i][j] << endl;
		} 
	}

	readOut(maxScore); 	
} 
