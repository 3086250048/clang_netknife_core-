#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <calc_fn.h>


//符号表



unsigned int symhash(char * sym){
	unsigned int hahs  = 0;
	unsigned  int  c;
	while (c = *sym++) hash = hash * 9 ^ c;
    return hash ;
}

