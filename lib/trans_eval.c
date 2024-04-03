#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


int newfile_trans(char * fn ){
	FILE * f =	fopen(fn,"r");
	struct bufstack * bs=malloc(sizeof(bufstack));
	if(!f){ perror(fn), return 0};
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

	if(!prevbs) return 0;
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	return 1;
}

struct trans_table * eval_trans(void  * p ){
		 switch((*(int *)p)){
			case TRANS_TABLE_NODE :
				eval_trans(p->trans);
				break;
			case TRANS_NODE:
				eval_trans(p->import_rule_chain);
			case IMPORT_NODE:
				if(p->file_name != NULL){
				     
				}
		 }		
	 }
} 





