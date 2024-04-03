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
		  yyparse();
		  return 0;
		}else{
			FILE * f = fopen(argv[1],"r");
			file_name = malloc(strlen(argv[1]));
			strcpy(file_name,argv[1]);
			yyrestart(f);
			yyparse();
			fclose(f);
			return 0;
		}
}
