#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

struct buffer * buffer_root = NULL;

struct buffer *  assign_join_buffer_chain( struct buffer * root, char * filename , char * buffer_name , int buffer_type ,  void * buffer){
		if(filename==NULL || buffer_name  == NULL || buffer== NULL )err("assign_join_buffer_chain","element is NULL");
		struct buffer * tmp =malloc(sizeof(struct buffer));
		tmp->node_type = BUFFER_NODE;
		tmp->filename = filename;
		tmp->buffer_type = buffer_type;
		tmp->buffer_name = buffer_name;
		tmp->buffer = buffer ;
		tmp->next = NULL;
		tmp->prev = NULL;
		if(root == NULL){
			root = tmp;
			return root;
		}
		root->prev = tmp;
		tmp->next = root;
		root = tmp;
		return root;
}

void join_buffer_chain( char * filename , char * buffer_name , int buffer_type ,  void * buffer){
		if(filename==NULL || buffer_name  == NULL || buffer== NULL )  err("join_buffer_chain","element is NULL");
		struct buffer * tmp =malloc(sizeof(struct buffer));
		tmp->node_type = BUFFER_NODE;
		tmp->filename = filename;
		tmp->buffer_type = buffer_type;
		tmp->buffer_name = buffer_name;
		tmp->buffer = buffer ;
		tmp->next = NULL;
		tmp->prev = NULL;
		if(buffer_root == NULL){
			buffer_root = tmp;
			return ;
		}
		buffer_root->prev = tmp;
		tmp->next = buffer_root;
		buffer_root = tmp;
}

struct buffer * get_buffer(){
	struct buffer * tmp = buffer_root ;
	buffer_root = NULL;
	return tmp;
}

static unsigned int buf_index_hash(char * filename, int  buf_type ,char * buf_name){
	char * s1 =strdup(filename);
	char s2[10] ;
	sprintf(s2,"%d",buf_type);
	char * s3 = strdup(buf_name);
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


void join_buf( char * filename , char * buf_name , int buf_type , void * buf){
		
	unsigned int hash = buf_index_hash(filename,buf_type,buf_name)%MAX_HASH;
	struct buf * tmp = &buf_tab[hash];
	if(tmp->node_type != BUF_NODE){
		tmp->node_type =BUF_NODE;
    	tmp->filename = filename;
		tmp->buf_name = buf_name;
		tmp->buf_type = buf_type;
		tmp->buf = buf;
		tmp->dup_buf = NULL;
	}else{
		struct buf * tail = tmp ;
		struct buf * dup = malloc(sizeof(struct buf));
		while(tail->dup_buf){
			tail = tail->dup_buf;
		}
		dup->node_type =BUF_NODE;
    	dup->filename = filename;
		dup->buf_name = buf_name;
		dup->buf_type = buf_type;
		dup->buf = buf;
		dup->dup_buf = NULL;	
		tail->dup_buf = dup;
	}
	
}

struct buf * get_buf( char * filename , char * buf_name , int buf_type){
	unsigned int hash = buf_index_hash(filename,buf_type,buf_name)%MAX_HASH;
	struct buf * tmp = &buf_tab[hash];
	if(tmp->node_type == BUF_NODE){
		return tmp;
	}else{
		err("get_buf","buf no has this entry");
	}
}


