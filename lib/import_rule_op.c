#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


static struct import_rule * import_rule_root = NULL;


struct range * join_range(struct range * root , char * regx ,int s_lineno ,int d_lineno ,char * s_comment,char * d_comment )
{
	struct range * tmp = malloc(sizeof(struct range));
	tmp->node_type = RANGE_NODE;
	tmp->regx = regx;
	tmp->s_lineno = s_lineno;
	tmp->d_lineno = d_lineno;
	tmp->s_comment = s_comment;
	tmp->d_comment = d_comment;
	tmp->next = root;
	root = tmp;
	return root ;
}




void print_range(struct range * range_root){
	 struct range * tmp = range_root ;
	 while(tmp){
	 	printf("%*snode_type:RANGE_NODE\n",PRINT_RANGE);
		printf("%*sregx:%s\n",PRINT_RANGE,tmp->regx);
		printf("%*ss_lineno:%d\n",PRINT_RANGE,tmp->s_lineno);
		printf("%*sd_lineno:%d\n",PRINT_RANGE,tmp->d_lineno);
		printf("%*ss_comment:%s\n",PRINT_RANGE,tmp->s_comment);
		printf("%*sd_comment:%s\n",PRINT_RANGE, tmp->d_comment);
		tmp=tmp->next;
	 }

}


struct filter * join_filter(struct filter * root , int node_type ,struct range * range){
		struct filter *  tmp = malloc(sizeof(struct filter));
		tmp->node_type = node_type ;
		tmp->range=range;
		tmp->next = root;
		root = tmp;
		return root;
}

void print_filter(struct filter * filter_root){
	while(filter_root){
		if(filter_root->node_type == INCLUDE_NODE){
			printf("%*snode_type:INCLUDE_NODE\n",PRINT_FILTER);
		}else{
			printf("%*snode_type:EXCLUDE_NODE\n",PRINT_FILTER);	
		}
		print_range(filter_root->range);
		filter_root=filter_root->next;
	}
}


struct  import_rule * join_import_rule(char * file_name ,char * import_name , int lineno,struct filter * filter ){
	struct import_rule * tmp = malloc(sizeof(struct import_rule));
	tmp->node_type = IMPORT_NODE;
	tmp->lineno = lineno ;
	tmp->file_name = file_name ;
	tmp->import_name=import_name;
	tmp->filter = filter ;
	tmp->next = import_rule_root ;
	import_rule_root = tmp ;
	return  tmp ;
}


struct import_rule * get_import_rule(){
	struct import_rule * tmp = import_rule_root;
	import_rule_root = NULL;
	return tmp ;
}


void print_import_rule(struct import_rule * import_rule_root){
	struct import_rule * tmp = import_rule_root;
	while(tmp){
		printf("%*snode_type:IMPORT\n",PRINT_IMPORT);
		printf("%*sfile_name:%s\n",PRINT_IMPORT,tmp->file_name);
		printf("%*simport_name:%s\n",PRINT_IMPORT,tmp->import_name);
		printf("%*slineno:%d\n",PRINT_IMPORT,tmp->lineno);
		print_filter(tmp->filter);
		tmp = tmp->next;
	}
}


