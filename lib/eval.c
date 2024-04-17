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
	if(!filter){
		 struct filter * filter =malloc(sizeof(struct filter));
		 filter->node_type = SKIP_NODE;
	}	
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
	if(!curfilterstack || !curfilter ) return 1;
	if(filter_stack_count>1){
	curfilter = curfilterstack->prev->filter;
	struct filterstack * tmp=curfilterstack;
	curfilterstack = curfilterstack->prev;
	free(tmp);
	filter_stack_count--;
	return 1;
	}else{
		curfilter = NULL;
		return 1;
	}
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


struct buffer * drop_buffer(struct buffer * tmp ){
	/*drop标志位置1*/
	if(tmp->prev) tmp->prev->next = tmp->next;
	if(tmp->next) tmp->next->prev= tmp->prev;
	struct buffer * cur = tmp->next;
    free(tmp);
	return cur;
}

int get_comment_lineno(struct buffer * buf,char * c){
	while(buf){
		char  * comment =((struct comment *)buf->buffer)->c;
		if( !strcmp(comment,c) )return  ((struct comment *)buf->buffer)->lineno;	
	}
	/*当c_buf中不存在传入的comment则return -1*/
	return -1;
}

int bitmap( char * regx , int s_lineno , int d_lineno , char * s_comment ,char * d_comment ){
	if(regx)return REGX_ONLY ;
	if(s_lineno!=0 && d_lineno == 0 && s_comment ==0 && d_comment == 0 ) return S_LINENO_ONLY;
	if(s_comment!=0 && d_comment == 0 && s_lineno ==0 && d_lineno ==0 )return S_COMMENT_ONLY ;
	if(s_lineno!=0 && d_lineno != 0 && s_comment == 0 && d_comment == 0) return LINENO_ONLY;
	if(s_comment != 0 && d_comment !=0 && s_lineno == 0 && d_lineno ==0 ) return COMMENT_ONLY;
	if(s_lineno!=0 && s_comment!=0 && d_lineno == 0 && d_comment ==0) return LINENO_AND_COMMENT;
}

void swap_number(int * a , int * b){
	int tmp  = *a  ;
	*a =*b  ;
	*b = tmp ;
}

struct buffer * extract_buffer(struct buffer * buf,int node_type ){
	struct buffer * tmp = NULL;
	while(buf){
		 if(buf->buffer_type == node_type){
		  	tmp = assign_join_buffer_chain(tmp,"TMP","TMP",node_type,buf->buffer); 
		  }	
		  buf=buf->next;
	} 
	return tmp;
}

/*将buffer中的数据根据filter过滤*/
struct rule *  filter_rule(struct rule * rule,struct buffer * c_buf){
		/*如果不存在filter则直接退出*/
		if(!curfilter || !curfilterstack || curfilter->node_type == SKIP_NODE)return rule; 
		struct filter* filter = curfilter;		
		/*合并filter中的range*/
		struct buffer * range_buf=NULL ;
		while(filter){
			struct range * range = filter->range;
			while(range){
				if(filter->node_type == INCLUDE_NODE )range_buf = assign_join_buffer_chain(range_buf,"RANGE","INCLUDE",RANGE_NODE,range); 
				if(filter->node_type == EXCLUDE_NODE) range_buf = assign_join_buffer_chain(range_buf,"RANGE","EXCLUDE",RANGE_NODE,range); 
				range=range->next;
			}
			filter = filter->next;
		}
		/*判断rule是否符合filter*/
		while(range_buf){
				struct range * range = range_buf->buffer;
				int mode = bitmap(range->regx,range->s_lineno,range->d_lineno,range->s_comment ,range->d_comment);
				/*regx*/
				if( mode==REGX_ONLY ){
					if(range_buf->buffer_name="INCLUDE" )if(!regx_match(range->regx,rule->s)) return rule ;
					if(range_buf->buffer_name="EXCLUDE" )if(!regx_match(range->regx,rule->s)) return NULL;
				}
				/*s_lineno*/
				if(mode == S_LINENO_ONLY ){
					if(range_buf->buffer_name="INCLUDE" )if(rule->lineno ==  range->s_lineno) return rule;
					if(range_buf->buffer_name="EXCLUDE" )if(rule->lineno ==  range->s_lineno) return NULL;
				}
				/*s_comment*/
				if( mode == S_COMMENT_ONLY )
				{
					int lineno = get_comment_lineno(c_buf , range->s_comment);
					if(lineno== -1){ printf("This comment does not exist");exit(-1); }
					if(range_buf->buffer_name="INCLUDE" )if(rule->lineno == lineno) return rule ; 	
					if(range_buf->buffer_name="EXCLUDE" )if(rule->lineno == lineno) return NULL;
				}	
				/*lineno*/
				if( mode == LINENO_ONLY){
					if(range->s_lineno > range->d_lineno)	swap_number(&range->s_lineno, &range->d_lineno);
					if(range_buf->buffer_name="INCLUDE" )if(rule->lineno >= range->s_lineno && rule->lineno <= range->d_lineno)return rule;
					if(range_buf->buffer_name="EXCLUDE" )if(rule->lineno >= range->s_lineno && rule->lineno <= range->d_lineno)return NULL;	
				}
				/*comment*/
				if( mode == COMMENT_ONLY){
					int s_c = get_comment_lineno(c_buf , range->s_comment);
					int d_c = get_comment_lineno(c_buf,range->d_comment);
					if(s_c== -1 || d_c == -1){ printf("This comment does not exist");exit(-1); }
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(range_buf->buffer_name="INCLUDE" )if(  rule->lineno >= s_c && rule->lineno <= d_c)return rule;
					if(range_buf->buffer_name="EXCLUDE" )if(  rule->lineno >= s_c &&  rule->lineno <= d_c)return NULL;		
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					int s_c = get_comment_lineno(c_buf ,range->s_comment);
					if(s_c== -1){ printf("This comment does not exist");exit(-1); }
					if(range->s_lineno > s_c) swap_number(&range->s_lineno,&s_c);
					if(range_buf->buffer_name="INCLUDE" )if(  rule->lineno >= range->s_lineno && rule->lineno <=s_c)return rule;
					if(range_buf->buffer_name="EXCLUDE" )if( rule->lineno>= range->s_lineno && rule->lineno<=s_c)return NULL;		
				}
				range_buf = range_buf->next ;
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
			/*添加filter栈*/
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
				/*添加buffer终结_EOF_,防止不同import语句的filter互相干扰*/
				join_buffer_chain("EOF","EOF",EOF_NODE,"EOF");
				import_stack_count--;	
				import_node=import_node->next;
			}
		}
		


		/*import最终归约*/
		if(!import_stack_count){
			struct trans *  tmp = get_netknife_node(curfilename,TRANS_NODE,start_trans );
			struct rule_table * rule_tab  = tmp->rule_tab;
			struct comment_table * comment_tab =  tmp->comment_tab ;	
			/*get_buffer包含重置buffer_root动作*/
			struct buffer * buf_root = get_buffer();
			/*提取所有comment*/
			struct buffer * c_buf= extract_buffer(buf_root,COMMENT_NODE);
			/*跳过初始的EOF头*/
			buf_root = buf_root->next;		
			while(buf_root){
				if(buf_root->buffer_type==EOF_NODE) popfilter();
				if(buf_root->buffer_type == RULE_NODE){
					struct rule * rule = filter_rule(buf_root->buffer,c_buf);
					if(rule)assign_join_rule_table(rule_tab,rule);
				}
				if(buf_root->buffer_type == COMMENT_NODE) assign_join_comment_table(comment_tab,buf_root->buffer)	;
				buf_root=buf_root->next;
			}
			cur_state = NORMAL_STATE;
			start_trans=NULL;
		}
}





