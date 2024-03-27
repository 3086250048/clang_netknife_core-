#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "netknife.h"

int main(){
    struct index_string * s=join_index_string(s," ");
    s=join_index_string(s,"this");
    s=join_index_string(s," ");
    s=join_index_string(s,"is");
    s=join_index_string(s," ");
	char * a= cat_string(string(s));
	printf("%s\n",a);

}
