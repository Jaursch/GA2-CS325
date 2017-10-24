#include <cstdint>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
//#include <fstream>
using namespace std;

/*The &n means n will be passed by reference,
which means the same memory address will be used for n for each call of highestBranch.
highestBranch() will be called recursively many times,
so this should save some memory on the stack & help prevent a stack overflow.*/
int_fast16_t highest(char* filePath, FILE * filePointer, const int_fast16_t &n);
//filerow can't be passed by reference as it will be modified in each call of highestBranch()
//highestBranch() will be called by highest() & it will recurse on itself many times
int_fast16_t highestBranch(FILE * filePointer, const int_fast16_t &n, int16_t score, int16_t row, int16_t column);

int main(int argc, char *argv[]) {
	int_fast16_t n; //The size of the grid
	int_fast32_t highestScore; //The highest possible score
	char filePath[100]; //A cstring to hold the path to the file
	FILE * filePointer; //A simple pointer to  keep track of the file
		
	//If the user doesn't supply the file path as an initial parameter
	if (argc < 2) {
		puts("Please enter the name of your input file");
		cin >> filePath;
	}
	else //If the user supplies the file path as an initial parameter
		strcpy(filePath, argv[1]);
	filePointer = fopen(filePath, "r");
	//If the user entered a bad file path
	while (filePointer == NULL) {
		memset(filePath, '\0', sizeof(filePath));
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
	printf(filePath);
	//Read the first row of the file & check that fgets() actually returns that as a cstring
	if (fgets(buffer, bufferSize, filePointer) == NULL) {
		//Print the file path with the error to the error stream (means this will display no matter what)
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
	highest(filePath, filePointer, n);

	fclose(filePointer);

	return 0;
}

int_fast32_t highest(char* filePath, FILE * filePointer, const int_fast16_t &n) {
	const int_fast8_t bufferSize = 10; //Size of buffer
	char buffer[bufferSize]; //Used to read in a number from the bottom or rightmost border of the file
	int_fast8_t score;
	//Itterate down the rows
	for (int_fast16_t rowNumber = 1; rowNumber < n; rowNumber++) {
		//Assume the file pointer is already on the correct row
		//Loop to the last number on the first row of n numbers
		for (int_fast16_t i = 1; i < n;) {
			//Itterate by n-1 commas
			if (fgetc(filePointer) == ',') i++;
		}
		if (fscanf(filePointer, "%i", &score) < 1){
			//Print the file path with the error to the error stream (means this will display no matter what)
			fprintf(stderr, "Error reading border of file. Score: %i\n", score);
			//Exit/crash the program on this error
			return -1;
		}
		//Create a new file pointer & duplicate the first file pointer into it every time
		FILE *filePointer2 = fopen(filePath, "r");
		fpos_t position;
		if (fgetpos(filePointer, &position) == 0)
			fsetpos(filePointer2, &position);
		//highestBranch(filePointer2, n, score, rowNumber, n);
	}
	//Itterate down the columns of the last row
	for (int_fast16_t columnNumber = 0; columnNumber < n; columnNumber++) {
		if (fscanf(filePointer, "%i", &score) < 1) {
			//Print the file path with the error to the error stream (means this will display no matter what)
			fprintf(stderr, "Error reading border of file. Score: %i\n", score);
			//Exit/crash the program on this error
			return -1;
		}
		//Throw away the next comma
		fgetc(filePointer);
		//Create a new file pointer & duplicate the first file pointer into it every time
		FILE *filePointer2 = fopen(filePath, "r");
		fpos_t position;
		if (fgetpos(filePointer, &position) == 0)
			fsetpos(filePointer2, &position);
		//highestBranch(filePointer2, n, score, n, columnNumber);
	}
}
int_fast16_t highestBranch(FILE * filePointer, const int_fast16_t &n, int16_t score, int16_t row, int16_t column) {
	if (score < -1000)
		return INT16_MIN;

	//else
	//highestBranch
}