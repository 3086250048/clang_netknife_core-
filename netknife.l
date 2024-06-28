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
SAVE_CMD ;return TRANS;}
\" {  SAVE_CMD ;BEGIN TRANS_COMMENT ;}
"{" { 
#ifdef ECHO_TOKEN 
 printf("LBRACE ");
#endif
 SAVE_CMD ;BEGIN READY; return LBRACE;} 
; {
#ifdef ECHO_TOKEN 
 printf("SEM");
#endif
 SAVE_CMD ;return SEM;
}

@ { SAVE_CMD;goto_global =1 ;flex_state = OTHER_STATE ;BEGIN TRANS_IMPORT;return IMPORT; }




[\x80-\xFFa-zA-Z0-9_]+ {
#ifdef ECHO_TOKEN 
 printf("STRING ");
#endif
SAVE_CMD ;yylval.s=strdup(yytext );return STRING;} 
. { SAVE_CMD;} 
\n { 
SAVE_CMD ;
#ifdef ECHO_TOKEN
printf("\n");
#endif
}
<<EOF>> {

	if( AL_TRANS && start_trans){
		
		if(IMPORT_STATE){
			struct import_info * import_info = Top(&import_stack)->buffer  ;
			//import_info = Filter(import_info);
			if(import_info){
				SET_TARGET_TRANS;
				join_import_rule(import_info->file_name , import_info->import_name , import_info->lineno , import_info->filter);
				if(newfile(import_info->file_name)){
					Pop(&import_stack);
					yyparse();
				}
			}//else{
				//	Pop(&import_stack);	
				//if(Top(&import_stack) == NULL){
				//	struct trans * t = join_trans(start_trans , yylineno , get_rule_table(), get_import_rule()); 
				//	RESET_START_TRANS;
				//	print_trans(t);
				//	join_netknife_table(start_file , t );
				//	RESET_START_FILE;				
				//}

			//}
		}else{
			struct trans * t = join_trans(start_trans , yylineno , get_rule_table(), get_import_rule()); 
			RESET_START_TRANS;
			print_trans(t);
			join_netknife_table(start_file , t );
			RESET_START_FILE;				
//			Clear(&filter_entry_tab);
		}
		
	}

	if(!AL_TRANS && start_trans){
		err("import_trans_state","no match target trans");
		exit(1);
	} 

	if(file_stack_count == 1 ){ yyterminate();}
	if(!popfile()) {yyterminate();}
	
}

<READY>[ \t] { SAVE_CMD; }
<READY>[\n] { SAVE_CMD;
#ifdef ECHO_TOKEN 
printf("\n");
#endif
}
<READY>. {
	 unput(yytext[0]);
	 if(goto_global){
		flex_state = GLOBAL_STATE;
		goto_global = 0 ;
		BEGIN 0 ; 
	}else{
		BEGIN TRANS_RULE;
	}
}



<TRANS_COMMENT>\" { SAVE_CMD;BEGIN 0;}
<TRANS_COMMENT>.|\n { 
SAVE_CMD;
#ifdef ECHO_TOKEN
printf("\n");
#endif
}

<TRANS_RULE_COMMENT>\" {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("COMMENT_END ");
#endif
BEGIN READY ;return COMMENT_END;}
<TRANS_RULE_COMMENT>[ \t]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN 
 printf("EMPTY ");
#endif
 yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE_COMMENT>[^ \t\n"]+ { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif 
 yylval.s=strdup(yytext) ;return STRING; } 
<TRANS_RULE_COMMENT>\n {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}

<TRANS_IMPORT_COMMENT>\" {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("TRANS_IMPORT_COMMENT_END ");
#endif
BEGIN TRANS_IMPORT; return TRANS_IMPORT_COMMENT_END;}
<TRANS_IMPORT_COMMENT>[ \t]+ { 
SAVE_CMD;
#ifdef ECHO_TOKEN
printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY;}
<TRANS_IMPORT_COMMENT>[^ \t\n"]+ {  
SAVE_CMD;
#ifdef ECHO_TOKEN
printf("STRING ");
#endif
yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_COMMENT>\n {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}


<REGX>\" {
SAVE_CMD;
#ifdef ECHO_TOKEN
printf("REGX_END ");
#endif
BEGIN TRANS_IMPORT;return REGX_END;}
<REGX>[ \t]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY; }
<REGX>[^ "\t]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; } 

<TRANS_IMPORT_NAME>")"  {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("RBRACE ");
#endif
BEGIN TRANS_IMPORT ;return RBRACE; }
<TRANS_IMPORT_NAME>[^ \t\n\)]+ { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s= strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT_NAME>[ \n\t]+ {
SAVE_CMD;
}

<TRANS_IMPORT>include {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("INCLUDE ");
#endif
return INCLUDE;}
<TRANS_IMPORT>exclude {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("EXCLUDE ");
#endif
return EXCLUDE;}
<TRANS_IMPORT>[0-9]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("NUMBER ");
#endif
yylval.d=atoi(yytext);return NUMBER;}
<TRANS_IMPORT>to {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("TO ");
#endif
return TO;}
<TRANS_IMPORT>,   {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("COMMA ");
#endif
return COMMA;}
<TRANS_IMPORT>\" { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("TRANS_IMPORT_COMMENT_START ");
#endif
BEGIN TRANS_IMPORT_COMMENT;return  TRANS_IMPORT_COMMENT_START;}
<TRANS_IMPORT>r\" {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("REGX_START ");
#endif
BEGIN REGX;return REGX_START;}
<TRANS_IMPORT>; {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("SEM ");
#endif
if(goto_global){
	goto_global = 0;
	BEGIN 0;
	return SEM;
}else{
	BEGIN READY ;return SEM;
}
}
<TRANS_IMPORT>- {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("HYPHEN ");
#endif
return HYPHEN; }
<TRANS_IMPORT>> {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("GT ");
#endif
return GT ;} 
<TRANS_IMPORT>"(" {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("LBRACE ");
#endif
BEGIN TRANS_IMPORT_NAME ;return LBRACE;}
<TRANS_IMPORT>[\x80-\xFFa-zA-Z0-9_]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; } 
<TRANS_IMPORT>[ \t] {
SAVE_CMD;
} 
<TRANS_IMPORT>. { 
SAVE_CMD;
}
<TRANS_IMPORT>\n {
SAVE_CMD;
printf("\n");}

<TRANS_RULE>= { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("EQ ");
#endif
BEGIN TRANS_PRIORITY;return EQ;}
<TRANS_RULE>@ { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("IMPORT ");
#endif
BEGIN TRANS_IMPORT;return IMPORT;}
<TRANS_RULE>; {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("SME ");
#endif
BEGIN READY ;return SEM;}
<TRANS_RULE>\" { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("COMMENT_START ");
#endif
BEGIN TRANS_RULE_COMMENT;return COMMENT_START;}
<TRANS_RULE>\\n { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("LINE_BREAK ");
#endif
yylval.s=strdup("\n"); return LINE_BREAK;}
<TRANS_RULE>[ \t]+ {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("EMPTY ");
#endif
yylval.s=strdup(" ");return EMPTY; }
<TRANS_RULE>"}" { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("RBRACE\n");
#endif
BEGIN 0;return RBRACE;}
<TRANS_RULE>[^\"=>;}\n\t@ ]+ { 
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("STRING ");
#endif
yylval.s=strdup(yytext) ;return STRING ; }
<TRANS_RULE>. {
SAVE_CMD;
}
<TRANS_RULE>\n {
SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("\n");
#endif
}

<TRANS_PRIORITY>[0-9]+ {

SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("NUMBER ");
#endif
yylval.d=atoi(yytext);return NUMBER;}
<TRANS_PRIORITY>> {

SAVE_CMD;
#ifdef ECHO_TOKEN
 printf("GT ");
#endif
BEGIN READY;return GT;}
<TRANS_PRIORITY>. {

SAVE_CMD;
}
<TRANS_PRIORITY>\n { 

SAVE_CMD;
#ifdef ECHO_TOKEN
printf("\n");
#endif
}




%%



