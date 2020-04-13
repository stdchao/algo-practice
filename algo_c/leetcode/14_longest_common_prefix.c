#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestCommonPrefix(char** strs, int strsSize) {
	if(strs == NULL || *strs == NULL)
	return "";

	int preLen = 0;
	//
	int str0size = strlen(strs[0]);
	for(int i = 0; i < str0size; i++){
		for(int j = 1; j < strsSize; j++){
			if(strs[j][i] != strs[0][i]){
				// break loop
				i = str0size;
				break;                                                                                  }
		}	
		if(i < str0size)
			preLen++;
	}
	
	char *prefix = (char*)malloc(sizeof(char)*(preLen+1));
	for(int i=0; i< preLen; i++)
		prefix[i] = strs[0][i];
	prefix[preLen] = '\0';
	
	return prefix;
}

int main(int argc, char** argv){
	char* strs[] = {"a", "ac"};
	int strsSize = 2;
	
	char* prefix = longestCommonPrefix(strs, strsSize);
	free(prefix);	
	printf("result %s\n", prefix);

return 0;
}

