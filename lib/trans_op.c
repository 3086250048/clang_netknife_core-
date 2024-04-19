#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>



struct trans * join_trans(char *  name ,int lineno , struct rule_table * rule_tab , struct comment_table * comment_tab ,struct import_rule * import_rule_chain ){
	struct trans  * tmp = malloc(sizeof(struct trans));
		tmp->node_type = TRANS_NODE;
		tmp->name = name ;
		tmp->lineno=lineno;
		tmp->rule_tab = rule_tab ;
		tmp->comment_tab = comment_tab;
		tmp->import_rule_chain = import_rule_chain;
		return tmp;
}

//打印trans_table表项
void print_trans(struct trans * trans){
	printf("%*snode_type:TRANS_NODE\n",PRINT_TRANS_TABLE_ENTRY);
	printf("%*strans_name:%s\n",PRINT_TRANS_TABLE_ENTRY,trans->name);
	printf("%*slineno:%d\n",PRINT_TRANS_TABLE_ENTRY,trans->lineno);
	int i;
	if(trans->rule_tab)
	for(i=0;i<MAX_HASH;i++){
		if((trans->rule_tab)[i].r){
			print_rule_table_entry(&(trans->rule_tab)[i]);
		}
	}
	if(trans->comment_tab)
	for(i=0;i<MAX_HASH;i++){
		if((trans->comment_tab[i].c)){
			print_comment_table_entry(&(trans->comment_tab)[i]);
		}
	}
	if(trans->import_rule_chain)
	print_import_rule(trans->import_rule_chain);
}


struct trans *  trans_reduce()
{
	if( file_stack_count == 1 ){
		return join_trans(cur_trans,yylineno,get_rule_table(),get_comment_table(),get_import_rule());
	}
	
}







