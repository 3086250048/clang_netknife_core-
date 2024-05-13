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

int transcmp(char * t1 , char * t2){
	if(!t1 || !t2 )return 0;
	if(strcmp(t1,t2) == 0) return 1;
	return 0;
}

void t_join_rule_table (){
	struct buffer * tmp  = rule_chain ;
	while( tmp ){
			struct rule * rule = (struct rule *)tmp->buffer;
			rule = filter_rule(rule );
			if(rule){
				join_rule_table(rule);
			}
			tmp = tmp->next ;
	}
	while(rule_chain){
	struct buffer * r_tmp = rule_chain ;
	rule_chain=rule_chain->next ;
	free(r_tmp);
	}

	while(comment_chain){
	struct buffer * c_tmp = comment_chain;
	comment_chain  = comment_chain->next;
	free(c_tmp);
	}
	
	popfile();

}

struct trans *  trans_reduce()
{
	if(ACCEPT){
		struct buffer * top = Top(&token_stack);	
		if(top->type == RULE_NODE){
			struct rule * rule = top->buffer;
				
		}
		if(top->type == IMPORT_NODE){
			
			struct import_info * import_info = top->buffer; 
			if()

			struct filter * plfilter = Top(&PreLevelFilterStack)->buffer; 
			struct filter * filter = import_info->filter;
			while(filter->next){
				filter=filter->next;
			}
			filter->next = plfilter ;
			Push(&PreLevelFilterStack,curfilename,cur_trans,filter);	
			curfilter = filter ;
			

			
			}	
		}
	}

}








