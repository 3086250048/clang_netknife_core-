#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

struct buffer * buffer_root = NULL;

void join_buffer_chain( char * filename , char * buffer_name , int buffer_type ,  void * buffer){
		if(filename==NULL || buffer_name  == NULL || buffer== NULL ) {printf("element is NULL\n");exit(1);}
		struct buffer * tmp =malloc(sizeof(struct buffer));
		tmp->node_type = BUFFER_NODE;
		tmp->filename = filename;
		tmp->buffer_type = buffer_type;
		tmp->buffer_name = buffer_name;
		tmp->buffer = buffer ;
		tmp->next = buffer_root;
		buffer_root = tmp;
}

struct buffer * get_buffer(){
	struct buffer * tmp = buffer_root ;
	buffer_root = NULL;
	return tmp;
}
