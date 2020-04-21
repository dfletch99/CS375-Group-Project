#include "sort.h"
#include <time.h>
#include <string>

using namespace std;
extern const int ARRAY_LENGTH;
const int NUMBER_OF_LOOPS = 100000;
enum sortType{INSERTION = 0, QUICK, QUICKRANDOM, MERGE};
sortType whichSort = MERGE;
bool verbose = false;


//fill the array with random values using srand, seeded with the time() function
void fillArray(int array[]){
	srand(time(NULL));
	for(int i = 0; i < ARRAY_LENGTH; i++){
		array[i] = rand() % 100;
	}
}

bool isSorted(int array[]){
	for(int i = 0; i < ARRAY_LENGTH - 1; i++){
		if(array[i] > array[i+1]) return false;
	}
	return true;
}

int main(){
	int array[ARRAY_LENGTH];
	Sorter s;
	for(int i = 0; i < NUMBER_OF_LOOPS; i++){
		fillArray(array);
		if(verbose){
			cout << "BEFORE SORT:" << endl;
			cout << "Array: [";
			for(int j = 0; j < ARRAY_LENGTH-1; j++){
				cout << array[j] << ", ";
			}
			cout << array[ARRAY_LENGTH - 1] << "]" << endl;
		}
		switch(whichSort){
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

		if(verbose){
			cout << "AFTER SORT:" << endl;
			cout << "Array: [";
			for(int j = 0; j < ARRAY_LENGTH-1; j++){
				cout << array[j] << ", ";
			}
			cout << array[ARRAY_LENGTH - 1] << "]" << endl;
			cout << "Is it sorted? " << (isSorted(array) ? "YES":"NO") << endl;
			cout << endl;
		}
		else{
			cout << "Iteration " << i << ": " << (isSorted(array) ? "SORTED":"NOT SORTED\n") << endl;
		}
	}
}

