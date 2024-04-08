#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


int newfile(char * fn ){
	if(stack_count >= MAX_STACK ){
		perror("Too many file stacks");exit(1);
	}
	FILE * f =	fopen(fn,"r");
	struct bufstack * bs=malloc(sizeof(struct bufstack));
	if(!f){ perror(fn);return 0;}
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
	--stack_count;
		return 0;
	}
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	--file_stack_count; 
	return 1;
}


void eval_import(struct import_rule * import_node,char * trans_name){		
		cur_state = IMPORT_TRANS_IMPORT;
		import_stack_count++;
		while(import_node){
			char * filename ;	
			if(import_node->import_name)target_trans=import_node->import_name;
			if(!import_node->import_name)target_trans=ALL_TRANS;

			if(import_node->file_name != NULL){
				filename = import_node->file_name;
			}else{
				filename = curfilename;
			}
			if(newfile(filename)) yyparse();			
			import_node=import_node->next;
		}
		import_stack_count--;
		if(!import_tack_count){
			struct trans *  tmp = get_netknife_node(curfilename,TRANS_NODE,trans_name);
			//将buffer中的所有trans->rule_tab->rule添加到tmp->trans->rule_tab中 		
			cur_state = NULL;
		}
}





