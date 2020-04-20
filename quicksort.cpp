#include <iostream>
#include <fstream>

using namespace std;

void quickSort(int arr[], int low, int high)
{
	//
}

int main(int argc, char *argv[])
{
	ifstream inFile(argv[1]);
	string fileName(argv[2]);

	int numNums;
	inFile >> numNums;

	int arr[numNums];
	for (int i=0; i<numNums; i++)
	{
		inFile >> arr[i];
	}

	quickSort(arr, 0, numNums-1);
}
