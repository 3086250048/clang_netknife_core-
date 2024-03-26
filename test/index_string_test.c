#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"


int main(){
    struct index_string * s=join_index_string(s,"this");
	s=join_index_string(s,"	");
	s=join_index_string(s,"is");
	print_index_string(s);
	s= string(s);

}
