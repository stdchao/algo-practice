#include <stdio.h>
#include "util.h"

/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n) {
    int** mat = NULL;
    
    if(n == 0)
        return mat;

	mat = (int**) malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++)
		mat[i] = (int*) malloc(sizeof(int)*n);
        
    int rowStart = 0, rowEnd = n-1, colStart = 0, colEnd = n-1;
    int num = 1;
    while(rowStart <= rowEnd && colStart <= colEnd){
        for(int i = colStart; i <= colEnd; i++){
            mat[rowStart][i] = num++;
        }
        rowStart++;
        
        for(int i = rowStart; i <= rowEnd; i++){
            mat[i][colEnd] = num++;
        }
        colEnd--;
        
        for(int i = colEnd; i >= colStart; i--){
            if(rowStart <= rowEnd)
                mat[rowEnd][i] = num++;
        }
        rowEnd--;
        
        for(int i = rowEnd; i >= rowStart; i--){
            if(colStart <= colEnd)
                mat[i][colStart] = num++;
        }
        colStart++;
    }
    
    return mat;
}

int main(int argc, char** argv){
	int n = 5;
	int** mat;
	mat = generateMatrix(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%5d", mat[i][j]);
		printf("\n");
	}	

	return 0;
}

