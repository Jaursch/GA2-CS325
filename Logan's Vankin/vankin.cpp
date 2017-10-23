#include <cstdint>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
//#include <fstream>
using namespace std;

//namespace std {
	/*The &n means n will be passed by reference,
	which means the same memory address will be used for n for each call of highestBranch.
	highestBranch() will be called recursively many times,
	so this should save some memory on the stack & help prevent a stack overflow.*/
	int_fast16_t highest(FILE * filePointer, const int_fast16_t &n);
	//filerow can't be passed by reference as it will be modified in each call of highestBranch()
	//highestBranch() will be called by highest() & it will recurse on itself many times
	//int_fast16_t highestBranch(FILE * filePointer, const int_fast16_t &n, int16_t score, int16_t row, int16_t column);

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

		//This is supposed to duplicate the first file pointer, but it's not working properly for some reason
		FILE *filePointer2  = fdopen(dup(fileno(filePointer)), "r");

		//FILE* filepointer2 = (FILE*)malloc(sizeof(filePointer));
		//memcpy(filePointer, filepointer2, sizeof(filePointer));
		//memset(buffer, '\0', bufferSize);
		printf("File Pointer 1: %s \t File Pointer 2: %s\n", fgets(buffer, bufferSize/2, filePointer), fgets(buffer, bufferSize/2, filePointer2));

		fclose(filePointer);

		return 0;
	}

	/*int_fast32_t highest(FILE * filePointer, const int_fast16_t &n) {
		const int_fast8_t bufferSize = 10; //Size of buffer
		char buffer[bufferSize]; //Used to read in a number from the bottom or rightmost border of the file
		//Itterate down the rows
		for (int16_t rowNumber = 1; rowNumber < n; rowNumber++) {
			//Make sure buffer contains no garbage
			memset(buffer, '\0', bufferSize);
			//This is an int because fgetc() can return an integer to signify EOF
			int_fast32_t charBuffer; //Used to read in characters
			//Assume the file pointer is already on the correct row
			//Loop to the last number on the first row of n numbers
			for (int_fast16_t i = 1; i < n;) {
				charBuffer = fgetc(filePointer);
				//Itterate by n-1 commas
				if (charBuffer == ',') i++;
			}
			if (fgets(buffer, bufferSize - 1, filePointer) == NULL) {
				//Print the file path with the error to the error stream (means this will display no matter what)
				fprintf(stderr, "");
				//Exit/crash the program on this error
				return -1;
			}
			highestBranch(filePointer, n, atoi(buffer), rowNumber, n);
		}
	}*/

//}