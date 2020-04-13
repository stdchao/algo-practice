#include <string.h>
#include <stdio.h>

void reverseWords(char* s){
    if(s == NULL)
        return;
    
	int i = 0;
	int j = 0;
	while(s[i] != '\0'){
		printf("test 0 \"%s\", %d \"%c\" %d\n", s, i, s[i], j);
		// empty string
		if(s[i] == ' '){
			// i point to non-empty index
			while(s[i] == ' ') i++;

			// check tail
			if(s[i] == '\0')
				break;
			
			// j point to update index 
			if(j > 0) {
				s[j] = ' ';
				j++;
			}
		}
		printf("test 1 \"%s\", %d, \"%c\" %d\n", s, i, s[i], j);

		// get word start and end
		int start, end, jend;
		start = i;
		while(s[i] != ' ' && s[i] != '\0') 
			i++;
		end = i - 1;
		jend = j + end - start + 1;
		printf("test 2 %s, %d, %d, %d, %d, %d\n", s, i, start, end, j, jend);
		
		// reverse word
		while(start <= end && j <= jend){
			if(j < start){
				// update from j index
				s[j] = s[end];
				j++;
				printf("test 3 %s, %d, %d, %d\n", s, j, start, end);
			}else{
				// jump j point next to word end
				if(j == start)
					j = end + 1;
				char tmp = s[start];
				s[start] = s[end];
				s[end] = tmp;
				start++;
				printf("test 4 %s, %d, %d, %d\n", s, j, start, end);
			}
			end--;
			printf("test 5 %s, %d, %d, %d\n\n", s, j, start, end);
		}
	}

	// reverse string
	s[j] = '\0';
	printf("test 6 %s, %d\n", s, j);
	int start = 0;
	int end = j - 1;
	while(start < end){
		char tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
		start++;
		end--;
	}
}

int main(int argc, char** argv){
	char s[100] = " The sky is blue ";
	printf("raw string: %s\n", s);
	reverseWords(s);
	printf("reverse string: \"%s\"\n", s);

	return 0;
}
