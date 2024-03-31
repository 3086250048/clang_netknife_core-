#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


static struct regx * regx_root = NULL;
static struct range * range_root = NULL;
static struct import_rule * import_rule_root = NULL;

struct regx * join_regx(char * exp){
	struct regx * tmp = malloc(sizeof(struct regx));
	tmp->node_type = REGX_NODE;
	tmp->exp = exp ;
	tmp->next = regx_root;
	regx_root = tmp;
	return tmp ;
}


struct regx * get_regx(){
	struct regx * tmp = regx_root ;
	regx_root = NULL;
	return tmp ;
}


void print_regx(struct regx * regx_root){
	 struct regx * tmp = regx_root ;
	 while(tmp){
	 	printf("%*snode_type:REGX_NODE\n",PRINT_REGX);
		printf("%*sexp:%s\n",PRINT_REGX,tmp->exp);
		tmp=tmp->next;
	 }

}


struct range * join_range(int s_lineno ,int d_lineno ,char * s_comment,char * d_comment )
{
	struct range * tmp = malloc(sizeof(struct range));
	tmp->node_type = RANGE_NODE;
	tmp->s_lineno = s_lineno;
	tmp->d_lineno = d_lineno;
	tmp->s_comment = s_comment;
	tmp->d_comment = d_comment;
	tmp->next = range_root;
	range_root = tmp;
	return tmp ;
}


struct range * get_range(){
	struct range * tmp = range_root ;
	range_root = NULL;
	return tmp ;
}


void print_range(struct range * range_root){
	 struct range * tmp = range_root ;
	 while(tmp){
	 	printf("%*snode_type:RANGE_NODE\n",PRINT_RANGE);
		printf("%*ss_lineno:%d\n",PRINT_RANGE,tmp->s_lineno);
		printf("%*sd_lineno:%d\n",PRINT_RANGE,tmp->d_lineno);
		printf("%*ss_comment:%s\n",PRINT_RANGE,tmp->s_comment);
		printf("%*sd_comment:%s\n",PRINT_RANGE, tmp->d_comment);
		tmp=tmp->next;
	 }

}


struct include * join_include(struct include *include , struct regx * regx , struct range * range ){
	if(!include){
	 	include  =  malloc(sizeof(struct include));
	}
	 include->node_type = INCLUDE_NODE ;
	 include->regx =regx ;
	 include->range =range;
	 return include ;
}



void print_include(struct include * include){
	 if(include){
	 	struct include * tmp = include ;
	 	printf("%*snode_type:INCLUDE_NODE\n",PRINT_INCLUDE);
	 	print_regx(tmp->regx);
	 	print_range(tmp->range);
	 }

}




struct exclude * join_exclude(struct exclude * exclude ,struct regx * regx ,struct range * range ){
	 if(!exclude){
   	 	exclude  =  malloc(sizeof(struct exclude));
	 }
	 exclude->node_type = EXCLUDE_NODE ;
	 exclude->regx =regx ;
	 exclude->range=range;
	 return exclude ;
}


void print_exclude(struct exclude * exclude){
	if(exclude){
		struct exclude * tmp = exclude ;
		printf("%*snode_type:EXCLUDE\n",PRINT_EXCLUDE);
		print_regx(tmp->regx);
		print_range(tmp->range);
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

