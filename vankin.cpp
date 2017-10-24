#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>

using namespace std;

int_fast32_t highestScore(int8_t* array, const int_fast16_t &n, int16_t score, int16_t row, int16_t column) {
	score += array[row*column];
	if (row == 1)
		return highestScore(array, n, score, row - 1, column);
	else if (column == 1)
		return highestScore(array, n, score, row, column - 1);
	else if (row == 1 && column == 1)
		return score;
	int32_t down = highestScore(array, n, score, row - 1, column);
	int32_t right = highestScore(array, n, score, row, column - 1);
	if (down > right)
		return down;
	else
		return right;
}

int readN(){
	ifstream Input;
	Input.open("input1.txt");
	
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
} 
