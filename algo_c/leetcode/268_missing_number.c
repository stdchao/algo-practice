// method 1: binary search
int missingNumber(int* nums, int numsSize) {
    if(nums == NULL || numsSize == 0)
        return 0;

	int left = 0;
	int right = numsSize -1;
	while(left < right){
		mid = (left + right) /2;
		if(nums[mid] < mid)
			right = mid;
		else
			left = mid + 1;
	}
	return left;
}

// method 2: sum
int missingNumber(int* nums, int numsSize) {
    if(nums == NULL || numsSize == 0)
        return 0;
    
    int sumN = numsSize;
    int sumNums = 0;
    for(int i = 0; i < numsSize; i++){
        sumN += i;
        sumNums += nums[i];
    }
    
    return sumN - sumNums;
}

// method3: xor
int missingNumber(int* nums, int numSize){
	if(nums == NULL || numsSize == 0)
		return 0;

	int res = numsSize;
	for(int i = 0; i < numsSize; i++){
		res ^= i;
		res ^= nums[i];
	}
	return res;
}
