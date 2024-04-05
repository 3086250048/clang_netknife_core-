#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void cat_test(char * s1,char *s2){
	
	char * s3 = strcat(s1,s2);
	printf("%s\n",s3);
}

#define PRINT 10," "

int main(){
	char str[10];
	int a=1234;
	sprintf(str,"%d",a);
	printf("%s\n",str);
}
