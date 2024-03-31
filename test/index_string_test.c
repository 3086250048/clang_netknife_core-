#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "netknife.h"
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

int main(){
    struct index_string * s=join_index_string(NULL," ");
    s=join_index_string(s,"t这");
    s=join_index_string(s,"is");	
    s=join_index_string(s," ");
    s=join_index_string(s,"你好");
	print_index_string(s);


}
