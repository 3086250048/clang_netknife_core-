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
	struct include * inc ;
	struct exclude * exc ;
	struct import_rule * import_rule_chain;
	struct trans * trans;
	struct trans_table * trans_tab ;					  
}

//声明记号

%token <d> NUMBER 
%token <s> STRING EMPTY
%token TRANS IMPORT OUTPUT IN COMMENT_START COMMENT_END INCLUDE EXCLUDE TO LBRACE RBRACE REGX_START REGX_END COMMA EQ GT SEM LINE_BREAK  
%type <str> index_string_exp 
%type <rule_tab> rule_table_exp;
%type <comment_tab> comment_table_exp;
%type <reg> regx_exp;
%type <inc> include_exp;
%type <exc> exclude_exp;
%type <import_rule_chain> import_rule_chain_exp;
%type <trans> trans_exp;
%type <trans_tab> trans_table_exp;
%%


trans_exp : TRANS STRING SEM { join_trans("TEST",$2,yylineno,NULL,NULL,NULL);}
		  | TRANS STRING LBRACE RBRACE SEM {join_trans("TEST",$2,yylineno,NULL,NULL,NULL);}
		  | TRANS STRING LBRACE rule_table_exp RBRACE {join_trans("TEST",$2,yylineno,$4,NULL,NULL);}
		  | TRANS STRING LBRACR comment_table_exp RBRACE {join_trans("TEST",$2,yylineno,NULL,$4,NULL);}
	      | TRANS STRING LBRACE import_rule_exp  





import_rule_chain_exp : IMPORT STRING
					  |	IMPORT STRING 
					  | IMPORT STRING  
					  | IMPORT STRING 
					  | IMPORT STRING 
					  | 
					  ;



include_exp : INCLUDE NUMBER TO NUMBER 
			| INCLUDE NUMBER TO COMMENT 
			| INCLUDE COMMENT TO COMMENT 
			| INCLUDE COMMENT TO NUMBER 
			;


regx_exp : REGX_START index_string REGX_END {
			 join_regx($2);
		 }
		 | regx_exp REGX_START index_string REGX_END {
			 join_regx($3);
		 }



comment_table_exp : COMMENT_START index_string_exp COMMENT_END { 
				  	join_comment_table(join_comment($1,yylineno));
					}
				  ;

rule_table_exp : index_string_exp EQ GT index_string_exp SEM  {
			   	 join_rule_table(join_rule($1,$4,yylineno,0));
				 }
		 	   | index_string_exp EQ NUMBER GT index_string_exp SEM {
				 join_rule_table(join_rule($1,$5,yylineno,$3));
				 }
		 		;
index_string_exp : STRING { join_index_string($1);}
				 | index_string_exp STRING {join_index_string($2);}
				 ;
%%






