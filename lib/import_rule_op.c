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


struct include * join_include(struct include * root , struct range * range ){
	 struct include * tmp =  malloc(sizeof(struct include));
	 tmp->node_type = INCLUDE_NODE ;
	 tmp->range =range;
	 tmp->next = root;
	 root = tmp ;
	 return root ;
}



void print_include(struct include * include){
		while(include){	
	 	printf("%*snode_type:INCLUDE\n",PRINT_INCLUDE);
	 	print_range(include->range);
		include=include->next;
		}
}




struct exclude * join_exclude(struct exclude *root ,struct range * range ){
	struct exclude * tmp =  malloc(sizeof(struct exclude));
	tmp->node_type = EXCLUDE_NODE ;
	tmp->range=range;
	tmp->next= root;
	root=tmp;
	return root ;
}


void print_exclude(struct exclude * exclude){
		while(exclude){
		printf("%*snode_type:EXCLUDE\n",PRINT_EXCLUDE);
		print_range(exclude->range);
		exclude=exclude->next;
		}

}

struct  import_rule * join_import_rule(char * import_name , int lineno,struct include * inc , struct exclude * exc){
	struct import_rule * tmp = malloc(sizeof(struct import_rule));
	tmp->node_type = IMPORT_NODE;
	tmp->lineno = lineno ;
	tmp->import_name=import_name;
	tmp->inc =inc;
	tmp->exc=exc;
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
		printf("%*simport_name:%s\n",PRINT_IMPORT,tmp->import_name);
		printf("%*slineno:%d\n",PRINT_IMPORT,tmp->lineno);
		print_include(tmp->inc);
		print_exclude(tmp->exc);
		tmp = tmp->next;
	}
}

