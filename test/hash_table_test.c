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
	
	//根据index_string 获取表项
	struct rule_table * rule_tab_entry_1= get_rule_table_entry(rule_tab,s1);
	struct rule_table * rule_tab_entry_2= get_rule_table_entry(rule_tab,s2);

	struct comment_table * comment_tab_entry_1 = get_comment_table_entry(comment_tab,str1);
	struct comment_table * comment_tab_entry_2 = get_comment_table_entry(comment_tab,str2);

	
	//打印获取的表项
	print_rule_table_entry(rule_tab_entry_1);
	print_rule_table_entry(rule_tab_entry_2);
	print_comment_table_entry(comment_tab_entry_1);
	print_comment_table_entry(comment_tab_entry_2);

	
		

}
