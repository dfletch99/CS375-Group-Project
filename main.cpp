#include "sort.h"
#include <time.h>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

//initial array length (will change throughout testing)
int ARRAY_LENGTH = 5;

//total number of iterations for testing
//number of loops for one batch of tests
const int NUMBER_OF_LOOPS = 5;
//do these tests all the way up to this length of array
const int MAX_ARRAY_LENGTH = 5000;
//incrememnt array size by this value for each batch
const int SIZE_INCREMENT = 1;

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

//log the time of the algorithm?
bool timer = false;

//fill array with random values (true), or sorted values (false)?
bool fillRandom = true;


//fill the array with random values using uniform integer distribution RNG, or sorted values if fillRandom is false
//array[] is the array to be sorted
void fillArray(int array[]){
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(MINIMUM_VALUE, MAXIMUM_VALUE);

	for(int i = 0; i < ARRAY_LENGTH; i++){
		if(fillRandom)  //random values
			array[i] = distr(eng);
		else		//sorted values
			array[i] = i;
	}
}

//failsafe checker to determine if the algorithms do what they're supposed to.
//Note: do not include this in lengthy testing after you are certain the algorithms function properly. It adds an additional O(n) time to the complexity, and larger array sizes really slows that down.
//array[] is the array to be sorted
bool isSorted(int array[]){
	for(int i = 0; i < ARRAY_LENGTH - 1; i++){
		if(array[i] > array[i+1]) return false;
	}
	return true;
}

//main function to conduct all the testing
int main(){
	//timer for the entire program (not used in testing results, but gives the user an idea of how long each entire test takes)
	auto entireProgramStart = chrono::steady_clock::now();

	//write results to an output file
	ofstream outfile;
	outfile.open("dummy.txt", ios::app);
	outfile << "NUMBER OF LOOPS PER BATCH: " << NUMBER_OF_LOOPS << "\n" << endl;

	//random seed for quicksort's random pivot picking functionality
	srand(time(NULL));
	
	//begin testing
	while(ARRAY_LENGTH <= MAX_ARRAY_LENGTH){
		//timer for an entire batch of sorts (to be averaged for a more accurate result)
		chrono::duration<double> elapsedTimeTotal = chrono::steady_clock::duration::zero();

		//initialize array and sorting class
		int array[ARRAY_LENGTH];
		Sorter s(ARRAY_LENGTH);

		
		cout << "ARRAY LENGTH " << ARRAY_LENGTH << ":" << endl;
	
		//complete one batch of tests for the same array length. NUMBER_OF_LOOPS = the number of times an array of the current length is sorted
		for(int testNumber = 0; testNumber < NUMBER_OF_LOOPS; testNumber++){
			
			if(logEach)
				cout << "sort batch " << testNumber + 1 << ":";

			//fill the array with values
			fillArray(array);

			//verbose output, mainly for debugging purposes
			if(verbose){
				cout << "BEFORE SORT:" << endl;
				cout << "Array: [";
				for(int j = 0; j < ARRAY_LENGTH-1; j++){
					cout << array[j] << ", ";
				}
				cout << array[ARRAY_LENGTH - 1] << "]" << endl;
			}
			
			//timer for one individual sort
			auto start = chrono::steady_clock::now();
			//call the sorting algorithm specified
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
			//stop timer for one individual sort
			auto end = chrono::steady_clock::now();

			//verbose output, mainly for debugging purposes
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
			
			
			//calculate time taken for a single sort
			chrono::duration<double> elapsedTimeSingle = end - start;
			//add that time to the entire time for the batch
			elapsedTimeTotal += elapsedTimeSingle;
			if(timer){
				if(logEach)
					cout << "Time taken: " << elapsedTimeSingle.count() << endl;
				outfile << "Time taken: " << elapsedTimeSingle.count() << endl;
			}
		}

		//print out results (different format for console/output file)
		//involves taking the total elapsed time (of all sorts in the batch) and dividing it by NUMBER_OF_LOOPS, creating an average run-time
		//this is helpful because it prevents outliers from corner-cases to affect the time complexity graph.
		//For example, if an array was filled with random values, but it was "mostly sorted" by chance, insertion sort might perform better on one pass-through of that array length.
		//multiple runs of the same length make this sort of scenario much less impactful.
		cout << "TOTAL TIME TAKEN FOR LENGTH " << ARRAY_LENGTH << ": " << elapsedTimeTotal.count() << "\nAVERAGE TIME: " << (elapsedTimeTotal.count()) / NUMBER_OF_LOOPS << endl;
		outfile << ARRAY_LENGTH << " " << (elapsedTimeTotal.count()) / NUMBER_OF_LOOPS << endl;
		//increase the array size and do it all again
		ARRAY_LENGTH += SIZE_INCREMENT;
	}
	
	
	outfile.close();

	auto entireProgramEnd = chrono::steady_clock::now();
	chrono::duration<double> entireProgramTime = entireProgramEnd - entireProgramStart;

	cout << "\nENTIRE PROGRAM DURATION: " << entireProgramTime.count() << " seconds" << endl;
}

