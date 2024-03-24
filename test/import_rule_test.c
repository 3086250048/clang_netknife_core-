#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"



int main(){

	//regx	
	struct index_string * s1=join_index_string(s1,"^dispay");
	s1=join_index_string(s1,"[^adwawd]");
	join_regx(string(s1));
	struct index_string * s2=join_index_string(s2,"^show");
	s2=join_index_string(s2,"[^abc]");
	join_regx(string(s2));
	struct regx * r =  get_regx();

	//range 
	struct index_string * s3 = join_index_string(s3,"huawei_to_cisco");
	struct index_string * s4 = join_index_string(s4,"ruijie_to_huawei");
	join_range(100,200,string(s3),string(s4));
	join_range(0,0,string(s3),NULL);
	struct range * range_1 = get_range();
	join_range(10,20,string(s4),NULL);
	join_range(0,0,NULL,string(s3));
	struct range * range_2 = get_range();


	//include 
	
		struct include * i = join_include(i,r,range_1);
		print_include(i);
	//exclude
		struct exclude * e = join_exclude(e,r,range_2);
		print_exclude(e);
	//import_rule 
	    join_import_rule("CISCO_2730_TEST",100,i,e);
	    join_import_rule("HUAWEI_2730_TEST",100,i,e);
		struct import_rule * import_rule_root = get_import_rule();
		print_import_rule(import_rule_root);

}
