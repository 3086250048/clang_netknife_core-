#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void cat_test(char * s1,char *s2){
	
	char * s3 = strcat(s1,s2);
	printf("%s\n",s3);
}


static unsigned int netknife_index_hash(char * filename, int  child_type ,char * child_name){
char * s1 =strdup(filename);
	char s2[10] ;
	sprintf(s2,"%d",child_type);
	char * s3= strdup(child_name);
	strcat(s1,s2);
	strcat(s1,s3);
	unsigned int hash = 0;
	unsigned c ;
	char * tmp =s1;
	while(c=*tmp++){
		   	hash = hash*9 ^ c;
	}
	free(s1);
	free(s3);
	return hash;
}



int main(){
	int hash = netknife_index_hash("你好",220,"f2uck");
	printf("%ld\n",hash);
}
