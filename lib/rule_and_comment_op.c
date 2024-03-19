#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


struct rule * join_rule(struct index_string * s , struct index_string * d,int lineno , int priority ){
	struct rule * tmp = malloc(sizeof(struct index_string));
	tmp->node_type = RULE;
	tmp->lineno=lineno;
	tmp->priority=priority;
	tmp->s=s;
	tmp->d=d;
	return tmp;
}


struct comment * join_comment(struct index_string * c, int lineno ){
	struct comment * tmp = malloc(sizeof(struct comment));
	tmp->node_type = COMMENT;
	tmp->c = c;
	tmp->lineno = lineno;
	return tmp;
}



void print_comment(struct comment * c){
	printf("c:%s l:%d \n",c->c,c->lineno);
}

void  print_rule(struct rule * r){
	printf("s:%s d:%s l:%d p:%d \n",r->s,r->d,r->lineno,r->priority);
}
