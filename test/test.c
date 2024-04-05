#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void cat_test(char * s1,char *s2){
	
	char * s3 = strcat(s1,s2);
	printf("%s\n",s3);
}

#define PRINT 10," "
static unsigned int netknife_index_hash(char * filename, int  child_type ,char * child_name){
	char * s1 = malloc(strlen(filename));
	char * s2 = malloc(strlen(child_name));
	char s3[10];
	sprintf(s3,"%d",child_type);
	strcpy(s1,filename);
	strcpy(s2,child_name);
	char * netknife_index = strcat(s1,s2);
	netknife_index = strcat(netknife_index,s3);
	char * tmp = netknife_index; 
	unsigned int hash = 0;
	unsigned c ;
	while(c=*netknife_index++) hash = hash*9 ^ c;
	free(s1);
	free(s2);
	return hash;
}



int main(){
	int hash = netknife_index_hash("你好",220,"fuck");
	printf("%ld\n",hash);
}
