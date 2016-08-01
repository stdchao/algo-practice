#include "util.h"

#define DEBUG
#undef TEST
#undef PRINT

/*--------------------------- insertion sort ----------------------------*/
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

/*------------------- merge sort - divide and conquer -------------------*/

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
		}
		else
		{
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

/*-------------------------- quick sort ---------------------------------*/

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
	printf("parition: [%d,%d] %d\n", i, j, ckey);
	printSubArr(arr, i, j);
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
		printSubArr(arr, i, j);
#endif
	}

	// swap the compare element to tail of min subArr
	arr[i] = arr[ipos];
	arr[ipos] = ckey;
#ifdef DEBUG
	printSubArr(arr, i, j);
	printf("return: [%d]\n", ipos);
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

/*-------------------------- heap sort ----------------------------------*/

/* fix down to sub max heap in arr[i..size-1] */
void fixdownMaxHeap(int* arr, int i, int size)
{
	int tmp = arr[i];
	int maxpos = 2*i + 1;
	
	while(maxpos < size)
	{
		if(maxpos + 1 < size && arr[maxpos+1] > arr[maxpos])
			++maxpos;

		if(tmp >= arr[maxpos])
			break;

		arr[i] = arr[maxpos];
		i = maxpos;
		maxpos = 2*i + 1;
	}
	arr[i] = tmp;
}

/* build max heap */
void makeMaxHeap(int* arr, int size)
{
	for(int i = ((size-1)-1)/2; i>=0; i--)
		fixdownMaxHeap(arr, i, size);
#ifdef DEBUG
	printArr(arr, size, size);
#endif
}

/* sort ascend in max heap */
void heapSortAscend(int* arr, int size)
{
	for(int i = size-1; i >= 1; i--)
	{
		// swap min value to array tail
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;
		// fixdown maxHeap
		fixdownMaxHeap(arr, 0, i);
#ifdef DEBUG
		printArr(arr, size, i);
#endif
	}
}

/*-------------------------------radix sort ----------------------------*/
// counting sort
void countSort(int* arr, int size, int k)
{
	//
	int sortArr[size];
	memset(sortArr, 0, sizeof(int) * size);

	int countArr[k];
	// initialize
	for(int i=0; i<k; i++)
		countArr[i] = 0;

	// count for arr[j]
	for(int j=0; j<size; j++)
		countArr[arr[j]] += 1;
#ifdef DEBUG
	printArr(countArr, k, -2);
#endif	
	// count for smaller than arr[j]
	for(int i=1; i<k; i++)
		countArr[i] += countArr[i-1];
#ifdef DEBUG
	printArr(countArr, k, -2);
#endif
	// sort
	for(int j=size-1; j>=0; j--)
	{
		sortArr[countArr[arr[j]]-1] = arr[j];
		countArr[arr[j]] -= 1;
#ifdef DEBUG
		printArr(sortArr, size, j);
#endif
	}
	//
	memcpy(arr, sortArr, size*sizeof(int));
}

// radix sort
void radixSort(int* arr, int size, int radix, int digit)
{
	for(int n = 0; n < digit; n++)
	{
		// init count array
		int countArr[radix];
		memset(countArr, 0, sizeof(int) * radix);
		
		// fill count array
		int k = pow(radix, n);
		for(int i = 0; i < size; i++)
		{
			int value = (arr[i] / k) % radix;
			countArr[value] += 1;
		}
#ifdef DEBUG
			printArr(countArr, radix, 0);
#endif

		for(int i = 1; i < radix; i++)
			countArr[i] += countArr[i-1];
#ifdef DEBUG
			printArr(countArr, radix, 0);
#endif
		
		// sort arr
		int sortArr[size];
		memset(sortArr, 0, sizeof(int) * size);
		for(int j = size - 1; j >= 0; j--)
		{
			int value = (arr[j] / k) % radix;
			sortArr[countArr[value] - 1] = arr[j];
			countArr[value] -= 1;
#ifdef DEBUG
			printArr(sortArr, size, j);
#endif
		}

		//
		memcpy(arr, sortArr, sizeof(int) * size);
#ifdef DEBUG
		printArr(arr, size, n);
#endif
	}
}

/*-------------------------------- main --------------------------------*/
int main(int argc, char** argv) 
{
	int arr[] = {5,3,4,1,4,6,4,2};
	int length = sizeof(arr)/sizeof(int);
	quickSort(arr, 0, length-1);
	printArr(arr, length, 0);

	int lenArr[5] = {10, 100, 1000, 10000, 100000};
	for(int i = 0; i < 5; i++){
		int testLength = lenArr[i];
		int testArr[testLength];
		printf("\nN = %d\n", testLength);

#ifdef TEST
		// insert sort
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

		// merge sort
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

		// quick sort
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
		// heap sort
		generateRandom(testArr, testLength, 0, 100000);
#ifdef PRINT
		printArr(testArr, testLength, 0);
#endif
		startRuntime("heapSort");
		makeMaxHeap(testArr, testLength);
		heapSortAscend(testArr, testLength);
		endRuntime("heapSort");
#ifdef PRINT
		printArr(testArr, testLength, -1);
#endif
		// count sort
		generateRandom(testArr, testLength, 0, 100000);
#ifdef PRINT
		printArr(testArr, testLength, 0);
#endif
		startRuntime("countSort");
		countSort(testArr, testLength, 100001);
		endRuntime("countSort");
#ifdef PRINT
		printArr(testArr, testLength, -1);
#endif
		// radix sort
		generateRandom(testArr, testLength, 0, 100000);
#ifdef PRINT
		printArr(testArr, testLength, 0);
#endif
		startRuntime("radixSort");
		radixSort(testArr, testLength, 10, 5);
		endRuntime("radixSort");
#ifdef PRINT
		printArr(testArr, testLength, -1);
#endif
#endif //TEST
		
	}

	return 0;
}
