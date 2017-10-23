#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	int_fast16_t n; //The size of the grid
	int_fast32_t highestScore; //The highest possible score
	char filePath[100]; //A cstring to hold the path to the file
	FILE * filePointer; //A simple pointer to  keep track of the file

						//If the user doesn't supply the file path as an initial parameter
	if (argc < 2) {
		filePointer = fopen(argv[1], "r");
		//If the provided file path is invalid
		if (filePointer == NULL) {
			printf("Please enter the name of your input file\n");
			cin >> filePath;
		}
		filePointer = fopen(filePath, "r");
	}
	else //If the user supplies the file path as an initial parameter
		filePointer = fopen(argv[1], "r");
	//If the user entered a bad file path
	while (filePointer == NULL) {
		//Print this with & the error to the error stream (means this will show up no matter what)
		//A newrow is automatically appended to whatever perror prints (so \n is unnecessary)
		perror("Please re-enter the name of your input file");
		cin >> filePath;
		filePointer = fopen(filePath, "r");
	}
	//Seek to the beginning of the file as fopen() is glitchy
	fseek(filePointer, 0, SEEK_SET);

	const int_fast8_t bufferSize = 30; //Size of buffer
	char buffer[bufferSize]; //Used to read in the first row of the file, which should contain n

							 //Make sure buffer contains no garbage
	memset(buffer, '\0', bufferSize);

	//Read the first row of the file & check that fgets() actually returns that as a cstring
	if (fgets(buffer, bufferSize, filePointer) == NULL) {
		//Print the file path with the error to the error stream (means this will display no matter what)
		if (filePath[0] = '\0') //If the file path was provided as an argument
			perror(argv[1]);
		else //If the user had to enter the file path later
			perror(filePath);
		//Exit/crash the program on this error
		return -1;
	}
	//Convert the cstring to an integer n
	n = atoi(buffer);
	//Make sure n is within the acceptable range
	if (n < 1 || n > 1000) {
		//Print the error, & n to the error stream (means this will display no matter what)
		fprintf(stderr, "Invalid matrix size: %d\n", n);
		//Exit/crash the program on this error
		return n;
	}
	
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

