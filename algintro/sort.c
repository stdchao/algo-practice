#include <stdlib.h>
#include <string.h>
#include "util.h"

#undef DEBUG
#undef PRINT
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

// partition arr into two subArr divided by an element,
// return the index of the element
int partition(int* arr, int i, int j)
{
	// select the compare element and swap to the head of arr
	int cpos = rand() % (j-i+1) + i;
	int ckey = arr[cpos];
	arr[cpos] = arr[i];
	arr[i] = ckey;

	// partition ipos and jpos for subArr tail that divided
	int ipos = i;
	int jpos = i + 1;
#ifdef DEBUG 
	printf("parition: [%d,%d]\n", i, j);
	printArr(arr, j-i+1, 1);
#endif
	while(jpos <= j)
	{
		if(arr[jpos] < ckey)
		{
			ipos++;
			int tmp = arr[jpos];
			arr[jpos] = arr[ipos];
			arr[ipos] = tmp;
		}
		jpos++;
#ifdef DEBUG
		printArr(arr, j-i+1, jpos);
#endif
	}
	
	// swap the compare element to tail of min subArr
	arr[i] = arr[ipos];
	arr[ipos] = ckey;
#ifdef DEBUG
		printArr(arr, j-i+1, jpos);
#endif
	return ipos;
}

void quickSort(int* arr, int i, int j)
{
	if(i < j)
	{
		int r = partition(arr, i, j);
		quickSort(arr, i, r-1);
		quickSort(arr, r+1, j);
	}
}

/* main */
int main(int argc, char** argv) 
{
	int arr[] = {5,3,1,4,6,2};
	int length = sizeof(arr)/sizeof(int);
	printArr(arr, length, 0);

	int lenArr[5] = {10, 100, 1000, 10000, 100000};
	for(int i = 0; i < 5; i++){ 
 		int testLength = lenArr[i];
		int testArr[testLength];
		printf("\nN = %d\n", testLength);
 		
 		generateRandom(testArr, testLength, 0, 100000); 
#ifdef PRINT
		printArr(testArr, testLength, 0);
#endif
 		startRuntime("insertSort");
		insertSort(testArr, testLength);
 		endRuntime("insertSort");
#ifdef PRINT
 		printArr(testArr, testLength, -1);
#endif

		generateRandom(testArr, testLength, 0, 100000);
#ifdef PRINT
 		printArr(testArr, testLength, 0);
#endif
 		startRuntime("mergeSort");
		mergeSort(testArr, 0, testLength-1);
 		endRuntime("mergeSort");
#ifdef PRINT
		printArr(testArr, testLength, -1);
#endif
	
 		generateRandom(testArr, testLength, 0, 100000);
#ifdef PRINT
		printArr(testArr, testLength, 0);
#endif
 		startRuntime("quickSort");
		quickSort(testArr, 0, testLength-1);
 		endRuntime("quickSort");
#ifdef PRINT
		printArr(testArr, testLength, -1); 
#endif
	}

	return 0;
}
