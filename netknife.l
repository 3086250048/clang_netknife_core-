%option  noyywrap  nodefault yylineno
%{
	#include <stdlib.h>
	#include <string.h>
	#include "netknife.tab.h"
	#include "netknife.h"
%}

%x READY  TRANS_RULE TRANS_PRIORITY REGX TRANS_COMMENT TRANS_RULE_COMMENT TRANS_IMPORT_COMMENT TRANS_IMPORT TRANS_IMPORT_NAME 
%%
trans { 
#ifdef ECHO_TOKEN
  printf("TRANS ");
#endif 
return TRANS;}

\" {  BEGIN TRANS_COMMENT ;}
"{" { 
#ifdef ECHO_TOKEN 
 printf("LBRACE ");
#endif
BEGIN READY; return LBRACE;} 
[\x80-\xFFa-zA-Z0-9_]+ {
#ifdef ECHO_TOKEN 
 printf("STRING ");
#endif
yylval.s=strdup(yytext );return STRING;} 
. {} 
\n { 
#ifdef ECHO_TOKEN
printf("\n");
#endif
}
<<EOF>> { 
	if(transcmp(target_trans,ALL_TRANS)){
		struct trans * t= join_trans(cur_trans,yylineno,get_rule_table(),get_comment_table(),get_import_rule());
		print_trans(t);
		printf("\n");
	}

	if(file_stack_count > 1 && import_state){
		err("import_trans_state","no imported trans found");
		exit(1);
	}  
	if(file_stack_count == 1){
		return 0;
	}else{
		popfile();
	}
}

<READY>[ \t] { }
<READY>[\n] { 
#ifdef ECHO_TOKEN 
printf("\n");
#endif
}
<READY>. { unput(yytext[0]);BEGIN TRANS_RULE;}


<TRANS_COMMENT>\" { BEGIN 0;}
<TRANS_COMMENT>.|\n { 
#ifdef ECHO_TOKEN
printf("\n");
#endif
}

<TRANS_RULE_COMMENT>\" {
#ifdef ECHO_TOKEN
 printf("COMMENT_END ");
#endif
BEGIN READY ;return COMMENT_END;}
<TRANS_RULE_COMMENT>[ \t]+ {
#ifdef ECHO_TOKEN 
 printf("EMPTY ");
#endif
 yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE_COMMENT>[^ \t\n"]+ { 
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif 
 yylval.s=strdup(yytext) ;return STRING; } 
<TRANS_RULE_COMMENT>\n {
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}

<TRANS_IMPORT_COMMENT>\" {
#ifdef ECHO_TOKEN
 printf("TRANS_IMPORT_COMMENT_END ");
#endif
BEGIN TRANS_IMPORT; return TRANS_IMPORT_COMMENT_END;}
<TRANS_IMPORT_COMMENT>[ \t]+ { 
#ifdef ECHO_TOKEN
printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY;}
<TRANS_IMPORT_COMMENT>[^ \t\n"]+ {  
#ifdef ECHO_TOKEN
printf("STRING ");
#endif
yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_COMMENT>\n {
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}


<REGX>\" {
#ifdef ECHO_TOKEN
printf("REGX_END ");
#endif
BEGIN TRANS_IMPORT;return REGX_END;}
<REGX>[ \t]+ {
#ifdef ECHO_TOKEN
 printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY; }
<REGX>[^ "\t]+ {
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; } 

<TRANS_IMPORT_NAME>")"  {
#ifdef ECHO_TOKEN
 printf("RBRACE ");
#endif
BEGIN TRANS_IMPORT ;return RBRACE; }
<TRANS_IMPORT_NAME>[^ \t\n\)]+ { 
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_NAME>[ \n\t]+ {}

<TRANS_IMPORT>include {
#ifdef ECHO_TOKEN
 printf("INCLUDE ");
#endif
return INCLUDE;}
<TRANS_IMPORT>exclude {
#ifdef ECHO_TOKEN
 printf("EXCLUDE ");
#endif
return EXCLUDE;}
<TRANS_IMPORT>[0-9]+ {
#ifdef ECHO_TOKEN
 printf("NUMBER ");
#endif
yylval.d=atoi(yytext);return NUMBER;}
<TRANS_IMPORT>to {
#ifdef ECHO_TOKEN
 printf("TO ");
#endif
return TO;}
<TRANS_IMPORT>,   {
#ifdef ECHO_TOKEN
 printf("COMMA ");
#endif
return COMMA;}
<TRANS_IMPORT>\" { 
#ifdef ECHO_TOKEN
 printf("TRANS_IMPORT_COMMENT_START ");
#endif
BEGIN TRANS_IMPORT_COMMENT;return  TRANS_IMPORT_COMMENT_START;}
<TRANS_IMPORT>r\" {
#ifdef ECHO_TOKEN
 printf("REGX_START ");
#endif
BEGIN REGX;return REGX_START;}
<TRANS_IMPORT>; {
#ifdef ECHO_TOKEN
 printf("SEM ");
#endif
BEGIN READY ;return SEM;}
<TRANS_IMPORT>- {
#ifdef ECHO_TOKEN
 printf("HYPHEN ");
#endif
return HYPHEN; }
<TRANS_IMPORT>> {
#ifdef ECHO_TOKEN
 printf("GT ");
#endif
return GT ;} 
<TRANS_IMPORT>"(" {
#ifdef ECHO_TOKEN
 printf("LBRACE ");
#endif
BEGIN TRANS_IMPORT_NAME ;return LBRACE;}
<TRANS_IMPORT>[\x80-\xFFa-zA-Z0-9_]+ {
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT>[ \t] {} 
<TRANS_IMPORT>. {}
<TRANS_IMPORT>\n { printf("\n");}

<TRANS_RULE>= { 
#ifdef ECHO_TOKEN
 printf("EQ ");
#endif
BEGIN TRANS_PRIORITY;return EQ;}
<TRANS_RULE>@ { 
#ifdef ECHO_TOKEN
 printf("IMPORT ");
#endif
BEGIN TRANS_IMPORT;return IMPORT;}
<TRANS_RULE>; {
#ifdef ECHO_TOKEN
 printf("SME ");
#endif
BEGIN READY ;return SEM;}
<TRANS_RULE>\" { 
#ifdef ECHO_TOKEN
 printf("COMMENT_START ");
#endif
BEGIN TRANS_RULE_COMMENT;return COMMENT_START;}
<TRANS_RULE>\\n { 
#ifdef ECHO_TOKEN
 printf("LINE_BREAK ");
#endif
yylval.s=strdup("\n"); return LINE_BREAK;}
<TRANS_RULE>[ \t]+ {
#ifdef ECHO_TOKEN
 printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE>"}" { 
#ifdef ECHO_TOKEN
 printf("RBRACE\n");
#endif
BEGIN 0;return RBRACE;}
<TRANS_RULE>[^\"=>;}\n\t@ ]+ { 
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; }
<TRANS_RULE>. {}
<TRANS_RULE>\n {
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}

<TRANS_PRIORITY>[0-9]+ {
#ifdef ECHO_TOKEN
 printf("NUMBER ");
#endif
yylval.d=atoi(yytext);return NUMBER;}
<TRANS_PRIORITY>> {
#ifdef ECHO_TOKEN
 printf("GT ");
#endif
BEGIN READY;return GT;}
<TRANS_PRIORITY>. {}
<TRANS_PRIORITY>\n { 
#ifdef ECHO_TOKEN
printf("\n");
#endif
}




%%



