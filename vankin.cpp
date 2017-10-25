#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;


int32_t ** buildArray(FILE * filePointer, const int_fast16_t n);
int_fast32_t findHighest(int32_t** array, const int_fast16_t &n);

int main() {

	int_fast16_t n; //The size of the grid
	int_fast32_t score = INT32_MIN; //The highest possible score
	FILE * filePointer = fopen("input.txt", "r"); //A simple pointer to  keep track of the file
	
	//Seek to the beginning of the file as fopen() is glitchy
	fseek(filePointer, 0, SEEK_SET);
	
	if (fscanf(filePointer, "%i", &n) < 1) {
		//Print the file path with the error to the error stream (means this will display no matter what)
		fprintf(stderr, "Error reading n from file. n: %i\n", n);
		//Exit/crash the program on this error
		return n;
	}

	//Throw away the next newline
	fgetc(filePointer);

	//Make sure n is within the acceptable range
	if (n < 1 || n > 1000) {
		//Print the error, & n to the error stream (means this will display no matter what)
		fprintf(stderr, "Invalid matrix size: %d\n", n);
		//Exit/crash the program on this error
		return n;
	}
	int32_t** array = buildArray(filePointer, n);

	fclose(filePointer);

	score = findHighest(array, n);

	filePointer = fopen("output.txt", "w");
	
	fprintf(filePointer, "%i\n", score);

	fclose(filePointer);

	return 0;
}

int32_t** buildArray(FILE * filePointer, const int_fast16_t n) {
	int32_t **arr = (int32_t**)malloc(sizeof(int32_t*) * n * n);
	for (int_fast16_t rowNumber = 0; rowNumber < n; rowNumber++) {
		arr[rowNumber] = (int32_t*)calloc(sizeof(int32_t), n);
		for (int_fast16_t columnNumber = 0; /*columnNumber < n*/; /*columnNumber++*/) {
			if (fscanf(filePointer, "%i", &arr[rowNumber][columnNumber]) < 1) {
				//Print the file path with the error to the error stream (means this will display no matter what)
				fprintf(stderr, "Error reading border of file. Score: %i\n", arr[rowNumber][columnNumber]);
				//Exit/crash the program on this error
				return arr;
			}

			//Throw away the next comma or newline
			fgetc(filePointer);

			columnNumber++;

			if (columnNumber >= n)
				break;
		}
	}
	return arr;
}
int_fast32_t findHighest(int32_t** array, const int_fast16_t &n) {
	int_fast32_t score = array[n - 1][n - 1];
	for (int_fast16_t column = n - 2; column >= 0; column--) {
		if (array[n - 1][column + 1] > 0)
			array[n - 1][column] += array[n - 1][column + 1];
		if (array[n - 1][column] > score)
			score = array[n - 1][column];
	}
	for (int_fast16_t row = n - 2; row >= 0; row--) {
		for (int_fast16_t column = n - 1; column >= 0; column--) {
			if (column == n - 1) {
				if (array[row + 1][column] > 0){
					array[row][column] += array[row + 1][column];
					if (array[row][column] > score)
						score = array[row][column];
				}
			}
			else{
				if (array[row + 1][column] > array[row][column + 1])
					array[row][column] += array[row + 1][column];
				else
					array[row][column] += array[row][column + 1];
				if (array[row][column] > score)
					score = array[row][column];
			}
		}
	}
	return score;
}