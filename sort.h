#ifndef SORT_H
#define SORT_H
#include <iostream>
#include <algorithm>



using namespace std;

class Sorter{
	public:
		int ARRAY_LENGTH;

		Sorter(int);
		void insertionSort(int[]);
		void mergeSort(int[]);
		void swap(int[], int, int);
		int parition(int[], int, int, int);
		void quickSort(int[], int, int, int);
		void mergeSortHelper(int[], int, int);
		void merge(int[], int, int, int);
};

Sorter::Sorter(int length){
	ARRAY_LENGTH = length;
}

void Sorter::insertionSort(int array[]){
    int toSort;
    int temp;
    for(int i = 1; i < ARRAY_LENGTH; i++){
      toSort = array[i];
      temp = i-1;

      while(temp >= 0 && array[temp] > toSort){
        array[temp+1] = array[temp];
        temp--;
      }
      array[temp+1] = toSort;
    }
}


void Sorter::mergeSort(int array[]){
	mergeSortHelper(array, 0, ARRAY_LENGTH - 1);
}

//takes two values in an array and switches their locations with each other
//arr[] is an array of ints
//x is the index of one value to be changed
//y is the index of the other value to be changed
void Sorter::swap(int arr[], int x, int y)
{
	int temp = arr[x]; //temp holds the value at index x that will be moved to index y
	arr[x] = arr[y];
	arr[y] = temp;
}

//the helper function to quicksort that takes a pivot and places it in the correct spot in the array and makes everything to the left less than the pivot and everything to the right greater than or equal to the pivot
//arr[] is an array of ints to be sorted
//left is index of the leftmost value in the array to be worked on
//right is the index of the rightmost value in the array to be worked on
//isRandom is either 0 or 1 depending if the random version of quicksort is wanted or not 
int Sorter::parition(int arr[], int left, int right, int isRandom)
{
	if (isRandom == 1) //if random version do this
	{
		int random = rand() % (right - left + 1) + left; //random value such that left<=random<=right to serve as the pivot
		swap(arr, random, right);
	}

	int pivot = arr[right]; //value of the pivot which is comapred to 
	int low = left-1; //the boundry between items less than the pivot and greater than or equal to the pivot

	for (int j=left; j<right; j++)
	{
		if (arr[j] < pivot)
		{
			low++;
			swap(arr, low, j);
		}
	}
	swap(arr, low+1, right);
	return low+1;
}

//the quickSort algorithm both random version and non random
//arr[] is an array of ints to be sorted
//left is index of the leftmost value in the array to be worked on
//right is the index of the rightmost value in the array to be worked on
//isRandom is either 0 or 1 depending if the random version of quicksort is wanted or not 
void Sorter::quickSort(int arr[], int left, int right, int isRandom)
{
	if (left < right)
	{
		int part = parition(arr, left, right, isRandom); //the index where the sorted value is...everything left is less than everything right is greater or equal
		quickSort(arr, left, part-1, isRandom); //recursive call on left part
		quickSort(arr, part+1, right, isRandom); //recursive call on right part
	}
}

void Sorter::mergeSortHelper(int array[], int leftIndex, int rightIndex){
	if(leftIndex < rightIndex){
		int middleIndex = (leftIndex+rightIndex)/2;
		mergeSortHelper(array, leftIndex, middleIndex);
		mergeSortHelper(array, middleIndex + 1, rightIndex);
		
		merge(array, leftIndex, middleIndex, rightIndex);
	}
}

/* ~~~~~~BROKEN~~~~~~ */
void Sorter::merge(int array[], int leftIndex, int middleIndex, int rightIndex){
	int firstArrayLength = middleIndex - leftIndex + 1;
	int secondArrayLength = rightIndex - middleIndex;

	int firstArray[firstArrayLength], secondArray[secondArrayLength];
	
	//copy data of separate arrays
	for(int i = 0; i < firstArrayLength; i++){
		firstArray[i] = array[leftIndex+i];
	}
	for(int i = 0; i < secondArrayLength; i++){
		secondArray[i] = array[middleIndex + 1 + i];
	}
	/*	//PRINT STATEMENT DEBUGGING
	cout << "Left and Right:" << endl;
	cout << "[";
	for(int i = 0; i < firstArrayLength; i++){
		cout << firstArray[i] << ", ";
	}
	cout << "]" << endl;

	cout << "[";
	for(int i = 0; i < secondArrayLength; i++){
		cout << secondArray[i] << ", ";
	}
	cout << "]" << endl;
	*/

	//the actual merge
	int firstIndex = 0;
	int secondIndex = 0;
	int mergedIndex = leftIndex;
	while(firstIndex < firstArrayLength && secondIndex < secondArrayLength){
		if(firstArray[firstIndex] <= secondArray[secondIndex]){
			array[mergedIndex] = firstArray[firstIndex];
			firstIndex++;
		}
		else{
			array[mergedIndex] = secondArray[secondIndex];
			secondIndex++;
		}
		mergedIndex++;
	}

	//at this point, there are remaining elements to be merged in ONLY one of the subarrays. fill the rest of the main array with those values.

	while(firstIndex < firstArrayLength){
		array[mergedIndex] = firstArray[firstIndex];
		firstIndex++;
		mergedIndex++;
	}

	while(secondIndex < secondArrayLength){
		array[mergedIndex] = secondArray[secondIndex];
		secondIndex++;
		mergedIndex++;
	}

	/*	//PRINT STATEMENT DEBUGGING
	cout << "merged array:" << endl;
	cout << "[";
	for(int i = 0; i < ARRAY_LENGTH; i++){
		cout << array[i] << ", ";
	}
	cout << "]\n" << endl;
	*/
}
#endif
