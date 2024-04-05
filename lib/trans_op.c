#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


static unsigned int trans_index_hash(char * filename,char * trans_name){
	char * s1 = malloc(strlen(filename));
	char * s2 = malloc(strlen(trans_name));
	strcpy(s1,filename);
	strcpy(s2,trans_name);
	char * trans_index = strcat(s1,s2);
	unsigned int hash = 0;
	unsigned c ;
	while(c=*trans_index++) hash = hash*9 ^ c;
	free(s1);
	free(s2);
	return hash;
}



struct trans * join_trans_table(char * filename ,char * trans_name,int lineno , struct rule_table * rule_tab , struct comment_table * comment_tab ,struct import_rule * import_rule_chain ){
	struct trans  * tmp = &trans_tab[trans_index_hash(filename,trans_name)%MAX_HASH];
    if(tmp->node_type !=TRANS_NODE ){	
		tmp->node_type = TRANS_NODE;
		tmp->filename = filename ;
		tmp->trans_name = trans_name ;
		tmp->lineno=lineno;
		tmp->rule_tab = rule_tab ;
		tmp->comment_tab = comment_tab;
		tmp->import_rule_chain = import_rule_chain;
		return tmp;
	}else{
		perror("trans name conflict");exit(1);
	}
}

//获取表地址
struct trans * get_trans_table(){
		struct trans  * tmp = trans_tab ;
		trans_tab = calloc(MAX_HASH, sizeof(struct trans) );
		return tmp;
}

//打印trans_table表项
void print_trans(struct trans * trans){
	printf("%*snode_type:TRANS_NODE\n",PRINT_TRANS_TABLE_ENTRY);
	printf("%*sfilename:%s\n",PRINT_TRANS_TABLE_ENTRY,trans->filename);
	printf("%*strans_name:%s\n",PRINT_TRANS_TABLE_ENTRY,trans->trans_name);
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

