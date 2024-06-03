#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


struct stack *  Push ( struct  stack ** root, char * filename , char * name , int type ,  void * buffer){
		struct stack  * tmp =malloc(sizeof(struct stack));
		tmp->filename = filename;
		tmp->type = type;
		tmp->name = name;
		tmp->buffer = buffer ;
		tmp->next = NULL;
		tmp->prev = NULL;
		if( *root == NULL){
			*root = tmp;
			return tmp;
		}
		(*root)->prev = tmp;
		tmp->next = *root;
		*root = tmp;
		return tmp;
}

struct stack * Top(struct stack ** root){
		if(*root){
			return *root;
		}
		return NULL;
}

void   Pop(struct stack ** root){
		struct stack * tmp = *root; 
		if(tmp){
		free(tmp);
		*root=(*root)->next ;
		}
}


unsigned long buffer_index_hash(const char * filename, int  type ,const char * name){
    unsigned long combined_hash = hash_string(filename);
    combined_hash = combine_hashes(combined_hash, hash_string(name));
    combined_hash = combine_hashes(combined_hash, type);
    return combined_hash;
}


struct table *  Add( struct table ** root , char * filename , char * name , int type  , void * buffer){	
	if(!*root){
	 	*root = calloc(MAX_HASH,sizeof(struct table));	
	}
	unsigned int hash = buffer_index_hash(filename,type,name)%MAX_HASH;
	struct table * tmp = &(*root)[hash];
	if(!tmp->buffer ){
    	tmp->filename = filename;
		tmp->name = name;
		tmp->type = type;
		tmp->buffer = buffer;
		tmp->dup_buffer = NULL;
		return tmp;
	}else{
		struct table * tail = tmp ;
		struct table  * dup = malloc(sizeof(struct table));
		while(tail->dup_buffer){
			tail = tail->dup_buffer;
		}
    	dup->filename = filename;
		dup->name = name;
		dup->type = type;
		dup->buffer = buffer;
		dup->dup_buffer = NULL;	
		tail->dup_buffer = dup;
		return dup ;
	}
	
}

struct table * Clear(struct table ** root){
	 struct table * r = *root ;
	 free(r);
	 *root  = calloc(MAX_HASH,sizeof(struct table));
}

struct  table * Get( struct table * root , char * filename , char * name , int type){
	unsigned int hash = buffer_index_hash(filename,type,name)%MAX_HASH;
	struct table * tmp = &root[hash];
	if(tmp->type){
		return tmp;
	}else{
		return NULL;
/*		err("get_buf","buf no has this entry");
		exit(1); */
	}
}





