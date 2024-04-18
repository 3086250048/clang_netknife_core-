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
