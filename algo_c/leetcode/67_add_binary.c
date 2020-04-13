#include <string.h>

char* addBinary(char* a, char* b){
	int lenA =strlen(a);
	int lenB = strlen(b);

	char* longC;
	char* shortC;
	int lenL, lenS;
	if(lenA > lenB){
		longC = a;
		lenL = lenA;
		shortC = b;
		lenS = lenB;
	}else{
		longC = b;
		lenL = lenB;
		shortC = a;
		lenS = lenA;
	}

	int indexL = lenL - 1;
	int indexS = lenS - 1;
	int carry = 0;
	while(indexL >= 0){
		int valL = longC[indexL] - '0';

		int valS = 0;
		if(indexS >= 0){
			valS = shortC[indexS--] - '0';
		}
	
		int sum = valL + valS + carry;
		carry = sum / 2;
		longC[indexL--] = sum % 2 + '0';

		if(indexS < 0 && carry == 0)
			return longC;
	}
	
	if(carry == 1){
		char* newlongC = (char*) malloc(sizeof(char) * (lenL+1));
		newlongC[0] = '1';
		strcpy(newlongC+1, longC);
		return newlongC;

	}else{
		return longC
	}
}

