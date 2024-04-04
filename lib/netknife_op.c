#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

static unsigned int trans_index_hash(char * filename,char * trans_name){
	char * s1 = malloc(strlen(filename));
	char * s2 = malloc(strlen(trans_name));
	strcpy(s1,filename);
	strcpy(s2,trans_name);
	char * trans_index = strcat(s1,s2);
	unsigned int hash = 0;
	unsigned c ;
	while(c=*trans_index++) hash = hash*9 ^ c;
	return hash;
}


struct netknife * join_netknife_table(voud * node_tab){


}

void  * get_node_table(struct trans_table * trans_tab , char * filename , char * trans_name){
		struct trans_table * tmp = &trans_tab[trans_index_hash(filename,trans_name)%MAX_HASH];
		
		if(tmp->trans){
				return tmp->trans;
		}else{
		 	printf("trans_table no has this entry\n");
		}	
}
