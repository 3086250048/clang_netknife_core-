#include <stdio.h>
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
		  yyparse();
		  return 0;
		}else{
			FILE * f = fopen(argv[1],"r");
			yyrestart(f);
			yyparse();
			fclose(f);
			return 0;
		}
}
