#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"


int main(){
    struct index_string * s=join_index_string(s,"this is test1");
	s=join_index_string(s,"this is test5");
	s=join_index_string(s,"this is test6");
	s= string(s);
	printf("%s \n",cat_string(s));
}
