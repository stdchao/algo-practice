#include <stdlib.h>
#include "util.h"

/* quick sort */
void quickSort(int* nums, int start, int end){
    if(start < end){
        // partition
        int k = rand() % (end - start + 1) + start;
        //
        int key = nums[k];
        nums[k] = nums[start];
        nums[start] = key;
        //
        int i = start;
        int j = i + 1;
        while(j <= end){
            if(nums[j] <= key){
                // swap
                i++;
                int tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
            j++;
        }
        //
        nums[start] = nums[i];
        nums[i] = key;
        //
        
        quickSort(nums, start, i-1);
        quickSort(nums, i+1, end);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize) {
    int **returnNums = (int **)malloc(sizeof(int *));
    *returnSize = 0;
    // sort nums
    quickSort(nums, 0, numsSize-1);
	printSubArr(nums, 0, numsSize-1);
    // 
    for(int i = 0; i < numsSize-2; i++){
        // skip repeat elements
        if(i > 0 && nums[i] == nums[i-1])
            continue;
        
        // two sum
        int start = i + 1;
        int end = numsSize - 1;
        int target = -nums[i];
        while(start < end){
            if (start > i + 1 && nums[start - 1] == nums[start]) {
                    start++;
                    continue;
            }
            if (nums[start] + nums[end] < target) {
                start++;
            } else if (nums[start] + nums[end] > target) {
                end--;
            } else {
				returnNums = (int**) realloc(returnNums, sizeof(int*) * ((*returnSize)+1));
                returnNums[*returnSize] = (int*)malloc(sizeof(int)*3);
                returnNums[*returnSize][0] = nums[i];
                returnNums[*returnSize][1] = nums[start];
                returnNums[*returnSize][2] = nums[end];
                (*returnSize)++;
                start++;
            }   
        }
    }
    
	return returnNums;
}

/* main */
int main(int argc, char** argv){
	//int nums[6] = {-1,0,1,2,-1,-4};
	int nums[17] = {-1, -2, -3, 4, 1, 3, 0, 3, -2, 1, -2, 2, -1, 1, -5, 4, -3};
	int numsSize = 17;
	int *returnSize;
	
	int **returnNums = threeSum(nums, numsSize, returnSize);
	printf("returnSize %d\n", *returnSize);
	
	// print result
	for(int row = 0; row < *returnSize; row++){
		printf("[");
		for(int col = 0; col < 3; col++)
			printf("%d ", returnNums[row][col]);
		printf("]\n");
	}

	return 0;
}
