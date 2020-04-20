#ifndef SORT_H
#define SORT_H
#include <iostream>

const int ARRAY_LENGTH = 10;

class Sorter{
	public:
		int array[ARRAY_LENGTH];
		void insertionSort(int[]);
		void mergeSort(int[]);
		void quickSort(int[], bool);
		void mergeSortHelper(int[], int, int);
		void merge(int[], int, int, int);
};

void Sorter::insertionSort(int array[]){
	//TODO: do
}

void Sorter::mergeSort(int array[]){
	mergeSortHelper(array, 0, ARRAY_LENGTH - 1);
}

void Sorter::quickSort(int array[], bool random){
	//TODO: do
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

	//the actual merge
	int firstIndex = 0;
	int secondIndex = 0;
	int mergedIndex = 1;
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
}
#endif
