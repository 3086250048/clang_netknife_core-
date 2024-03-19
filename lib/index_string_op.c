#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

static struct  index_str * index_str_root = NULL;


//反转
static  void reverse_index_string(){
	//如果只存在一个节点则直接退出
	if(!index_str_root->next) return ;

	index_str * pre,* cur,* nex;
	pre=NULL;
	cur=index_str_root;
	while(cur!=NULL){
		nex=cur->next;
		cur->next = pre;
		pre=cur;
		cur=nex;
	}
	index_str_root = pre;
}

//去除index_str两端空格
static void  drop_index_string_htempty(){
		//如果只存在一个节点,则直接退出
		if(!index_str_root->next  ) return ;

		struct index_str * tmp = index_str_root ;
		if(!(tmp->s) && tmp->next->s ){
			index_str_root = tmp->next;
			free(tmp);
			struct index_str * tmp = index_str_root;
		}
		index_str * prev ;
		while(tmp->next){
			prev = tmp ;
			tmp=tmp->next;
		}
		if(!(tmp->s)){
			prev->next=NULL;
			free(tmp);
		}

}
//添加字符到index_str 
struct index_string * join_index_string(char * str){	
   	struct index_str * tmp = malloc(sizeof(struct index_str)) ;
	tmp->node_type=INDEX_STRIGN;
	tmp->s=str;
	tmp->next = index_str_root;
	index_str_root = tmp ;

	
	reverse_index_string();
	drop_index_string_htempty();
	
	return tmp;
}


//打印ndex_string
void print_index_string(){
    struct index_str * tmp =index_str_root;
	while(tmp != NULL){
		printf("%s",tmp->s);
		tmp=tmp->next;
	}
	printf("\n");
}
//获取index_string,并让根指向NULL
struct index_string * get_index_string( ){
	struct index_string * tmp = index_str_root;
	index_str_root = NULL;
	return tmp;
}

//释放index_string
void free_index_string(struct index_string * root ){
	while(root){
		struct index_string * tmp =root;
		root=root->next;
		free(tmp);
	}
}


