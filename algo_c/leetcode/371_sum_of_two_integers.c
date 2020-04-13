#include <stdio.h>

/*
 * function: sum of two integers 	
 * method: bit operation(&, ^, ~)
 */ 

int getSum(int a, int b){
	if(a == 0) return b;
	if(b == 0) return a;
	
	while(b != 0){
		int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

int main(int argc, char** argv){
	int a, b;
	printf("please input two integers:\n");
	scanf("%d", &a);
	scanf("%d", &b);
	printf("sum of %d and %d is %d.\n", a, b, getSum(a, b));
	return 0;
}
