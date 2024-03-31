#include <stdlib.h>
#include <stdio.h>
#include "netknife.h"

int main(){
	//初始化表
	init();
	//初始化index_string
    struct index_string * s1= join_index_string(s1,"this is s1");
    struct index_string * d1= join_index_string(d1,"this is d1");
    struct index_string * s2= join_index_string(s2,"this is s2");
    struct index_string * d2= join_index_string(d2,"this is d2");

	//初始化rule
	struct rule * r1=join_rule(string(s1),string(d1),99,1);
	struct rule * r2=join_rule(string(s2),string(d2),99,1);
	struct rule * r3=join_rule(string(s1),string(d2),99,1);
	struct rule * r4=join_rule(string(s2),string(d1),99,1);
	struct rule * r5=join_rule(string(s2),string(d1),99,1);
	struct rule * r6=join_rule(string(s2),string(d2),99,1);


	//初始化comment
	struct comment * c1= join_comment(string(s1),100);
	struct comment * c2= join_comment(string(s1),100);
	struct comment * c3= join_comment(string(s1),199);

	//加到hash表中
	join_rule_table(r1);	
	join_rule_table(r2);	
	join_rule_table(r3);	
	join_rule_table(r4);	
	join_rule_table(r5);	
    struct rule_table *  r_tab = join_rule_table(r6);	
	
	join_comment_table(c1);
	join_comment_table(c2);
	struct comment_table * c_tab =  join_comment_table(c3);

	//获取表的地址，并重置表
	struct rule_table * rule_tab= get_rule_table();
	struct comment_table * comment_tab = get_comment_table();
	
	//根据index_string 获取表项
	struct rule_table * rule_tab_entry_1= get_rule_table_entry(rule_tab,s1);
	struct rule_table * rule_tab_entry_2= get_rule_table_entry(rule_tab,s2);

	struct comment_table * comment_tab_entry_1 = get_comment_table_entry(comment_tab,s1);

	//打印获取的表项
	print_rule_table_entry(rule_tab_entry_1 );
	print_rule_table_entry(rule_tab_entry_2 );
	print_comment_table_entry(comment_tab_entry_1);

	
		

}
