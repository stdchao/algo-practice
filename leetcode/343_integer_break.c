#include <stdio.h>
#include <string.h>

int max(a, b){
	return a > b? a: b;
}

int integerBreak(int n) {
    int c[n+1];
    memset(c, 0, sizeof(c));
    
    for(int i = 2; i < n+1; i++){
        for(int j = 1; j < i; j++){
            int tmp = max(c[i-j], i-j) * max(c[j], j);
            c[i] = max(c[i], tmp);
        }
    }
    return c[n];
}

int main(int argc, char** argv){
	for(int i =2; i < 20; i++)
		printf("IntegerBreak [%d,%d]\n", i, integerBreak(i));

	return 0;
}
