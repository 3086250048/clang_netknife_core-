#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


#define MAX_HASH 9999
struct rule_table  *rule_tab = malloc(sizeof(struct rule_table) * MAX_HASH);
struct comment_table *comment_tab = malloc(sizeof(struct comment_table) *MAX_HASH);

static void rule_reverse(struct rule_table * root){
	if(!root->dup_r )  return ;
	index_str * pre,* cur,* nex;
	pre=NULL;
	cur=root;
	while(cur!=NULL){
		nex=cur->next;
		cur->next = pre;
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
struct rule * join_rule_table(struct rule * r){
	struct rule_table  * tmp = rule_tab[index_string_hash(r->s)%MAX_HASH];
	    if(tmp->r){
			struct rule_table * dup = malloc(sizeof(struct rule_table));
			dup->node_type = RULE_TABLE;
			dup ->  rule = r ;
			dup -> dup_r  = tmp;
			tmp = dup ;
			rule_reverse(tmp);		
			return tmp;
		}

		if(!tmp->r){
			tmp->node_type = RULE_TABLE;
			tmp->r = r;
		   	tmp->dup_r = NULL;
			return tmp;	
		}
}



//添加comment 到表中
struct comment * join_comment_table(struct comment * c){
	struct comment_table  * tmp = comment_tab[index_string_hash(c->s)%MAX_HASH];
			if(tmp->c){
				struct comment_table * dup = malloc(sizeof(struct comment_table));
				dup->node_type = COMMENT_TABLE;
				dup ->  c = c ;
				dup -> dup_c  = tmp;
				tmp = dup ;
				reverse(tmp);		
				return tmp;
			}

			if(!tmp->c){
				tmp->node_type =COMMENT_TABLE;
				tmp->c = c;
				tmp->dup_r = NULL;
				return tmp;	
			}

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





