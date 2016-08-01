#include "heap.h"
#include "../leetcode/util.h"

int main(int argc, char** argv){
	/* init heap */
	int* pHeap = (int*) malloc(sizeof(int));
	pHeap[0] = 0;

	/* build heap */
	for(int i = 0; i < 10; i++){
		int key = rand() % 10;
		insertMaxHeap(&pHeap, i+1, key);
	}

	/* free memory */
	free(pHeap);

	return 0;
}
