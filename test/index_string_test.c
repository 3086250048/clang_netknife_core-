#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"


int main(){
	join_index_string("this is test1");
	join_index_string("this is test5");
	join_index_string("this is test6");
	struct index_string * root = get_index_string();
	printf("%s \n",cat_string(root));
	join_index_string("this is test5");
	join_index_string("this is test6");
	root = get_index_string();
	printf("%s \n",cat_string(root));
}
