#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>



struct trans * join_trans(char *  name ,int lineno , struct rule_table * rule_tab  ,struct import_rule * import_rule_chain ){
	
	struct trans  * tmp = malloc(sizeof(struct trans));
		tmp->node_type = TRANS_NODE;
		tmp->name = name ;
		tmp->lineno=lineno;
		tmp->rule_tab = rule_tab ;
		tmp->comment_tab = NULL;
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
/*	if(trans->comment_tab)
	for(i=0;i<MAX_HASH;i++){
		if((trans->comment_tab[i].c)){
			print_comment_table_entry(&(trans->comment_tab)[i]);
		}
	}*/
	if(trans->import_rule_chain)
	print_import_rule(trans->import_rule_chain);
}

int transcmp(char * t1 , char * t2){
	if(!t1 || !t2 )return 0;
	if(strcmp(t1,t2) == 0) return 1;
	return 0;
}


struct trans *  trans_reduce()
{
	if(ACCEPT){
		while(Top(&rule_stack)){
			struct rule * rule = Top(&rule_stack)->buffer;	
			rule = Filter(rule);
			if(rule){
				join_rule_table(rule);
			}	
			Pop(&rule_stack);
		}
	
		struct import_info * import_info = Top(&import_stack)->buffer;
		import_info = Filter(import_info);
		if(import_info){
			join_import_rule(import_info->file_name,import_info->import_name , import_info->lineno , import_info->filter);
			struct filter * plfilter = Top(&PreLevelFilterStack)->buffer; 
			struct filter * filter = import_info->filter;
			while(filter->next){
				filter=filter->next;
			}	
			filter->next = plfilter ;
			Push(&PreLevelFilterStack,curfilename,cur_trans,import_info->filter->node_type ,import_info->filter);	
			curfilter = filter ;		
			if(file_stack_count ==1 ){ start_trans = cur_trans; }
			if( newfile(import_info->file_name) ){
				yyparse();	
			}
		}else{
			if(start_trans ){
				start_trans=NULL;
				 return  join_trans(start_trans,yylineno,get_rule_table(),get_import_rule());	
			}else{
				 return join_trans(cur_trans,yylineno , get_rule_table(),get_import_rule());	
			}		
		}
	}	
}










