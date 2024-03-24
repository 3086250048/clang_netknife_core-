#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>



//反转
static struct index_string *  reverse_index_string(struct index_string * root){
	//如果只存在一个节点则直接退出
	if(!root->next) return root;

	struct  index_string * pre,* cur,* nex;
	pre=NULL;
	cur=root;
	while(cur!=NULL){
		nex=cur->next;
		cur->next = pre;
		pre=cur;
		cur=nex;
	}
	root = pre;
	return root;
}

//去除index_str两端空格
static void  drop_index_string_htempty(struct index_string * root ){
		//如果只存在一个节点,则直接退出
		if(!root->next  ) return ;

		struct index_string * tmp = root ;
		if(!(tmp->s) && tmp->next->s ){
			root = tmp->next;
			free(tmp);
			struct index_string * tmp = root;
		}
		struct index_string * prev ;
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
struct index_string * join_index_string(struct index_string * root, char * str){	
   	struct index_string * tmp = malloc(sizeof(struct index_string)) ;
	tmp->node_type=INDEX_STRING;
	tmp->s=str;
	tmp->next = root;
	root = tmp ;	
	return root;
}


//打印ndex_string
void print_index_string(struct index_string * root){
    struct index_string * tmp =root;
	while(tmp != NULL){
		printf("%s",tmp->s);
		tmp=tmp->next;
	}
	printf("\n");
}
struct index_string * string(struct index_string * root ){
	root = reverse_index_string(root);
	drop_index_string_htempty(root);
	return root;
}



//释放index_string
void free_index_string(struct index_string * root ){
	while(root){
		struct index_string * tmp =root;
		root=root->next;
		free(tmp);
	}
	root=NULL;
}


//返回char*字符串
char * cat_string(struct index_string * root){
	struct index_string * tmp = root ;
	int size=0;
	while(tmp){
		size+=strlen(tmp->s);
		tmp=tmp->next; 
	};
	char * s = malloc(size);
	while(root){
		strcat(s,root->s);
		root=root->next;
	}
	return s;
}
