#include <stdio.h>
#include <string.h>

int containsDuplicate(int* nums, int numsSize) {
    if(nums == NULL || numsSize <2)
        return 0;
    
    int max = nums[0];
    int min = nums[0];
    for(int i = 1; i < numsSize; i++){
        max = nums[i] > max? nums[i]: max;
        min = nums[i] < min? nums[i]: min;
    }
    
    int len = max - min + 1;
    int count[len];
    memset(count, 0, sizeof(count));
    
    for(int i = 0; i < numsSize; i++){
        int key = (nums[i] - min) % len;
        if(count[key] > 0)
            return 1;
        
        count[key]++;
    }
    return 0;
}

int main(int argc, char** argv){
	int nums[2] = {2,2};
	int numsSize = 2;
	if(containsDuplicate(nums, numsSize))
		printf("contains duplicate\n");
	else
		printf("not contains duplicate\n");

	return 0;
}
