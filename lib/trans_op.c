#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


struct trans * join_trans(char * filename ,char * trans_name,int lineno , struct rule_table * rule_tab , struct comment_table * comment_tab ,struct import_rule * import_rule_chain ){
	struct trans * tmp = malloc(sizeof(struct trans));
	tmp->node_type = TRANS;
	tmp->filename = filename ;
	tmp->trans_name = trans_name ;
	tmp->lineno=lineno;
	tmp->rule_tab = rule_tab ;
	tmp->comment_tab = comment_tab;
	tmp->import_rule_chain = import_rule_chain;
	return tmp;
}

static unsigned int trans_index_hash(char * filename,char * trans_name){
	char * s1 = malloc(strlen(filename));
	char * s2 = malloc(strlen(trans_name));
	strcpy(s1,filename);
	strcpy(s2,trans_name);
	char * trans_index = strcat(s1,s2);
	unsigned int hash = 0;
	unsigned c ;
	while(c=*trans_index++) hash = hash*9 ^ c;
	return hash;
}

//添加rule到表中
struct trans_table   * join_trans_table(struct  trans * trans){	
	struct trans_table * tmp = &trans_tab[trans_index_hash(trans->filename,trans->trans_name)%MAX_HASH];
			
		if(!tmp->trans){
			tmp->trans = trans;
			return  tmp ;
		}else{
			printf("trans_table hash confilct\n");
		}
}

//获取rule表表项
struct trans * get_trans_table_entry(struct trans_table * trans_tab , char * filename , char * trans_name){
		struct trans_table * tmp = &trans_tab[trans_index_hash(filename,trans_name)%MAX_HASH];
		
		if(tmp->trans){
				return tmp->trans;
		}else{
		 	printf("trans_table no has this entry\n");
		}	
}

//获取表地址
struct trans_table * get_trans_table(){
		struct trans_table * tmp = trans_tab ;
		trans_tab = malloc(sizeof(struct trans_table)*MAX_HASH);
		return tmp;
}

//打印trans_table表项
void print_trans_table_entry(struct trans * trans){
	printf("node_type:TRANS\n");
	printf("filename:%s\n",trans->filename);
	printf("trans_name:%s\n",trans->trans_name);
	printf("lineno:%d\n",trans->lineno);
	int i;
	for(i=0;i<MAX_HASH;i++){
		if((trans->rule_tab)[i].r){
			print_rule_table_entry(&(trans->rule_tab)[i]);
		}
	}
	for(i=0;i<MAX_HASH;i++){
		if((trans->comment_tab[i].c)){
			print_comment_table_entry(&(trans->comment_tab)[i]);
		}
	}
	print_import_rule(trans->import_rule_chain);
}

