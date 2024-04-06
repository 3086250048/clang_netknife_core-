#include "netknife.h"
#include <ctype.h>
#include <string.h>


int main(){
	char * s;
    s=strdup("he \n \n \n llo \n wo \n rd");
    s=trim(s);
	int l=0;
	while(s[l]){
		if(s[l]=='\n'){printf("回车\n");}else{
		printf("%c\n",s[l]);
		}
		l++;
	}
}
