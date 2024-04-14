#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>
#include <regex.h>


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
	curfilter = tmp->filter;
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

int regx_match(char * regx , char * str){
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, regx, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // 匹配字符串
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
    	regfree(&regex);
		return 0;
    } else if (reti == REG_NOMATCH) {
    	regfree(&regex);
		return 1;
    } else {
    	regfree(&regex);
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}


void drop_buffer(struct buffer * tmp ){
	struct buffer * prev = tmp->prev;
	struct buffer * next = tmp->next;
    free(tmp);
	prev->next = next;
	next->prev = prev;				
}

int get_comment_lineno(struct buffer * buf,char * c){
	while(buf){
		char  * comment =((struct comment *)buf->buffer)->c
		if( !strcmp((comment,c) )return  ((struct comment *)buf->buffer)->lineno;	
	}
	/*当c_buf中不存在传入的comment则return -1*/
	return -1;
}

/*将buffer中的数据根据filter过滤*/
struct buffer * filter_buffer(){
		struct buffer * tmp = buffer_root;
		int s_lineno ;
		int d_lineno ;
		char * s_comment;
		char * d_comment;
		char * regx;
		if(!curfilter)return NULL; 
		struct filter* filter = curfilter;
		
		struct buffer * c_buf=NULL;
		while(tmp){
		   if(tmp->buffer_type == COMMENT_NODE){
		  		assign_join_buffer_chain(c_buf,"TMP","TMP",COMMENT_NODE,tmp->buffer); 
		   }	
		   tmp=tmp->next;
		} 

		while(tmp){
				while(filter){
				struct range * range = curfilter->range;
						while(range){
								if(range->s_lineno)s_lineno=range->s_lineno;
								if(ranfe->d_lineno)d_lineno=range->d_lineno;
								if(range->s_comment)s_comment=range->s_comment;
								if(range->d_comment)d_comment=range->d_comment;
								if(range->d_comment)regx=range->regx;
								if(tmp->buffer_type == RULE_NODE){
									struct rule * rule =(struct rule *)tmp->buffer;
								}else{
									continue ;
								}
								//regx only
								if(regx){
									if(filter->node_type == INCLUDE_NODE){
										//判断是否匹配正则
										if(regx_match(regx,rule->s)drop_buffer(tmp); 
									}
									if(filter->node_type == EXCLUDE_NODE){
										if(!regx_match(regx,rule->s))drop_buffer(tmp);
									}
										
								}
								//s_lineno only
								if(s_lineno && !d_lineno && !s_comment && !d_comment){
									if(filter->node_type == INCLUDE_NODE){
										if(rule->lineno !=  s_lineno)drop_buffer(tmp);
									}
									if(filter->node_type == EXCLUDE_NODE){
										if(rule->lineno ==  s_lineno)drop_buffer(tmp);
									}
								}
								//s_comment only
								if(s_comment && !d_comment && !s_lineno && !d_lineno)
								{
									int lineno = get_comment_lineno(buf_c , s_comment);
									if(lineno== -1){ printf("This comment does not exist");exit(-1); }
									if(filter->node_type == INCLUDE_NODE){
										if(rule->lineno != lineno)drop_buffer(tmp); 	
									}
									if(filter->node_type == EXCLUDE_NODE){
										if(rule->lineno == lineno)drop_buffer(tmp);
									}
								}

								//s_lineno and d_lineno only
								if(s_lineno && d_lineno && !s_commet && !d_comment ){
									if(s_lineno > d_lineno){
										int a = s_lineno;
										s_lineno = d_lineno ;
										d_lineno = a;
									}
									if(filter->node_type == INCLUDE_NODE){
										if(  rule->lineno < s_lineno || rule->lineno >d_lineno  )drop_buffer(tmp);
									}
									if(filter->node_type == EXCLUDE_NODE){
										if( rule->lineno>= s_lineno && rule->lineno<=d_lineno  )drop_buffer(tmp);	
									}

															
								}
								
								//s_lineno and d_comment only
								if(s_lineno && d_comment){
									if(filter->node_type == INCLUDE_NODE){
									
									}
									if(filter->node_type == EXCLUDE_NODE){
									
									}

								}
								//s_comment  and d_comment only
								if(s_comment && d_comment){
									if(filter->node_type == INCLUDE_NODE){
									
									}
									if(filter->node_type == EXCLUDE_NODE){
									
									}

								
								}
								//s_comment  and d_lineno only
								if(s_comment && d_lineno){
									if(filter->node_type == INCLUDE_NODE){
									
									}
									if(filter->node_type == EXCLUDE_NODE){
									
									}

								
								
								}
								range=range->next;
						}
					filter=filter->next;
				}
				tmp=tmp->next;
				if(tmp->node_type == _EOF_ ) break;
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
				//执行buffer_filter 
				

				//添加buffer终结_EOF_,防止不同import语句的filter互相干扰
				join_buffer_chain("EOF","EOF",_EOF_);
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
			//get_buffer包含重置buffer_root动作
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





