#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"

int main(){
	//初始化表
	init();
	//初始化rule的index_string
	join_index_string("this is s1");
	struct index_string * s1 = get_index_string();
	join_index_string("this is d1");
	struct index_string * d1 = get_index_string();
	join_index_string("this is s2");
	struct index_string * s2 = get_index_string();
	join_index_string("this is d2");
	struct index_string * d2 = get_index_string();
	//初始化rule
	struct rule * r1=join_rule(s1,d1,99,1);
	struct rule * r2=join_rule(s2,d2,99,1);
	struct rule * r3=join_rule(s1,d2,99,1);
	struct rule * r4=join_rule(s2,d1,99,1);

	//初始化comment的index_string 
	join_index_string("this is str1");
	struct index_string  * str1 = get_index_string();
	join_index_string("this is str2");
	struct index_string  * str2 = get_index_string();
	//初始化comment
	struct comment * c1= join_comment(str1,100);
	struct comment * c2= join_comment(str2,100);
	struct comment * c3= join_comment(str2,199);

	//加到hash表中
	join_rule_table(r1);	
	join_rule_table(r2);	
	join_rule_table(r3);	
	join_rule_table(r4);	
	join_comment_table(c1);
	join_comment_table(c2);
	join_comment_table(c3);

	//获取表的地址，并重置表
	struct rule_table * rule_tab= get_rule_table();
	struct comment_table * comment_tab = get_comment_table();


	//regx	
		join_index_string("^dispay");
		join_index_string("[^adwawd]");
		join_regx(get_index_string());
		join_index_string("^show");
		join_index_string("[^abc]");
		join_regx(get_index_string());
		struct regx * r =  get_regx();
	//include 
		join_include(100,200,NULL,NULL);
		join_index_string("huawei_to_cisco");
		struct index_string * s3 = get_index_string();
		join_index_string("cisco_to_huawei");
		struct index_string * s4 = get_index_string();
		join_include(NULL,NULL,s3,s4);
		struct include * i = get_include();
	//exclude
		join_exclude(100,200,NULL,NULL);
		join_index_string("huawei_to_exclude");
		struct index_string * s5 = get_index_string();
		join_index_string("cisco_to_exlcude");
		struct index_string * s6 = get_index_string();
		join_exclude(NULL,NULL,s5,s6);
		struct exclude * e = get_exclude();
	//import_rule 
	    join_import_rule("CISCO_2730_TEST",100,r,i,e);
	    join_import_rule("HUAWEI_2730_TEST",100,r,i,e);
		struct import_rule * import_rule_root = get_import_rule();
		
	
	//trans 
	struct trans * trans_entry_1 = join_trans(__FILE__,"CISCO_TO_RUIJIE",100,rule_tab,comment_tab,import_rule_root);
	struct trans * trans_entry_2 = join_trans(__FILE__,"HUAWEI_TO_RUIJIE",200,rule_tab,comment_tab,import_rule_root);
	
	join_trans_table(trans_entry_1);
	join_trans_table(trans_entry_2);
	struct trans_table * trans_tab = get_trans_table();
	struct trans * trans_tab_entry_1 = get_trans_table_entry(trans_tab,__FILE__,"CISCO_TO_RUIJIE");
	struct trans * trans_tab_entry_2 = get_trans_table_entry(trans_tab,__FILE__,"HUAWEI_TO_RUIJIE");

	print_trans_table_entry(trans_tab_entry_1);	
	print_trans_table_entry(trans_tab_entry_2);	


	
}
