#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


int newfile(char * fn ){
	if(file_stack_count >= MAX_STACK ){
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


void eval_import(struct import_rule * import_node,char * trans_name){		
		int result;
		if(!import_stack_count)
		{
			start_trans = trans_name ; 			
		}
		cur_state = IMPORT_TRANS_STATE;
		while(import_node){
			char * filename ;	
			if(import_node->import_name)target_trans=import_node->import_name;
			if(!import_node->import_name)target_trans=ALL_TRANS;

			if(import_node->file_name != NULL){
				filename = import_node->file_name;
			}else{
				filename = curfilename;
			}
			if(newfile(filename)){
				import_stack_count++;
				 result = yyparse();			
			}
			if(!result){
				import_stack_count--;	
				import_node=import_node->next;
			}
		}
		if(!import_stack_count){
			struct trans *  tmp = get_netknife_node(curfilename,TRANS_NODE,start_trans );
			struct rule_table * rule_tab  = tmp->rule_tab;
			struct comment_table * comment_tab =  tmp->comment_tab ;	

			struct buffer * buf_root = get_buffer();
			while(buf_root){
				if(buf_root->node_type == RULE_NODE) assign_join_rule_table(rule_tab,buf_root->buffer);
				if(buf_root->node_type == COMMENT_NODE) assign_join_comment_table(comment_tab,buf_root->buffer)	;
				buf_root=buf_root->next;
			}
			cur_state = 0;
			start_trans=NULL;
		}
}





