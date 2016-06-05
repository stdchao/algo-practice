#include <stdio.h>
#include <sys/time.h>

/* public values */
struct timeval startTime, endTime;

void startRuntime(char* str)
{
	gettimeofday(&startTime, NULL);
	printf("\nstart %s:\n", str);
}

void endRuntime(char* str)
{
	gettimeofday(&endTime, NULL);
	int timeuse = 1000000 * ( endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
	printf("runtime:[%s, %d us]\n", str, timeuse);
}

void printArr(int* arr, int length, int process)
{
	printf("arr %d:\t", process);
	for(int i=0; i<length; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
