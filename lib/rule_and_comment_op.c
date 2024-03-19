#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


struct rule * join_rule(struct index_string * s , struct index_string * d,int lineno , int priority ){
	struct rule * tmp = malloc(sizeof(struct rule));
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
	char * str = cat_string(c->c);
	printf("c:%s l:%d \n",str,c->lineno);
}

void  print_rule(struct rule * r){
	char * src = cat_string(r->s);
	char * dst = cat_string(r->d);
	printf("s:%s d:%s l:%d p:%d \n",src,dst,r->lineno,r->priority);
}
