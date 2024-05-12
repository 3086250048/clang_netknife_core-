#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A ""
int main() {
	char * a =  A;
	printf("%d\n",strlen(a));
	FILE * s = fopen(a , "w" );
	fprintf(s,"hello");


}

