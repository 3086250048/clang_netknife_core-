%{
#include <stdio.h>
#include <stdlib.h>
#include  "netknife.h"
%}


%union {
	int d;
	char * s;
	struct index_string * str;
	struct rule * r;
	struct comment * c;
	struct rule_table * rule_tab;
	struct comment_table * comment_tab;	
	struct regx * reg;
	struct range * ran;
	struct include * inc ;
	struct exclude * exc ;
	struct import_rule * import_rule_chain;
	struct trans * trans;
	struct trans_table * trans_tab ;					  
}

//声明记号

%token <d> NUMBER 
%token <s> STRING EMPTY LINE_BREAK
%token TRANS IMPORT COMMENT_START COMMENT_END INCLUDE EXCLUDE TO LBRACE RBRACE REGX_START REGX_END COMMA EQ GT SEM TRANS_IMPORT_COMMENT_START TRANS_IMPORT_COMMENT_END 
%type <str> index_string_exp const_comment_exp
%type <rule_tab> rule_table_exp
%type <comment_tab> comment_table_exp
%type <reg> regx_exp
%type <ran> range_exp
%type <inc> include_exp
%type <exc> exclude_exp
%type <import_rule_chain> import_rule_chain_exp
%type <trans> trans_exp trans_body_exp
%type <trans_tab> trans_table_exp
%%

trans_table_exp : {$$=NULL;}
				| trans_table_exp trans_exp {$$=join_trans_table($2); print_trans_table_entry($$->trans);}
				;
trans_exp : TRANS STRING LBRACE RBRACE  { $$=join_trans("TEST",$2,yylineno,NULL,NULL,NULL); }
		  | TRANS STRING LBRACE trans_body_exp RBRACE { $$=join_trans("TEST",$2,yylineno,get_rule_table(),get_comment_table(),get_import_rule()) ;}
		  ;
trans_body_exp : rule_table_exp{$$=NULL;} 
			   | comment_table_exp {$$=NULL;} 
			   | import_rule_chain_exp{$$=NULL;}
			   | trans_body_exp rule_table_exp {$$=NULL;} 
			   | trans_body_exp comment_table_exp {$$=NULL;}
			   | trans_body_exp import_rule_chain_exp {$$=NULL;}	
			   ;

import_rule_chain_exp : IMPORT STRING SEM { $$=join_import_rule($2,yylineno,NULL,NULL);} 
					  |	IMPORT STRING include_exp SEM {$$=join_import_rule($2,yylineno,$3,NULL);}
					  | IMPORT STRING exclude_exp SEM {$$=join_import_rule($2,yylineno,NULL,$3);}
					  | IMPORT STRING include_exp exclude_exp SEM {$$=join_import_rule($2,yylineno,$3,$4);}
					  | IMPORT STRING exclude_exp include_exp SEM {$$=join_import_rule($2,yylineno,$4,$3);} 
					  ;

exclude_exp : EXCLUDE regx_exp   { $$=join_exclude($$,get_regx(),NULL);}
		   	| EXCLUDE  range_exp { $$=join_exclude($$,NULL,get_range()); }
			| EXCLUDE  regx_exp range_exp {$$=join_exclude($$,get_regx(),get_range());}
			| EXCLUDE  range_exp regx_exp {$$=join_exclude($$,get_regx(),get_range());}
			;

include_exp : INCLUDE regx_exp   { $$=join_include($$,get_regx(),NULL);}
		   	| INCLUDE range_exp { $$=join_include($$,NULL,get_range()); }
			| INCLUDE regx_exp range_exp {$$=join_include($$,get_regx(),get_range());}
			| INCLUDE range_exp range_exp {$$=join_include($$,get_regx(),get_range());}
			;

range_exp : NUMBER { $$=join_range($1,0,NULL,NULL); }
		  | const_comment_exp  {$$ = join_range(0,0,$1,NULL); }
		  | NUMBER  TO NUMBER  {$$=join_range($1,$3,NULL,NULL);}
		  | const_comment_exp  TO const_comment_exp  {$$=join_range(0,0,$1,$3);}
		  | NUMBER  TO const_comment_exp   {$$=join_range($1,0,$3,NULL);}
		  | const_comment_exp TO  NUMBER   {$$=join_range(0,$3,$1,NULL);}
		  | range_exp COMMA const_comment_exp {$$=join_range(0,0,$3,NULL);}
		  | range_exp COMMA NUMBER  {$$=join_range($3,0,NULL,NULL);}
		  | range_exp COMMA NUMBER TO NUMBER { $$ = join_range($3,$5,NULL,NULL);}
		  | range_exp COMMA NUMBER TO const_comment_exp {$$=join_range($3,0,NULL,$5);}
		  | range_exp COMMA const_comment_exp TO NUMBER {$$=join_range(0,$5,$3,NULL);}
		  | range_exp COMMA const_comment_exp TO const_comment_exp {$$=join_range(0,0,$3,$5);}
		  ;

regx_exp : REGX_START index_string_exp REGX_END {
		   $$=join_regx(string($2));
		 }
		 | regx_exp REGX_START index_string_exp REGX_END {
		   $$=join_regx(string($3));
		 }
		 ;

const_comment_exp : TRANS_IMPORT_COMMENT_START index_string_exp TRANS_IMPORT_COMMENT_END { $$=string($2); }

comment_table_exp : COMMENT_START index_string_exp COMMENT_END { 
				  	 $$=join_comment_table(join_comment(string($2),yylineno));
				  }
				  ;

rule_table_exp : index_string_exp EQ GT index_string_exp SEM  {
			   	  $$=join_rule_table(join_rule(string($1),string($4),yylineno,0));
				 }
		 	   | index_string_exp EQ NUMBER GT index_string_exp SEM {
				  $$=join_rule_table(join_rule(string($1),string($5),yylineno,$3));
				 }
		 		;

index_string_exp : STRING { $$=join_index_string($$,$1);}
				 | LINE_BREAK { $$=join_index_string($$,$1);}
				 | EMPTY  {  $$=join_index_string($$,$1);}
				 | index_string_exp STRING {  $$=join_index_string($1,$2);}
				 | index_string_exp EMPTY  {  $$=join_index_string($1,$2);}
				 | index_string_exp LINE_BREAK { $$=join_index_string($1,$2);}
				 ;
%%






