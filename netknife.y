%{
#include <stdio.h>
#include <stdlib.h>
#include  "netknife.h"
%}


%union {
	int d;
	char * s;
    ast * a;
}

//声明记号

%token <d> NUMBER 
%token <s> STRING EMPTY
%token TRANS IMPORT OUTPUT IN COMMENT_START COMMENT_END INCLUDE EXCLUDE TO LBRACE RBRACE REGX_START REGX_END COMMA EQ GT SEM LINE_BREAK  
%type  comment_list string_list 
%%



import_rule : IMPORT STRING {}
		   	| import_rule COMMA STRING {}	

include_list : INCLUDE comment_list {}
			 | INCLUDE NUMBER {}
			 | include_list TO NUMBER {}
			 | include_list TO comment_list {}
			 | include_list COMMA comment_list {} 
			 | include_list COMMA NUMBER {}
			 ;

exclude_list :
			 ;

trans_rule : string_list EQ GT string_list SEM
		  	 { }
		   | trans_rule string_list EQ GT string_list SEM
			 { }
		   ;

comment_list  :	COMMENT_START string_list COMMENT_END  
			  { print_index_string();} 
			  | comment_list COMMENT_START string_list COMMENT_END
			  { print_index_string();} 
		      ;
string_list : EMPTY { new_index_string($1);}
			| STRING { new_index_string($1);}
			| string_list EMPTY { new_index_string($2);}
			| string_list STRING { new_index_string($2);}
			;
%%


