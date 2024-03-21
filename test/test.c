#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void cat_test(char * s1,char *s2){
	
	char * s3 = strcat(s1,s2);
	printf("%s\n",s3);
}

int main(){
	char * s1 = malloc(8);
	char * s2 = malloc(10);
	printf("%d\n",strlen("test1"));
	strcpy(s1,"test1");
	strcpy(s2,"test2");

	cat_test(s1,s2);
}
