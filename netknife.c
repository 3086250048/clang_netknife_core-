#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "netknife.h"

void yyerror(char * s ,...){
	va_list ap;
	va_start(ap,s);
	fprintf(stderr,"%d: error: ",yylineno);
	vfprintf(stderr,s,ap);
	fprintf(stderr,"\n");
}

int main(int  argc ,char ** argv ){
		init();
		if(argc<2){
			if(newfile("cmd")){
				yyparse();
			}
		  return 0;
		}else{
			if(newfile(argv[1])){
				yyparse();
			}else{
				return 0;
			}
		}
}
