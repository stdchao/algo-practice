#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    //I(1)，V(5)，X(10)，L(50)，C(100)，D(500)，M(1000)	    
    char* charM[4] = {"", "M", "MM", "MMM"};
    char* charC[10] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	char* charX[10] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	char* charI[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	
	int iM = num/1000;
	int iC = (num%1000)/100;
	int iX = (num%100)/10;
	int iI = num%10;
	
	char* cM = charM[iM];
	char* cC = charC[iC];
	char* cX = charX[iX];
	char* cI = charI[iI];

	int len = strlen(cM) + strlen(cC) + strlen(cX) + strlen(cI) + 1;
	char* cNum = (char*) malloc(sizeof(char) * len);
	char* tempC = cNum; // store head pointer

	printf("[%d,%s] [%d,%s], [%d,%s] [%d,%s] %d\n", 
		iM, cM, iC, cC, iX, cX, iI, cI, len);

	while((*cNum++ = *cM++) != '\0');
	printf("%s, %s\n", tempC, cM);

	cNum--;
	while((*cNum++ = *cC++) != '\0');
	printf("%s, %s\n", tempC, cC);

	cNum--;
	while((*cNum++ = *cX++) != '\0')
	printf("%s, %s\n", tempC, cX);

	cNum--;
	while((*cNum++ = *cI++) != '\0')
	printf("%s, %s\n", tempC, cI);
	
	return tempC;
}

int main(int argc, char** argv){
	int test = 1;
	printf("%d to %s", test, intToRoman(test));

	return 0;
}

