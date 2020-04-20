#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void swap (int arr[], int x, int y)
{
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

int parition(int arr[], int left, int right)
{
	int random = rand() % (right - left + 1) + left;
	swap(arr, random, right);

	int pivot = arr[right];
	int low = left-1;

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

void quickSort(int arr[], int left, int right)
{
	if (left < right)
	{
		int part = parition(arr, left, right);
		quickSort(arr, left, part-1);
		quickSort(arr, part+1, right);
	}
}

int main(int argc, char *argv[])
{
	ifstream inFile(argv[1]);
	string fileName(argv[2]);
	ofstream outFile;
	outFile.open(fileName);

	int numNums;
	inFile >> numNums;

	int arr[numNums];
	for (int i=0; i<numNums; i++)
	{
		inFile >> arr[i];
	}

	outFile << "Before Sorting:" << endl;
	for (int a=0; a<numNums; a++)
	{
		outFile << arr[a] << " ";
	}
	outFile << endl;

	quickSort(arr, 0, numNums-1);

	outFile << "After Sorting:" << endl;
	for (int b=0; b<numNums; b++)
	{
		outFile << arr[b] << " ";
	}
	outFile << endl;

	outFile.close();
	return 0;
}
