#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"


int main(){
	join_index_string("this is test5");
	struct index_string * s = get_index_string();
	join_index_string("this is test6");
	struct index_string * d = get_index_string();
	
	printf("%s\n",cat_string(s));
	printf("%s\n",cat_string(d));

	struct rule * r=join_rule(s,d,99,1);

	print_rule(r);	
/*	join_index_string("this is testy");
	struct index_string  * str = get_index_string();
	struct comment * c= join_comment(str,100);
	print_comment(c);
*/
		

}
