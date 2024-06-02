#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

unsigned long netknife_index_hash(const char * filename ,  int child_type , const char * child_name) {
    unsigned long combined_hash = hash_string(filename);
    combined_hash = combine_hashes(combined_hash, hash_string(child_name));
    combined_hash = combine_hashes(combined_hash, child_type);
    return combined_hash;
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
			err("join_netknife_table","join netknife_table hash conflict");
		}
}


void  * get_netknife_node(char * filename , int child_type , char * child_name){
		struct netknife * tmp = &netknife_tab[netknife_index_hash(filename,child_type,child_name)%MAX_HASH];	
		if(tmp->node_type == NETKNIFE_NODE){
				return tmp->child_tab;
		}else{
			err("get_netknife_node","netknife_table no has this entry");
		}	
}


struct netknife * netknife_reduce( void  * node){
		if(!node)return NULL ;
		if(start_file){
			struct netknife * n =  join_netknife_table(start_file ,(struct trans *)node);
			RESET_START_FILE ;
			return n;
		}else{
			struct netknife * n =  join_netknife_table(curfilename ,(struct trans *)node);
			return n;
		}
}  


