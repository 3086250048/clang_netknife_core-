#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

struct rule * join_rule(char  * s , char * d,int lineno , int priority ){
	struct rule * tmp = malloc(sizeof(struct rule));
	tmp->node_type = RULE_NODE;
	tmp->lineno=lineno;
	tmp->priority=priority;
	tmp->s=s;
	tmp->d=d;
	return tmp;
}


struct comment * join_comment(char * c, int lineno ){
	struct comment * tmp = malloc(sizeof(struct comment));
	tmp->node_type = COMMENT_NODE;
	tmp->c = c;
	tmp->lineno = lineno;
	return tmp;
}


struct rule_table * rule_table_reduce( char * s ,char * d ,int priority ){
	if(cur_state==NORMAL_STATE){
		  	return join_rule_table(join_rule(trim(s),trim(d),yylineno,priority));
	}else{
		if(!strcmp(cur_trans,target_trans)||!strcmp(ALL_TRANS,target_trans)){
			join_buffer_chain(curfilename, cur_trans,RULE_NODE, join_rule(trim(s),trim(d),yylineno,priority));
			return NULL;
		}else{
			return NULL;
		}
	 }
}


struct comment_table * comment_table_reduce(char * c){
 	if(cur_state==NORMAL_STATE){
		 return join_comment_table(join_comment(trim(c),yylineno));
	}else{
		if(!strcmp(cur_trans,target_trans) || !strcmp(ALL_TRANS,target_trans)){
			join_buffer_chain(curfilename , cur_trans , COMMENT_NODE ,join_comment(trim(c),yylineno));
			return NULL;
		}else{
			return NULL;
		}
	}
}

void  print_comment(struct comment * c){
	printf("%*snode_type:COMMENT\n",PRINT_COMMENT);
	printf("%*slineno:%d\n",PRINT_COMMENT,c->lineno);
	printf("%*sstring:%s\n",PRINT_COMMENT,c->c);
}

void  print_rule(struct rule * r){
	printf("%*snode_type:RULE\n",PRINT_RULE);
	printf("%*ssource:%s\n",PRINT_RULE,r->s);
	printf("%*sdestination:%s\n",PRINT_RULE,r->d);
	printf("%*slineno:%d\n",PRINT_RULE,r->lineno);
	printf("%*spriority:%d\n",PRINT_RULE,r->priority);
}
