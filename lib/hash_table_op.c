#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>





static void rule_reverse(struct rule_table * root){
	if(!root->dup_r )  return ;
	struct rule_table * pre,* cur,* nex;
	pre=NULL;
	cur=root;
	while(cur!=NULL){
		nex=cur->dup_r;
		cur->dup_r = pre;
		pre=cur;
		cur=nex;
	}
	root = pre;
}
static void comment_reverse(struct comment_table * root){
	if(!root->dup_c )  return ;
	struct comment_table * pre,* cur,* nex;
	pre=NULL;
	cur=root;
	while(cur!=NULL){
		nex=cur->dup_c;
		cur->dup_c = pre;
		pre=cur;
		cur=nex;
	}
	root = pre;
}


static unsigned int index_string_hash(char * index_string){
	unsigned int hash = 0;
	unsigned c ;
	while(c=*index_string++) hash = hash*9 ^ c;
	return hash;
}

//添加rule到表中
struct rule_table * join_rule_table(struct rule * r){
	struct rule_table  * tmp = &rule_tab[index_string_hash(cat_string(r->s))%MAX_HASH];
	    if(tmp->r != NULL){
			struct rule_table * dup = malloc(sizeof(struct rule_table));
			dup->node_type = RULE_TABLE_NODE;
			dup->r = r ;
			dup->dup_r  = tmp;
			tmp = dup ;
			rule_reverse(tmp);		
			return tmp;
		}
		if(tmp->r == NULL){
			tmp->node_type = RULE_TABLE_NODE;
			tmp->r = r;
		   	tmp->dup_r = NULL;
			return tmp;	
		}
}


//添加comment 到表中
struct comment_table * join_comment_table(struct comment * c){
	struct comment_table  * tmp =&comment_tab[index_string_hash(cat_string(c->c))%MAX_HASH];
			if(tmp->c){
				struct comment_table * dup = malloc(sizeof(struct comment_table));
				dup->node_type = COMMENT_TABLE_NODE;
				dup->c = c ;
				dup->dup_c  = tmp;
				tmp = dup ;
				comment_reverse(tmp);		
				return tmp;
			}

			if(!tmp->c){
				tmp->node_type =COMMENT_TABLE_NODE;
				tmp->c = c;
				tmp->dup_c = NULL;
				return tmp;	
			}

}


//获取rule_table_entry
struct rule_table *  get_rule_table_entry(struct rule_table * rule_tab,struct index_string * s){
	
	struct rule_table  * tmp =&rule_tab[index_string_hash(cat_string(s))%MAX_HASH];
	if(!tmp->r) return NULL;
	return tmp;
}


//获取comment_table_entry
struct comment_table * get_comment_table_entry(struct comment_table * comment_tab ,struct index_string * c){
	
	struct comment_table  * tmp =&comment_tab[index_string_hash(cat_string(c))%MAX_HASH];
	if(!tmp->c) return NULL;
	return tmp;
}
//获取rule_table地址,重新分配空间给rule_tab
struct rule_table *  get_rule_table(){
	 struct rule_table * tmp = rule_tab;
	 rule_tab = NULL;
	 rule_tab = malloc(sizeof(struct rule_table)*MAX_HASH);
	 return tmp ; 
}

//获取comment_table地址,重新分配空间给comment_tab
struct comment_table * get_comment_table(){
	struct comment_table * tmp = comment_tab;
	comment_tab = NULL;
	comment_tab = malloc(sizeof(struct comment_table)*MAX_HASH);
	return tmp;
}

//打印rule_table表项
void print_rule_table_entry(struct rule_table * rule_tab){
	printf("node_type:RULE_TABLE\n");
	while(rule_tab)	{
		print_rule(rule_tab->r);
		rule_tab=rule_tab->dup_r;
	}	
}


//打印comment表项
void print_comment_table_entry(struct comment_table * comment_tab){
	printf("node_type:COMMENT_TABLE\n");
	while(comment_tab)	{
		print_comment(comment_tab->c);
		comment_tab=comment_tab->dup_c;
	}	
}








