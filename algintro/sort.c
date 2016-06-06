#include <stdlib.h>
#include <string.h>
#include "util.h"

#undef DEBUG

#undef TEST

/* insertion sort */
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
#ifdef DEBUG
		printArr(arr, length, i);
#endif
	}
}

/* merge sort - divide and conquer */

// merge two sorted arr[i:j-1] and arr[j:k]
void merge(int* arr, int i, int j, int k)
{
#ifdef DEBUG
	printf("merge index [i,%d],[j,%d],[k,%d]\n", i, j, k); 
#endif
	int* tmp = (int*)malloc(sizeof(int) * (k-i+1));
	memset(tmp, 0, sizeof(int) * (k-i+1));

	int ipos = i;
	int jpos = j;
	int tpos = 0;
	while(ipos < j && jpos <= k)
	{
		if(arr[ipos] <= arr[jpos])
		{
			tmp[tpos] = arr[ipos];
			ipos++;
			tpos++;
		}else{
			tmp[tpos] = arr[jpos];
			jpos++;
			tpos++;
		}
#ifdef DEBUG
		printArr(tmp, k-i+1, tpos);
#endif
	}

	if(ipos >= j)
	{
		while(jpos <= k)
		{
			tmp[tpos] = arr[jpos];
			tpos++;
			jpos++;
#ifdef DEBUG
			printArr(tmp, k-i+1, tpos);
#endif
		}
	}
	else if(jpos > k)
	{
		while(ipos < j)
		{
			tmp[tpos] = arr[ipos];
			tpos++;
			ipos++;
#ifdef DEBUG
			printArr(tmp, k-i+1, tpos); 
#endif
		}
	}

	int index = 0;
	while(i <= k){
		arr[i] = tmp[index];
		i++;
		index++;
	}

	//free malloc
	free(tmp);
}

// recursive divide arr into left and right until first equals last of subArr
void mergeSort(int* arr, int first, int last)
{
	if(first < last)
	{
		int mid = (first + last)/2;
		mergeSort(arr, first, mid);
		mergeSort(arr, mid+1, last);
		merge(arr, first, mid+1, last);
	}
}

/* quick sort */
void quickSort()
{
	
}

/* main */
int main(int argc, char** argv) 
{
	int arr[] = {5,3,1,4,6,2};
	int length = sizeof(arr)/sizeof(int);
	printArr(arr, length, 0);
	
	int arr2[] = {11,70,72,82,10,25,36,44,60};
	int length2 = sizeof(arr2)/sizeof(int);
	printArr(arr2, length2, 0);
	
	int length3 = 10000;
	int arr3[length3];

	generateRandom(arr3, length3, 0, 100000);
	printArr(arr3, length3, 0);
	startRuntime("insertSort");
	insertSort(arr3, length3);
	endRuntime("insertSort");
	printArr(arr3, length3, -1);

	generateRandom(arr3, length3, 0, 100000);
	printArr(arr3, length3, 0);
	startRuntime("mergeSort");
	mergeSort(arr3, 0, length3-1);
	endRuntime("mergeSort");
	printArr(arr3, length3, -1);
	
	return 0;
}
