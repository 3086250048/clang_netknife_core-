%option  noyywrap  nodefault yylineno
%{
	#include <stdlib.h>
	#include <string.h>
	#include "netknife.tab.h"
	#include "netknife.h"

%}

%x TRANS_RULE TRANS_PRIORITY REGX TRANS_COMMENT TRANS_RULE_COMMENT TRANS_IMPORT_COMMENT TRANS_IMPORT
%%
trans { return TRANS;}
\" { BEGIN TRANS_COMMENT ;}
"{" {  BEGIN TRANS_RULE; return LBRACE;} 
[\x80-\xFFa-zA-Z0-9_]+ { yylval.s=strdup(yytext ); return STRING;} 
[ \t] {} 
.|\n {}


<TRANS_COMMENT>\" { BEGIN 0;}
<TRANS_COMMENT>.|\n {}

<TRANS_RULE_COMMENT>\" { BEGIN TRANS_RULE;return COMMENT_END;}
<TRANS_RULE_COMMENT>[ \t]+ { yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE_COMMENT>[\x80-\xFFa-zA-Z0-9_]+ { yylval.s=strdup(yytext) ;return STRING; } 
<TRANS_RULE_COMMENT>.|\n {}

<TRANS_IMPORT_COMMENT>\" { BEGIN TRANS_IMPORT; return TRANS_IMPORT_COMMENT_END;}
<TRANS_IMPORT_COMMENT>[ \t]+ { yylval.s=strdup(" ");return EMPTY;}
<TRANS_IMPORT_COMMENT>[\x80-\xFFa-zA-Z0-9_]+ { yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_COMMENT>.|\n {}

<REGX>\" { BEGIN TRANS_IMPORT;return REGX_END;}
<REGX>[ \t]+ { yylval.s=strdup(" ");return EMPTY; }
<REGX>[\x80-\xFFa-zA-Z0-9_]+ { yylval.s=strdup(yytext) ;return STRING ; } 
<REGX>.|\n {}

<TRANS_IMPORT>include { return INCLUDE;}
<TRANS_IMPORT>exclude { return EXCLUDE;}
<TRANS_IMPORT>[0-9]+ { yylval.d=atoi(yytext);return NUMBER;}
<TRANS_IMPORT>to { return TO;}
<TRANS_IMPORT>,   { return COMMA;}
<TRANS_IMPORT>\" {  BEGIN TRANS_IMPORT_COMMENT;return  TRANS_IMPORT_COMMENT_START;}
<TRANS_IMPORT>r\" { BEGIN REGX;return REGX_START;}
<TRANS_IMPORT>; { BEGIN TRANS_RULE;return SEM;}
<TRANS_IMPORT>[\x80-\xFFa-zA-Z0-9_]+ { yylval.s=strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT>[ \t] {} 
<TRANS_IMPORT>.|\n {}

<TRANS_RULE>= {  BEGIN TRANS_PRIORITY;return EQ;}
<TRANS_RULE>@ { BEGIN TRANS_IMPORT;return IMPORT;}
<TRANS_RULE>; { return SEM;}
<TRANS_RULE>\" { BEGIN TRANS_RULE_COMMENT;return COMMENT_START;}
<TRANS_RULE>\\n { yylval.s=strdup("\n"); return LINE_BREAK;}
<TRANS_RULE>[ \t]+ { yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE>"}" {  BEGIN 0;return RBRACE;}
<TRANS_RULE>[^\"=>;}\n\t@ ]+ {  yylval.s=strdup(yytext) ;return STRING ; }
<TRANS_RULE>.|\n {}

<TRANS_PRIORITY>[0-9]+ { yylval.d=atoi(yytext);return NUMBER;}
<TRANS_PRIORITY>> { BEGIN TRANS_RULE;return GT;}
<TRANS_PRIORITY>.|\n { }
%%



