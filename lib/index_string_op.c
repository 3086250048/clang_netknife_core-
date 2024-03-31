#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

//去除index_str两端空格
static struct index_string *  drop_index_string_htempty(struct index_string * root) {
	struct index_string * tmp = root;
	while(tmp->s==NULL || strcmp(tmp->s," ")==0){
			free(tmp);
			tmp = root->next;
	}
	
	struct index_string * prev,*result =tmp ;
	if(!prev->next ) return result;
	while(tmp->next){
			prev = tmp ;
			tmp=tmp->next;
	}

	if(tmp->s == NULL || strcmp(tmp->s," ")==0){
			free(tmp);
			prev->next=NULL;			
	}

	return result ;
}


//添加字符到index_str 
struct index_string * join_index_string(struct index_string * root, char * str){	
   	struct index_string * tmp = malloc(sizeof(struct index_string)) ;
	tmp->node_type=INDEX_STRING_NODE;
	tmp->s=str;
	if(root==NULL){
	 tmp->next = root;
     root = tmp ;
	}else{
		struct index_string * tail=root;
		while(tail->next){
			tail = tail->next ;
		}
		tail->next=tmp;
	}	
	return root;
}

struct index_string * string(struct index_string * root){
	 printf("string_before\n");
	 root = drop_index_string_htempty(root);
	 printf("string_after\n");
	 return root ;
}


//打印ndex_string
void print_index_string(struct index_string * root){
    struct index_string * tmp =string(root);
	while(tmp){
		printf("%s",tmp->s);
		tmp=tmp->next;
	}
	printf("\n");
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
	printf("cat_before\n");
	struct index_string * tmp = root ;
	int size=0;
	while(tmp){
		size+=strlen(tmp->s);
		tmp=tmp->next; 
	};
	char * s = calloc(size,sizeof(char));
	while(root){
		strcat(s,root->s);
		root=root->next;
	}
	printf("cat_after\n");
	return s;
}
