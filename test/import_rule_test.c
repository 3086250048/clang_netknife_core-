#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"



int main(){
	//regx	
		join_index_string("^dispay");
		join_index_string("[^adwawd]");
		join_regx(get_index_string());
		join_index_string("^show");
		join_index_string("[^abc]");
		join_regx(get_index_string());
		struct regx * r =  get_regx();
		print_regx(r);
	//include 
		join_include(100,200,NULL,NULL);
		join_index_string("huawei_to_cisco");
		struct index_string * s1 = get_index_string();
		join_index_string("cisco_to_huawei");
		struct index_string * s2 = get_index_string();
		join_include(NULL,NULL,s1,s2);
		struct include * i = get_include();
		print_include(i);
	//exclude
		join_exclude(100,200,NULL,NULL);
		join_index_string("huawei_to_exclude");
		struct index_string * s3 = get_index_string();
		join_index_string("cisco_to_exlcude");
		struct index_string * s4 = get_index_string();
		join_exclude(NULL,NULL,s1,s2);
		struct exclude * e = get_exclude();
		print_exclude(e);
	//import_rule 
	    join_import_rule("CISCO_2730_TEST",100,r,i,e);
	    join_import_rule("HUAWEI_2730_TEST",100,r,i,e);
		struct import_rule * import_rule_root = get_import_rule();
		print_import_rule(import_rule_root);

}
