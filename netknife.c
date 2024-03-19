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

int main(){
	return yyparse();
}
