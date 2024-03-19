#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"


int main(){
	join_index_string("this is test1");
	join_index_string("this is test2");
	join_index_string("this is test3");
	join_index_string("this is test4");
	join_index_string("this is test5");
	join_index_string("this is test6");
	print_index_string();
    get_index_string();	
	join_index_string("this is test1");
	join_index_string("this is test2");
	print_index_string();
	struct index_string * root = get_index_string();
	printf("%s \n",cat_string(root));
	join_index_string("this is test5");
	join_index_string("this is test6");
	root = get_index_string();
	printf("%s \n",cat_string(root));
	


	


}
