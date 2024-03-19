#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


static struct regx * regx_root = NULL;
static struct include * include_root = NULL;
static struct exclude * exclude_root = NULL;
static struct import_rule * import_rule_root = NULL;

struct regx * join_regx(struct index_string * exp){
	struct regx * tmp = malloc(sizeof(struct regx));
	tmp->node_type = REGX;
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
	 	printf("node_type:REGX\n");
		printf("exp:%s\n",cat_string(tmp->exp));
		tmp=tmp->next;
	 }

}


struct include * join_include(int s_lineno ,int d_lineno ,struct index_string * s_comment ,struct index_string * d_comment ){
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

void print_include(struct include * include_root){
	 struct include * tmp = include_root ;
	 while(tmp){
	 	printf("node_type:INCLUDE\n");
		printf("s_lineno:%d\n",tmp->s_lineno);
		printf("d_lineno:%d\n",tmp->d_lineno);
		printf("s_comment:%s\n",cat_string(tmp->s_comment));
		printf("d_comment:%s\n",cat_string(tmp->d_comment));
		tmp=tmp->next;
	 }

}




struct exclude * join_exclude(int s_lineno ,int d_lineno ,struct index_string  * s_comment ,struct index_string  * d_comment ){
	 struct exclude * tmp =  malloc(sizeof(struct exclude));
	 tmp->node_type = EXCLUDE ;
	 tmp->s_lineno = s_lineno;
	 tmp->d_lineno = d_lineno ;
	 tmp->s_comment = s_comment;
	 tmp->d_comment = d_comment;
	 tmp->next = exclude_root ;
	 return tmp ;
}

struct exclude * get_exclude(){
	struct exclude * tmp = exclude_root ;
	exclude_root = NULL;
	return tmp ;
}

void print_exclude(struct exclude * exclude_root){
	 struct exclude * tmp = exclude_root ;
	 while(tmp){
	 	printf("node_type:EXCLUDE\n");
		printf("s_lineno:%d\n",tmp->s_lineno);
		printf("d_lineno:%d\n",tmp->d_lineno);
		printf("s_comment:%s\n",cat_string(tmp->s_comment));
		printf("d_comment:%s\n",cat_string(tmp->d_comment));
		tmp=tmp->next;
	 }

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


void print_import_rule(struct import_rule * import_rule_root){
	struct import_rule * tmp = import_rule_root;
	while(tmp){
		printf("node_type:IMPORT\n");
		printf("import_name:%d\n",tmp->import_name);
		printf("lineno:%d\n",tmp->lineno);
		print_regx(tmp->reg);
		print_include(tmp->inc);
		print_exclude(tmp->exc);
		tmp = tmp->next;
	}
}


