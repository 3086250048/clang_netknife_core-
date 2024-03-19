#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


static struct regx * regx_root = NULL;
static struct include * include_root = NULL;
static struct exclude * exclude_root = NULL;
static struct import_rule * import_rule_root = NULL;



struct regx * join_regx(char * exp){
	struct regx * tmp = malloc(sizeof(struct regx));
	tmp->nodetype = REGX;
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


struct include * join_include(int s_lineno ,int d_lineno ,char * s_comment ,char * d_comment ){
	 struct include * tmp =  malloc(sizeof(struct include));
	 tmp->node_type = INCLUDE ;
	 tmp->s_lineno = s_lineno;
	 tmp->d_lineno = d_lineno ;
	 tmp->s_comment = s_comment;
	 tmp->d_comment = d_comment ;
	 tmp->next = include_root ;
	 return tmp ;
}


struct include * get_include(){
	struct include * tmp = include_root ;
	include_root = NULL;
	return tmp ;
}


struct exclude * join_exclude(int s_lineno ,int d_lineno ,char * s_comment ,char * d_comment ){
	 struct exclude * tmp =  malloc(sizeof(struct exclude));
	 tmp->node_type = EXCLUDE ;
	 tmp->s_lineno = s_lineno;
	 tmp->d_lineno = d_lineno ;
	 tmp->s_comment = s_comment;
	 tmp->d_comment = d_comment ;
	 tmp->next = exclude_root ;
	 return tmp ;
}

struct exclude * get_exclude(){
	struct include * tmp = exclude_root ;
	exclude_root = NULL;
	return tmp ;
}


struct  import_rule * join_import_rule(char * import_name , int lineno,struct regx * reg ,struct include * inc , struct exclude * exc){
	struct import_rule * tmp = malloc(sizeof(struct import_rule));
	tmp->node_type = IMPORT;
	tmp->lineno = lineno ;
	tmp->reg = reg ;
	tmp->inc =inc;
	tmp->exc = exc;
	tmp->next = import_rule_root ;
	import_rule_root = tmp ;
	return  tmp ;
}


struct import_rule * get_import_rule(){
	struct import_rule * tmp = import_rule_root;
	import_rule_root = NULL;
	return tmp ;
}



