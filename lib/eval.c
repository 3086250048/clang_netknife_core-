#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


int newfile(char * fn ){
	if(file_stack_count >= MAX_STACK ){
		printf("Too many file stacks\n");exit(1);
	}
	FILE * f =	fopen(fn,"r");
	struct bufstack * bs=malloc(sizeof(struct bufstack));
	if(!f){ perror(fn);exit(1);}
	if(!bs) { perror("malloc"); exit(1);}

	//记住当前状态
	if(curbs)curbs->lineno = yylineno ;
	bs->prev=curbs ;
	//建立当前文件信息
	bs->bs=yy_create_buffer(f,YY_BUF_SIZE);
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
		
	if(!bs) return 0;
	//删除当前文件信息
	fclose(bs->f);
	yy_delete_buffer(bs->bs);
	//切换为上一个文件
	prevbs = bs->prev;
	free(bs);
	if(!prevbs){
	--file_stack_count;
		return 0;
	}
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	--file_stack_count; 
	return 1;
}

int newimport(char * filename , char * target_trans, struct filter * filter ){
	struct import_trans * cur = malloc(sizeof(struct import_trans));
	if(!cur){ perror("malloc err");exit(1);}
	cur->filename = filename;
	cur->target_trans = target_trans;
	cur->filter=filter;
	cur->prev=cur_import_trans;
	cur_import_trans=cur;
	return 1;
}

int popimport(){
	if(!cur_import_trans) return 0;
	struct import_trans * tmp = cur_import_trans;
	curfilename = cur_import_trans->filename;
	target_trans = cur_import_trans->target_trans;
	curfilter = cur_import_trans->filter;
	cur_import_trans = cur_import_trans->prev;
	free(tmp);
	return 1;
}


