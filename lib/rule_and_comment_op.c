#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


struct rule * join_rule(struct index_string * s , struct index_string * d,int lineno , int priority ){
	struct rule * tmp = malloc(sizeof(struct rule));
	tmp->node_type = RULE_NODE;
	tmp->lineno=lineno;
	tmp->priority=priority;
	tmp->s=s;
	tmp->d=d;
	return tmp;
}


struct comment * join_comment(struct index_string * c, int lineno ){
	printf("comment :%s\n",cat_string(c));
	struct comment * tmp = malloc(sizeof(struct comment));
	tmp->node_type = COMMENT_NODE;
	tmp->c = c;
	tmp->lineno = lineno;
	return tmp;
}



void print_comment(struct comment * c){
	char * str = cat_string(c->c);
	printf("node_type:COMMENT\n");
	printf("lineno:%d\n",c->lineno);
	printf("string:%s\n",str);

}

void  print_rule(struct rule * r){
	char * src = cat_string(r->s);
	char * dst = cat_string(r->d);
	printf("node_type:RULE\n");;
	printf("source:%s\n",src);
	printf("destination:%s\n",dst);
	printf("lineno:%d\n",r->lineno);
	printf("priority:%d\n",r->priority);
}
