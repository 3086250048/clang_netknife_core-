%option  noyywrap  nodefault yylineno
%{
	#include <stdlib.h>
	#include <string.h>
	#include "netknife.tab.h"
	#include "netknife.h"

%}

%x READY  TRANS_RULE TRANS_PRIORITY REGX TRANS_COMMENT TRANS_RULE_COMMENT TRANS_IMPORT_COMMENT TRANS_IMPORT
%%
trans { printf("TRANS "); return TRANS;}
\" {  BEGIN TRANS_COMMENT ;}
"{" {  printf("LBRACE ");BEGIN READY; return LBRACE;} 
[\x80-\xFFa-zA-Z0-9_]+ {  printf("STRING ");yylval.s=strdup(yytext ); return STRING;} 
. {} 
\n { printf("\n");}

<READY>[ \t] {}
<READY>[\n] {}
<READY>. { unput(strdup(yytext)[0]);BEGIN TRANS_RULE;}


<TRANS_COMMENT>\" { BEGIN 0;}
<TRANS_COMMENT>.|\n {}

<TRANS_RULE_COMMENT>\" { printf("COMMENT_END ");BEGIN READY ;return COMMENT_END;}
<TRANS_RULE_COMMENT>[ \t]+ { printf("EMPTY "); yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE_COMMENT>[\x80-\xFFa-zA-Z0-9_]+ {  printf("STRING "); yylval.s=strdup(yytext) ;return STRING; } 
<TRANS_RULE_COMMENT>. {}
<TRANS_RULE_COMMENT>\n {}

<TRANS_IMPORT_COMMENT>\" { printf("TRANS_IMPORT_COMMENT_END ");BEGIN TRANS_IMPORT; return TRANS_IMPORT_COMMENT_END;}
<TRANS_IMPORT_COMMENT>[ \t]+ { printf("EMPTY ");yylval.s=strdup(" ");return EMPTY;}
<TRANS_IMPORT_COMMENT>[\x80-\xFFa-zA-Z0-9_]+ {  printf("STRING ");yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_COMMENT>. {}
<TRANS_IMPORT_COMMENT>\n {}


<REGX>\" { printf("REGX_END ");BEGIN TRANS_IMPORT;return REGX_END;}
<REGX>[ \t]+ { printf("EMPTY ");yylval.s=strdup(" ");return EMPTY; }
<REGX>[^ "\t]+ { printf("STRING ");yylval.s=strdup(yytext) ;return STRING ; } 



<TRANS_IMPORT>include { printf("INCLUDE ");return INCLUDE;}
<TRANS_IMPORT>exclude { printf("EXCLUDE ");return EXCLUDE;}
<TRANS_IMPORT>[0-9]+ { printf("NUMBER ");yylval.d=atoi(yytext);return NUMBER;}
<TRANS_IMPORT>to { printf("TO ");return TO;}
<TRANS_IMPORT>,   { printf("COMMA ");return COMMA;}
<TRANS_IMPORT>\" {  printf("TRANS_IMPORT_COMMENT_START ");BEGIN TRANS_IMPORT_COMMENT;return  TRANS_IMPORT_COMMENT_START;}
<TRANS_IMPORT>r\" { printf("REGX_START ");BEGIN REGX;return REGX_START;}
<TRANS_IMPORT>; { printf("SEM ");BEGIN READY ;return SEM;}
<TRANS_IMPORT>[\x80-\xFFa-zA-Z0-9_]+ { printf("STRING ");yylval.s=strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT>[ \t] {} 
<TRANS_IMPORT>. {}
<TRANS_IMPORT>\n {}

<TRANS_RULE>= {  printf("EQ ");BEGIN TRANS_PRIORITY;return EQ;}
<TRANS_RULE>@ {  printf("IMPORT ");BEGIN TRANS_IMPORT;return IMPORT;}
<TRANS_RULE>; { printf("SME ");BEGIN READY ;return SEM;}
<TRANS_RULE>\" {  printf("COMMENT_START ");BEGIN TRANS_RULE_COMMENT;return COMMENT_START;}
<TRANS_RULE>\\n {  printf("LINE_BREAK ");yylval.s=strdup("\n"); return LINE_BREAK;}
<TRANS_RULE>[ \t]+ { printf("EMPTY ");yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE>"}" {  printf("RBRACE\n");BEGIN 0;return RBRACE;}
<TRANS_RULE>[^\"=>;}\n\t@ ]+ {  printf("STRING ");printf(" %s ",yytext);;yylval.s=strdup(yytext) ;return STRING ; }
<TRANS_RULE>. {}
<TRANS_RULE>\n {}

<TRANS_PRIORITY>[0-9]+ { printf("NUMBER ");yylval.d=atoi(yytext);return NUMBER;}
<TRANS_PRIORITY>> { printf("GT ");BEGIN READY;return GT;}
<TRANS_PRIORITY>. {}
<TRANS_PRIORITY>\n {}

%%



