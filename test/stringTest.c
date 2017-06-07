#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mergeStrings(char* a, char* b){
	
	char* mergedStr;
	mergedStr = malloc( (strlen(a)+strlen(b)+1) * sizeof(char) );

	char* startPtr = mergedStr;
	
	while(*a != '\0' && *b != '\0'){
		*mergedStr++ = *a++;
		*mergedStr++ = *b++;
	}

	while (*a != '\0')
		*mergedStr++ = *a++;

	while (*b != '\0')
		*mergedStr++ = *b++;

	*mergedStr = '\0';

	return startPtr;
}


int main(int argc, char const *argv[])
{
	char* res;
	char* _a;
	_a = (char*)malloc(10240 * sizeof(char));
	scanf("\n%[^\n]", _a);

	char* _b;
	_b = (char*)malloc(10240 * sizeof(char));
	scanf("\n%[^\n]", _b);

	res = mergeStrings(_a, _b);

	printf("%s\n", res);

	return 0;
}
