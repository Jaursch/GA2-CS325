#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>

using namespace std;

int_fast32_t highestScore(int** array, const int_fast16_t &n, int16_t score, int16_t row, int16_t column) {
	score += array[row][column];
	if (row == 0)
		return highestScore(array, n, score, row - 1, column);
	else if (column == 0)
		return highestScore(array, n, score, row, column - 1);
	else if (row == 0 && column == 0)
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

	//Call highestScore() 2n-1 times for each index along the bottom/right edge of the array
	int_fast32_t score = 0;
	for (int_fast32_t rowNumber = 0, temp; rowNumber <= n; rowNumber++) {
		temp = highestScore(Data, n, 0, rowNumber, n-1);
		if (temp > score)
			temp = score;
	}
	for (int_fast32_t columnNumber = 0, temp; columnNumber <= n; columnNumber++) {
		temp = highestScore(Data, n, 0, n - 1, columnNumber);
		if (temp > score)
			temp = score;
	}
	
	readOut(maxScore);
} 
