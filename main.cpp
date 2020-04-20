#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;
extern const int ARRAY_LENGTH;
const int NUMBER_OF_LOOPS = 10;
enum sortType{INSERTION = 0, QUICK, QUICKRANDOM, MERGE};
sortType sort = MERGE;


//fill the array with random values using srand, seeded with the time() function
void fillArray(int array[]){
	srand(time(NULL));
	for(int i = 0; i < ARRAY_LENGTH; i++){
		array[i] = rand() % 100;
	}
}

int main(){
	int array[ARRAY_LENGTH];
	Sorter s;
	for(int i = 0; i < NUMBER_OF_LOOPS; i++){
		fillArray(array);

		cout << "BEFORE SORT:" << endl;
		cout << "Array: [";
		for(int i = 0; i < ARRAY_LENGTH-1; i++){
			cout << array[i] << ", ";
		}
		cout << array[i] << "]" << endl;

		switch(sort){
			case 0:
				s.insertionSort(array);
				break;
			case 1:
				s.quickSort(array, false);
				break;
			case 2:
				s.quickSort(array, true);
				break;
			case 3:
				s.mergeSort(array);
				break;
			default:
				cerr << "error: inappropriate sort name" << endl;
		}
		cout << "AFTER SORT:" << endl;
		cout << "Array: [";
		for(int i = 0; i < ARRAY_LENGTH-1; i++){
			cout << array[i] << ", ";
		}
		cout << array[i] << "]\n" << endl;
	}
}

