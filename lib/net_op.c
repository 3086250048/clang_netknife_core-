#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>
#include <libssh/libssh.h>

void excute_ssh_command(char * raw ){
	 struct rule_table * tmp= NULL; 
	 if(after_filter_trans){
		tmp =  after_filter_trans->rule_tab ;
	 }
	 char * str = raw; 
	int i;
	if(tmp){
		for(i=0;i<MAX_HASH;i++){
			if(tmp[i].r){
			if(!strcmp(raw,tmp[i].r->s)){
					str = tmp[i].r->d;
					break;
			}
			}
		}
	}
	 printf("raw<%s>\n",raw);
	 printf("send<%s>\n",str); 
}


