int* getRow(int rowIndex, int* returnSize){
	*returnSize = rowIndex + 1;
	int** trigArray = (int**) malloc (sizeof(int*) * (*returnSize));
	
	trigArray[0] = (int*) malloc (sizeof(int));
	trigArray[0][0] = 1;

	for(int i = 1; i <= rowIndex; i++){
		int length = i + 1;
		trigArray[i] = (int*) malloc (sizeof(int) * length);
		
		trigArray[i][0] = 1;
		trigArray[i][length-1] = 1;
		for(int j = 1; j < length-1; j++){
			trigArray[i][j] = trigArray[i-1][j-1] + trigArray[i-1][j];
		}
	}	
	return trigArray[rowIndex];
}
