#include "util.h"

/* public values */
struct timeval startTime, endTime;

// get current time
uint64_t getCurrentMilliSec()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	uint64_t currentMilliSec = (uint64_t)(tv.tv_sec) * 1000 + (uint64_t)(tv.tv_usec) / 1000;
	return currentMilliSec;
}

void startRuntime(char* str)
{
	gettimeofday(&startTime, NULL);
	printf("start %s:\n", str);
}

void endRuntime(char* str)
{
	gettimeofday(&endTime, NULL);
	int timeuse = 1000000 * ( endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
	printf("runtime:[%s, %d us]\n", str, timeuse);
}

void printArr(int* arr, int length, int process)
{
	if(process == 0)
		printf("\n");

	printf("arr %d: ", process);
	for(int i=0; i<length; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void printSubArr(int* arr, int i, int j){
	printf("arr[%d..%d]: ", i, j);
	for(int k = i; k <= j; k++)
	{
		printf("%d ", arr[k]);
	}
	printf("\n");
}

void generateRandom(int* randomArr, int length, int low, int high)
{
 	srand((unsigned)time(NULL));
	int rangeLength = high - low + 1;
	int rangeArr[rangeLength];
	for(int i = low; i <= high; i++)
		rangeArr[i] = i;

	for(int i = 0; i < length; i++)
	{
		int index = rand() % rangeLength;
		int tmp = rangeArr[i];
		rangeArr[i] = rangeArr[index];
		rangeArr[index] = tmp;
	}

	for(int i = 0; i < length; i++)
		randomArr[i] = rangeArr[i];
}
