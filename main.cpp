#include "sort.h"
#include <time.h>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

//100, 600, 1100, 1600,  
int ARRAY_LENGTH = 3600;

//total number of iterations for testing
//number of loops for one batch of tests
const int NUMBER_OF_LOOPS = 1000;
//do these tests all the way up to this length of array
const int MAX_ARRAY_LENGTH = 10000;
//incrememnt array size by this value
const int SIZE_INCREMENT = 500;

//define minimum and maximum values for random number generation
const int MINIMUM_VALUE = -100;
const int MAXIMUM_VALUE = 100;

//choose which type of sort to test
enum sortType{INSERTION = 0, QUICK, QUICKRANDOM, MERGE};
sortType whichSort = INSERTION;

//print out each time calculation to console?
bool logEach = false;
//print out verbose calculations?
bool verbose = false;

//time the length of the algorithm?
bool timer = true;

//fill array with random values, or sorted values?
bool fillRandom = true;


//fill the array with random values using uniform integer distribution RNG
void fillArray(int array[]){
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(MINIMUM_VALUE, MAXIMUM_VALUE);

	for(int i = 0; i < ARRAY_LENGTH; i++){
		if(fillRandom)
			array[i] = distr(eng);
		else
			array[i] = i;
	}
}

bool isSorted(int array[]){
	for(int i = 0; i < ARRAY_LENGTH - 1; i++){
		if(array[i] > array[i+1]) return false;
	}
	return true;
}

int main(){
	auto entireProgramStart = chrono::steady_clock::now();

	ofstream outfile;
	outfile.open("data_output_insertion.txt", ios::app);
	outfile << "NUMBER OF LOOPS PER BATCH: " << NUMBER_OF_LOOPS << "\n" << endl;

	
	srand(time(NULL));
	
	while(ARRAY_LENGTH <= MAX_ARRAY_LENGTH){
		chrono::duration<double> elapsedTimeTotal = chrono::steady_clock::duration::zero();

		int array[ARRAY_LENGTH];
		Sorter s(ARRAY_LENGTH);

		//outfile << "ARRAY LENGTH " << ARRAY_LENGTH << ":" << endl;
		cout << "ARRAY LENGTH " << ARRAY_LENGTH << ":" << endl;
	
		for(int testNumber = 0; testNumber < NUMBER_OF_LOOPS; testNumber++){
			//outfile << "sort batch " << testNumber + 1 << ":";
			if(logEach)
				cout << "sort batch " << testNumber + 1 << ":";

			fillArray(array);
			if(verbose){
				cout << "BEFORE SORT:" << endl;
				cout << "Array: [";
				for(int j = 0; j < ARRAY_LENGTH-1; j++){
					cout << array[j] << ", ";
				}
				cout << array[ARRAY_LENGTH - 1] << "]" << endl;
			}

			auto start = chrono::steady_clock::now();
			switch(whichSort){
				case 0:
					s.insertionSort(array);
					break;
				case 1:
					s.quickSort(array, 0, ARRAY_LENGTH-1, 0);
					break;
				case 2:
					s.quickSort(array, 0, ARRAY_LENGTH-1, 1);
					break;
				case 3:
					s.mergeSort(array);
					break;
				default:
					cerr << "error: inappropriate sort name" << endl;
			}

			auto end = chrono::steady_clock::now();

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
				//cout << "Iteration " << i << ": " << (isSorted(array) ? "SORTED":"NOT SORTED\n") << endl;
			}
			
			//check if the array is actually sorted (**DO NOT USE DURING DATA COLLECTION**)
			
			
			if(!isSorted(array)){
				cout << "error! sort failed" << endl;
				return -1;
			}
			
			

			chrono::duration<double> elapsedTimeSingle = end - start;
			elapsedTimeTotal += elapsedTimeSingle;
			if(timer){
				if(logEach)
					cout << "Time taken: " << elapsedTimeSingle.count() << endl;
				//outfile << "Time taken: " << elapsedTimeSingle.count() << endl;
			}
		}
		cout << "TOTAL TIME TAKEN FOR LENGTH " << ARRAY_LENGTH << ": " << elapsedTimeTotal.count() << "\nAVERAGE TIME: " << (elapsedTimeTotal.count()) / NUMBER_OF_LOOPS << endl;
		outfile << ARRAY_LENGTH << " " << (elapsedTimeTotal.count()) / NUMBER_OF_LOOPS << endl;
		ARRAY_LENGTH += SIZE_INCREMENT;
	}
	
	
	outfile.close();

	auto entireProgramEnd = chrono::steady_clock::now();
	chrono::duration<double> entireProgramTime = entireProgramEnd - entireProgramStart;

	cout << "\nENTIRE PROGRAM DURATION: " << entireProgramTime.count() << " seconds" << endl;
}

