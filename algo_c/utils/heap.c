#include "heap.h"

#ifdef __HEAP_H__

/*
 * heap and priority queue
 */

void maxHeapify(int* arr, int length, int i){
	int left = 2*i;
	int right = 2*i+1;

	int maxPos = i;
	if(left < length && arr[left] > arr[maxPos]){
		maxPos = left;
	}
	
	if(right < length && arr[right] > arr[maxPos]){
		maxPos = right;
	}

	if(maxPos != i){
		int tmp = arr[i];
		arr[i] = arr[maxPos];
		arr[maxPos] = tmp;
		maxHeapify(arr, length, maxPos);
	}
}

void buildMaxHeap(int* arr, int length){
	for(int i = (length-2)/2; i >= 0; i--)
		maxHeapify(arr, length, i);
}

int maximumMaxHeap(int* arr){
	return arr[0];
}

int maxExtractMaxHeap(int* arr, int length){
	if(length < 1)
		return -1;

	int max = arr[0];
	arr[0] = arr[length-1];
	int* tmp = (int*) realloc(arr, sizeof(int) * (length-1));
	arr = tmp;
	maxHeapify(arr, length-1, 0);

	return max;
}

void increaseKeyMaxHeap(int* arr, int length, int i, int key){
	if(key < arr[i])
		return;

	arr[i] = key;
	int iParent = (i-1)/2;
	while(i > 0 && arr[i] > arr[iParent]){
		arr[i] = arr[iParent];
		arr[iParent] = key;
		
		i = iParent;
		iParent = (i-1)/2;
	}
}

void insertMaxHeap(int** arr, int length, int key){
	int* tmp = (int*) realloc(*arr, sizeof(int) * (length+1));
	*arr = tmp;
	tmp[length] = INT_MIN;
	
	increaseKeyMaxHeap(tmp, length+1, length, key);
	printArr(tmp, length+1, 0);
}

#endif
