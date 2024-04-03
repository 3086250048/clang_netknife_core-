%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "netknife.h"
%}


%union {
int d;
char * s;
struct rule * r;
struct comment * c;
struct rule_table * rule_tab;
struct comment_table * comment_tab;	
struct regx * reg;
struct range * ran;
struct filter * filter;
struct import_rule * import_rule_chain;
struct trans * trans;
struct trans_table * trans_tab ;					  
}

//声明记号

%token <d> NUMBER 
%token <s> STRING EMPTY LINE_BREAK
%token TRANS IMPORT COMMENT_START COMMENT_END INCLUDE EXCLUDE TO LBRACE RBRACE REGX_START REGX_END COMMA EQ GT SEM TRANS_IMPORT_COMMENT_START TRANS_IMPORT_COMMENT_END DOT  
%type <s> index_string_exp const_comment_exp
%type <rule_tab> rule_table_exp
%type <comment_tab> comment_table_exp
%type <ran> range_exp
%type <filter> filter_exp
%type <import_rule_chain> import_rule_chain_exp
%type <trans> trans_exp trans_body_exp  
%type <trans_tab> trans_table_exp
%%


trans_table_exp : {$$=NULL;}
		| trans_table_exp trans_exp {$$=join_trans_table($2); print_trans_table_entry($$->trans);}
		;
trans_exp : TRANS STRING LBRACE RBRACE  { $$=join_trans(curfilename,$2,yylineno,NULL,NULL,NULL); }
  | TRANS STRING LBRACE trans_body_exp RBRACE { $$=join_trans(curfilename,$2,yylineno,get_rule_table(),get_comment_table(),get_import_rule()) ;}
  ;
trans_body_exp : rule_table_exp{$$=NULL;} 
	   | comment_table_exp {$$=NULL;} 
	   | import_rule_chain_exp{$$=NULL;}
	   | trans_body_exp rule_table_exp {$$=NULL;} 
	   | trans_body_exp comment_table_exp {$$=NULL;}
	   | trans_body_exp import_rule_chain_exp {$$=NULL;}	
	   ;

import_rule_chain_exp :  IMPORT STRING SEM {  $$=join_import_rule(NULL,$2,yylineno,NULL);} 
			  | IMPORT  STRING  filter_exp SEM { $$=join_import_rule(NULL,$2,yylineno,$3);}
			  | IMPORT STRING DOT STRING  filter_exp SEM { $$=join_import_rule($2,$4,yylineno,$5);}
			  ;
filter_exp : INCLUDE range_exp { $$ = join_filter(NULL,INCLUDE_NODE,$2);}
		   | EXCLUDE range_exp { $$ = join_filter(NULL,EXCLUDE_NODE,$2);}
		   | filter_exp INCLUDE range_exp  { $$ = join_filter($1,INCLUDE_NODE,$3);}
		   | filter_exp EXCLUDE range_exp  { $$ = join_filter($1,EXCLUDE_NODE,$3);}

range_exp : NUMBER { $$=join_range(NULL,NULL,$1,0,NULL,NULL); }
  | const_comment_exp  {$$ = join_range(NULL,NULL,0,0,$1,NULL); }
  | REGX_START index_string_exp REGX_END  {$$ = join_range(NULL,trim($2),0,0,NULL,NULL); }
  | NUMBER  TO NUMBER  {$$=join_range(NULL,NULL,$1,$3,NULL,NULL);}
  | const_comment_exp  TO const_comment_exp  {$$=join_range(NULL,NULL,0,0,$1,$3);}
  | NUMBER  TO const_comment_exp   {$$=join_range(NULL,NULL,$1,0,NULL,$3);}
  | const_comment_exp TO  NUMBER   {$$=join_range(NULL,NULL,0,$3,$1,NULL);}
  | range_exp COMMA REGX_START index_string_exp REGX_END {$$=join_range($1,trim($4),0,0,NULL,NULL);} 
  | range_exp COMMA const_comment_exp {$$=join_range($1,NULL,0,0,$3,NULL);}
  | range_exp COMMA NUMBER  {$$=join_range($1,NULL,$3,0,NULL,NULL);}
  | range_exp COMMA NUMBER TO NUMBER { $$ = join_range($1,NULL,$3,$5,NULL,NULL);}
  | range_exp COMMA NUMBER TO const_comment_exp {$$=join_range($1,NULL,$3,0,NULL,$5);}
  | range_exp COMMA const_comment_exp TO NUMBER {$$=join_range($1,NULL,0,$5,$3,NULL);}
  | range_exp COMMA const_comment_exp TO const_comment_exp {$$=join_range($1,NULL,0,0,$3,$5);}
  ;

const_comment_exp : TRANS_IMPORT_COMMENT_START index_string_exp TRANS_IMPORT_COMMENT_END { $$=trim($2); }

comment_table_exp : COMMENT_START index_string_exp COMMENT_END { 
			 $$=join_comment_table(join_comment(trim($2),yylineno));
		  }
		  ;

rule_table_exp : index_string_exp EQ GT index_string_exp SEM  {
			$$=join_rule_table(join_rule(trim($1),trim($4),yylineno,0));
		 }
	   | index_string_exp EQ NUMBER GT index_string_exp SEM {
		   $$=join_rule_table(join_rule(trim($1),trim($5),yylineno,$3));
		 }
		;

index_string_exp : STRING {$$=$1;}
		 | LINE_BREAK { $$=$1;}
		 | index_string_exp STRING { $$=strcat($1,$2);}
		 | index_string_exp EMPTY  { $$=strcat($1,$2);}
		 | index_string_exp LINE_BREAK { $$=strcat($1,$2);}
		 ;


%%







