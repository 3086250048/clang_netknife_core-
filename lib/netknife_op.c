#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

static unsigned int netknife_index_hash(char * filename, int  child_type ,char * child_name){
	char * s1 =strdup(filename);
	char s2[10] ;
	sprintf(s2,"%d",child_type);
	char * s3 = strdup(child_name);
	strcat(s1,s2);
	strcat(s1,s3);
	unsigned int hash = 0;
	unsigned c ;
	char * tmp =s1;
	while(c=*tmp++){
		   	hash = hash*9 ^ c;
	}
	free(s1);
	return hash;

}


struct netknife * join_netknife_table( char * filename ,  void * node){
		char * child_name;
		int  child_type ;

		if(*((int *)node) =TRANS_NODE){
		    child_name = ((struct trans *)node)->name;
			child_type = TRANS_NODE; 	
		}
		unsigned int hash = netknife_index_hash(filename,child_type,child_name)%MAX_HASH;
		struct netknife *  tmp = &netknife_tab[hash];
		if(tmp->node_type != NETKNIFE_NODE ){
			tmp->node_type = NETKNIFE_NODE;
			tmp->filename = filename ;
			tmp->child_type = child_type;
		   	tmp->child_name = child_name ;
			tmp->child_tab = node ;	
			return tmp ;
		}else{
			printf("join netknife_table hash conflict\n");exit(1);
		}
}


void  * get_netknife_node(char * filename , int child_type , char * child_name){
		struct netknife * tmp = &netknife_tab[netknife_index_hash(filename,child_type,child_name)%MAX_HASH];	
		if(tmp->node_type == NETKNIFE_NODE){
				return tmp->child_tab;
		}else{
		 	printf("netknife_table no has this entry\n");
		}	
}


struct netknife * netknife_reduce( void  * node){
		if(!node)return NULL ;
		return  join_netknife_table(curfilename ,(struct trans *)node);
}  


