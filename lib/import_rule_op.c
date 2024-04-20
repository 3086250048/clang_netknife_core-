#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>
#include <regex.h>

static struct import_rule * import_rule_root = NULL;


struct range * join_range(struct range * root , char * regx ,int s_lineno ,int d_lineno ,char * s_comment,char * d_comment )
{
	struct range * tmp = malloc(sizeof(struct range));
	tmp->node_type = RANGE_NODE;
	tmp->regx = regx;
	tmp->s_lineno = s_lineno;
	tmp->d_lineno = d_lineno;
	tmp->s_comment = s_comment;
	tmp->d_comment = d_comment;
	tmp->next = root;
	root = tmp;
	return root ;
}




void print_range(struct range * range_root){
	 struct range * tmp = range_root ;
	 while(tmp){
	 	printf("%*snode_type:RANGE_NODE\n",PRINT_RANGE);
		printf("%*sregx:%s\n",PRINT_RANGE,tmp->regx);
		printf("%*ss_lineno:%d\n",PRINT_RANGE,tmp->s_lineno);
		printf("%*sd_lineno:%d\n",PRINT_RANGE,tmp->d_lineno);
		printf("%*ss_comment:%s\n",PRINT_RANGE,tmp->s_comment);
		printf("%*sd_comment:%s\n",PRINT_RANGE, tmp->d_comment);
		tmp=tmp->next;
	 }

}


struct filter * join_filter(struct filter * root , int node_type ,struct range * range){
		struct filter *  tmp = malloc(sizeof(struct filter));
		tmp->node_type = node_type ;
		tmp->range=range;
		tmp->next = root;
		root = tmp;
		return root;
}

void print_filter(struct filter * filter_root){
	while(filter_root){
		if(filter_root->node_type == INCLUDE_NODE){
			printf("%*snode_type:INCLUDE_NODE\n",PRINT_FILTER);
		}else{
			printf("%*snode_type:EXCLUDE_NODE\n",PRINT_FILTER);	
		}
		print_range(filter_root->range);
		filter_root=filter_root->next;
	}
}


struct  import_rule * join_import_rule(char * file_name ,char * import_name , int lineno,struct filter * filter ){
	struct import_rule * tmp = malloc(sizeof(struct import_rule));
	tmp->node_type = IMPORT_NODE;
	tmp->lineno = lineno ;
	tmp->file_name = file_name ;
	tmp->import_name=import_name;
	tmp->filter = filter ;
	tmp->next = import_rule_root ;
	import_rule_root = tmp ;
	return  tmp ;
}


struct import_rule * get_import_rule(){
	struct import_rule * tmp = import_rule_root;
	import_rule_root = NULL;
	return tmp ;
}







void print_import_rule(struct import_rule * import_rule_root){
	struct import_rule * tmp = import_rule_root;
	while(tmp){
		printf("%*snode_type:IMPORT\n",PRINT_IMPORT);
		printf("%*sfile_name:%s\n",PRINT_IMPORT,tmp->file_name);
		printf("%*simport_name:%s\n",PRINT_IMPORT,tmp->import_name);
		printf("%*slineno:%d\n",PRINT_IMPORT,tmp->lineno);
		print_filter(tmp->filter);
		tmp = tmp->next;
	}
}


int regx_match(char * regx , char * str){
    regex_t regex;
    int reti;
    char msgbuf[100];
	int flag =  REG_NOSUB | REG_EXTENDED;
    reti = regcomp(&regex, regx,flag);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    // 匹配字符串
    reti = regexec(&regex, str, 0, NULL,0);
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



int exist_comment (char * c){
	struct buf * buf =  get_buf(curfilename,c,COMMENT_NODE);
	if(buf->node_type == BUF_NODE){ 
	 	return ((struct comment *)buf)->lineno;
	}else{
		return 0;
	}
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



/*将buffer中的数据根据filter过滤*/
struct rule *  filter_rule(struct rule * rule){
		/*如果不存在filter则直接退出*/
		if(!curfilter )return rule; 
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
					int lineno = exist_comment( range->s_comment);
					if(lineno== -1){ printf("This comment does not exist\n");exit(-1); }
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
					int s_c = exist_comment( range->s_comment);
					int d_c = exist_comment( range->d_comment);
					if(!s_c || !d_c){ printf("This comment does not exist\n");exit(-1); }
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(range_buf->buffer_name="INCLUDE" )if(  rule->lineno >= s_c && rule->lineno <= d_c)return rule;
					if(range_buf->buffer_name="EXCLUDE" )if(  rule->lineno >= s_c &&  rule->lineno <= d_c)return NULL;		
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					
					int s_c = exist_comment( range->s_comment);
					if(!s_c){ printf("This comment does not exist");exit(-1); }
					if(range->s_lineno > s_c) swap_number(&range->s_lineno,&s_c);
					if(range_buf->buffer_name="INCLUDE" )if(  rule->lineno >= range->s_lineno && rule->lineno <=s_c)return rule;
					if(range_buf->buffer_name="EXCLUDE" )if( rule->lineno>= range->s_lineno && rule->lineno<=s_c)return NULL;		
				}
				range_buf = range_buf->next ;
			}
}

struct  import_rule * import_rule_reduce(char * file_name ,char * import_name , int lineno,struct filter * filter ){
	if(file_stack_count ==  1 || !strcmp(cur_trans,ALL_TRANS)  || !strcmp(cur_trans ,target_trans) ){
		/*被执行的import_rule添加进import_rule_chain*/
		struct import_rule * cur_import =  join_import_rule(file_name , import_name , lineno,filter );
		char * filename ;	
		/*目标trans*/
		if(import_name)target_trans=import_name;
		if(!import_name)target_trans=ALL_TRANS;
		/*使用的filter*/
		if(filter) curfilter=filter;
		if(!filter) curfilter=NULL;
		/*即将打开的文件*/
		if(file_name)filename = file_name;
		if(!file_name)filename = curfilename;
		/*添加到import_trans栈内*/
		newimport(filename , target_trans , curfilter);
		/*返回执行成功的import_rule*/
		return  cur_import ;
	}else{
		return NULL;
	}
}


