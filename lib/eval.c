#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>


int newfile(char * fn ){
	if(file_stack_count >= MAX_STACK || import_stack_count >= MAX_STACK ){
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

int newfilter(struct filter * filter){
	if(filter_stack_count >= MAX_STACK ){
		printf("Too many filter stacks \n");
		exit(1);
	}		
    struct filterstack * tmp  = malloc(sizeof(struct filterstack));
	tmp->prev=curfilterstack ;
	tmp->filter = filter ;
	curfilterstack = tmp;
	filter_stack_count++;
	return 1 ;
}

int popfilter(void){
	curfilter = curfilterstack->prev->filter;
	struct filterstack * tmp=curfilterstack;
	curfilterstack = curfilterstack->prev;
	free(tmp);
	filter_stack_count--;
	return 1;
}

/*将buffer中的数据根据filter过滤*/
struct buffer * filter_buffer(){
		struct buffer * tmp = buffer_root;
		int s_lineno ;
		int d_lineno ;
		char * s_comment;
		char * d_comment;
		char * regx;
		while(tmp){
			while(curfilter){
				if(curfilter->range->s_lineno)s_lineno=curfilter->range->s_lineno;
				if(curfilter->ranfe->d_lineno)d_lineno=curfilter->range->d_lineno;
				if(curfilter->range->s_comment)s_comment=curfilter->range->s_comment;
				if(curfilter->range->d_comment)d_comment=curfilter->range->d_comment;
				if(curfilter->range->d_comment)regx=curfilter->range->regx;
				if(regx){
					return 
				}
				if(s_lineno && d_lineno){
						
				}
				if(s_lineno && d_comment){
				}
				if(s_comment && d_comment){
				
				}
				if(s_comment && d_lineno){
				
				
				}
			}		
		}	
}


void eval_import(struct import_rule * import_node,char * trans_name){		
		int result;
		/*设置起始参数*/
		if(!import_stack_count)
		{
			cur_state = IMPORT_TRANS_STATE;			
			start_trans = trans_name ; 			
		}
		cur_state = IMPORT_TRANS_STATE;
		/*执行import动作*/
		while(import_node){
			//添加filter栈
			if(!newfilter(import_node->filter)){ printf("push filter stack error\n");exit(1);} 
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
				//弹出filter栈
				if(!popfilter()){ printf("pop filter stack error\n");exit(1); }
				import_node=import_node->next;
			}
		}
		
			/*import最终归约*/
		if(!import_stack_count){
			struct trans *  tmp = get_netknife_node(curfilename,TRANS_NODE,start_trans );
			struct rule_table * rule_tab  = tmp->rule_tab;
			struct comment_table * comment_tab =  tmp->comment_tab ;	

			struct buffer * buf_root = get_buffer();
			while(buf_root){
				if(buf_root->buffer_type == RULE_NODE)assign_join_rule_table(rule_tab,buf_root->buffer);
				if(buf_root->buffer_type == COMMENT_NODE) assign_join_comment_table(comment_tab,buf_root->buffer)	;
				buf_root=buf_root->next;
			}
			cur_state = NORMAL_STATE;
			start_trans=NULL;
		}
}





