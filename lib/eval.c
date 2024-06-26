#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


void append_string(char **dest, const char *src) {
    size_t dest_len = strlen(*dest);
    size_t src_len = strlen(src);
    
    // Reallocate memory for destination string
    *dest = (char *)realloc(*dest, dest_len + src_len + 1); // +1 for null terminator
    if (*dest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Append source string to destination string
    strcpy(*dest + dest_len, src);
}



unsigned long hash_string(const char * str){
	unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

unsigned long combine_hashes(unsigned long hash1, unsigned long hash2) {
    return hash1 ^ hash2;
}

void err_node(void * node,char * banner ){
	
	for(int i=0;i<50;i++)fprintf(stderr,"-");
	fprintf(stderr,"\n");
	fprintf(stderr,"%s\n",banner);
	if(*((int *)node) == RANGE_NODE ){
		stderr_print_range(node);
	}
	for(int i=0;i<50;i++)fprintf(stderr,"-");
	fprintf(stderr,"\n");

}

void err(char * state , char * err){
	for(int i=0;i<50;i++)fprintf(stderr,"-");
	fprintf(stderr,"\n");
	fprintf(stderr,"filename:%s\n",curfilename);
	fprintf(stderr,"file_stack_count:%d\n",file_stack_count);
	fprintf(stderr,"last_read_trans_name:%s\n",cur_trans);
	fprintf(stderr,"line:%d\n",yylineno);
	fprintf(stderr,"state:%s\n",state);
	fprintf(stderr,"err:%s\n",err);
	for(int i=0;i<50;i++)fprintf(stderr,"-");
	fprintf(stderr,"\n");
}

int newfile(char * fn ){	
	if(file_stack_count >= MAX_STACK ){
		err("newfile","too many file stacks");
		exit(1);
	}

	FILE * f ;
	if(strcmp(fn,"cmd")!=0) {
			f =	fopen(fn,"r");
	}else{
			f = stdin;
	}
	struct bufstack * bs=malloc(sizeof(struct bufstack));
	if(!f && fn ) {err("openfile","no file with the same name was found");exit(1);};
	if(!bs) { perror("malloc"); exit(1);}

	//记住当前状态
	if(curbs)curbs->lineno = yylineno ;
	bs->prev=curbs ;
	//建立当前文件信息
	if(file_stack_count !=0 &&  !strcmp(fn,"cmd") ){
		bs->bs = yy_scan_string(cmd_input);
	}else{
		bs->bs=yy_create_buffer(f,YY_BUF_SIZE);
	}
	
  	bs->f=f;
	bs->filename=fn;
	yy_switch_to_buffer(bs->bs);
	curbs=bs;
	yylineno=1;
	curfilename = fn;
	++file_stack_count ;
	return 1;
}


int popfile(void){
	struct bufstack * bs = curbs;
	struct bufstack * prevbs;
	
	if(!bs ) return 0 ;	

	//删除当前文件信息
	if( strcmp(bs->filename,"cmd")!=0){
			fclose(bs->f);
	}

	yy_delete_buffer(bs->bs);

	//切换为上一个文件
	prevbs = bs->prev;
	free(bs);
	if(!prevbs) return 0;
	
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	--file_stack_count; 
	return 1;
}




