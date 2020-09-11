#include <iostream>
#include <cstring>

using namespace std;

bool isSubStr(const char *text, const char* pattern){
	for(; *pattern == '*'; ++pattern);
	cout << *pattern << " ";
	if(*pattern == '\0'){
		return true;
	}
}

int main(){
	char text[] = "cabccbacbacba";
	char pattern[] = "****abcc*b*a*c*b*b*a";
	cout << (isSubStr(text, pattern) << endl;
	return 0;
}
