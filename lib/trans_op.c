#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

static struct trans * trans_tab = malloc(sizeof(struct trans)*MAX_HASH);

struct trans * join_trans(int lineno , char * trans_name , struct rule_table * rule_tab , struct comment_table * comment_tab ,struct import_rule * import_rule_chain ){
	struct trans * tmp = malloc(sizeof(struct trans));
	tmp->node_type = TRANS;
	tmp->filename = __FILE__;
	tmp->trans_name = trans_name ;
	tmp->rule_tab = rule_tab ;
	tmp->comment_tab = comment_tab;
	tmp->import_rule_chain = import_rule_chain;
	return tmp;
}




static unsigned int trans_index_hash(char * trans_name,char * filename){
	char *  trans_index = strcat(trans_name , filename);
	unsigned int hash = 0;
	unsigned c ;
	while(c=*trans_index++) hash = hash*9 ^ c;
	return hash;
}

//添加rule到表中
struct trans  * join_trans_table(struct  trans * trans){
	struct rule_table  * tmp = trans_tab[trans_index_hash(trans->filename,trans->trans_name)%MAX_HASH];
		if(!tmp->trans_name){
			memcpy(tmp,trans,sizeof(struct trans));
			free(trans);
			return tmp;	
		}
}


struct trans * get_trans_table(){
		return trans_tab;
}
