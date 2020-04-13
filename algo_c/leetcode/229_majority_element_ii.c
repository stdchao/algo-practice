#include <string.h>
#include <limits.h>
#include "util.h"

/**
*  * Return an array of size *returnSize.
*   * Note: The returned array must be malloced, assume caller calls free().
*    */
int* majorityElement(int* nums, int numsSize, int* returnSize) {
    if(nums == NULL || numsSize == 0)
        return NULL;
    
    int candidate1 = 0, candidate2 = 1, count1 = 0, count2 = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] == candidate1){
            count1++;
        } else if(nums[i] == candidate2){
            count2++;
        } else if(count1 == 0) {
            candidate1 = nums[i];
            count1 = 1;
        } else if(count2 == 0) {
            candidate2 = nums[i];
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }
    
    count1 = 0;
    count2 = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] == candidate1)
            count1++;
        
        if(nums[i] == candidate2)
            count2++;
    }
    
    int* returnNums = NULL;
    if(count1 > numsSize/3){
        returnNums = (int*)malloc(sizeof(int));
        returnNums[*returnSize] = candidate1;
        (*returnSize)++;
    }
    
    if(count2 > numsSize/3){
        returnNums = (int*)realloc(returnNums, sizeof(int) * 2);
        returnNums[*returnSize] = candidate2;
        (*returnSize)++;
    }

    return returnNums;
}


//wrong anwser
int* majorityElement_error(int* nums, int numsSize, int* returnSize) {
    int threshold = numsSize/3;

    int min = nums[0], max = nums[0];
    for(int i = 1; i < numsSize; i++){
        min = nums[i] < min? nums[i]: min;
        max = nums[i] > max? nums[i]: max;
    }
    
    int len = max - min + 1;
	printf("%d, %d, %d\n", max, min, len);
    int count[len];
    memset(count, 0, sizeof(count));

    *returnSize = 0;
	int* returnNums = NULL;
	
    for(int i = 0; i < numsSize; i++){
		int key = (nums[i] - min) % len;
        if(count[key] != -1){
			if(++count[key] > threshold){
				returnNums = returnNums == NULL?
                            (int*) malloc(sizeof(int*)*(*returnSize+1)):
                            (int*) realloc(returnNums, sizeof(int)*(*returnSize+1));
                returnNums[(*returnSize)++] = nums[i];
				printf(">%d,%d,%d,%d\n", threshold, nums[i], *returnSize, returnNums[0]);
                count[key] = -1;
            }
        }
    }

    return returnNums;
}

int main(int argc, char** argv){
	int nums[3] = {6, 5, 5};
	//int nums[3] = { -1, -1, 2147483647};
	int numsSize = sizeof(nums)/sizeof(int);
	int *returnSize = (int*) malloc(sizeof(int));
	//
	int* returnNums = majorityElement(nums, numsSize, returnSize);
	//
	printArr(returnNums, *returnSize, -1);
	//
	int test = INT_MAX;
	printf("%d", test);
	return 0;
}
