#include "netknife.h"
#include <ctype.h>
#include <string.h>


int main(){
	char * s;
    s=strdup(" hello word");




    s=trim(s);

	int l=0;
	while(s[l]){
		if(s[l]=='\n'){printf("回车\n");}else{
		printf("%c\n",s[l]);
		}
		l++;
	}
}
