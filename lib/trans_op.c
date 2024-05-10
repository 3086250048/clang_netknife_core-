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

struct trans *  trans_reduce()
{
	if(file_stack_count > 1 && !target_trans) return NULL;
	if(file_stack_count > 1 && !transcmp(target_trans , cur_trans )  && !transcmp(target_trans , cur_trans) ) return NULL;	
	if(popimport()){
		import_state = 1;
		if(file_stack_count == 1 ){start_trans = cur_trans;}
		if(newfile(curfilename)){
			yyparse();
		}
	}else{
		if(transcmp(target_trans , ALL_TRANS)) return NULL;
		char * trans ;
		if( import_state ){	
			import_state = 0;
			struct trans * t= join_trans(start_trans,yylineno,get_rule_table(),get_comment_table(),get_import_rule());
			start_trans = NULL;
			target_trans = NULL;
			print_trans(t);
			printf("\n");
			return t ;
		}
		if(file_stack_count == 1){
			struct trans * t= join_trans(cur_trans,yylineno,get_rule_table(),get_comment_table(),get_import_rule());
			print_trans(t);
			printf("\n");
			return t ;
		}
		return NULL;
	}	
}








