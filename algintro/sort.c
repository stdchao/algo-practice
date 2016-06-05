#include "util.h"

void insertSort(int* arr, int length)
{
	for(int i=1; i<length; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while(j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
		
		//debug
		printArr(arr, length, i);
	}
}

int main(int argc, char** argv) 
{
	int arr[] = {5,3,1,4,6,2};
	int length = sizeof(arr)/sizeof(int);
	printArr(arr, length, 0);

	startRuntime("insertSort");
	insertSort(arr, length);
	endRuntime("insertSort");
	
	return 0;
}
