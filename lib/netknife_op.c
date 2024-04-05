#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

static unsigned int netknife_index_hash(char * filename, int  child_type ,char * child_name){
	char * s1 = malloc(strlen(filename));
	char * s2 = malloc(strlen(child_name));
	char * s3[10];
	sprintf(s3,"%d",child_type);
	strcpy(s1,filename);
	strcpy(s2,child_name);
	char * trans_index = strcat(s1,s2);
	trans_index = strcat(trans_index,s3);
	unsigned int hash = 0;
	unsigned c ;
	while(c=*trans_index++) hash = hash*9 ^ c;
	return hash;
}


struct netknife * join_netknife_table(char * filename , int  child_type , char * child_name , void * child_tab){
		struct netknife *  tmp = &netknife_tab[netknife_index_hash(filename,child_type,child_name)%MAX_HASH];
		if(tmp->child_type != NETKNIFE_NODE ){
			tmp->child_type = NETKNIFE_NODE;
			tmp->filename = filename ;
			tmp->child_type = child_type;
		   	tmp->child_name = child_name ;
			tmp->child_tab = child_tab ;	
			return tmp ;
		}else{
			perror("netknife hash conflict");exit(1);
		}

}

void  * get_node_table(char * filename , int child_type , char * child_name){
		struct netknife * tmp = &netknife_tab[netknife_index_hash(filename,child_type,child_name)%MAX_HASH];	
		if(tmp->child_type == NETKNIFE_NODE){
				return tmp->child_tab;
		}else{
		 	printf("netknife_table no has this entry\n");
		}	
}
