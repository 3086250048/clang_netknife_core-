#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define A ""
int main() {
		FILE * f = stdin;
		if(!f){ printf("error\n");}
		f = fopen("netknife1","r");

		if(!f){ printf("error\n");}
 		f = fopen("netknife1","r");

		if(!f){ printf("error\n");}
 		f = fopen("netknife1","r");
}

[\x80-\xFFa-zA-Z0-9_]+ {
#ifdef ECHO_TOKEN 
 printf("STRING ");
#endif
SAVE_CMD ;yylval.s=strdup(yytext );return STRING;} 

