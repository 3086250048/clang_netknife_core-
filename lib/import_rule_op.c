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

void stderr_print_range(struct range * range_root){
	struct range * tmp  = range_root;
	while(tmp){
 		fprintf(stderr,"%*snode_type:RANGE_NODE\n",PRINT_RANGE);
		fprintf(stderr,"%*sregx:%s\n",PRINT_RANGE,tmp->regx);
		fprintf(stderr,"%*ss_lineno:%d\n",PRINT_RANGE,tmp->s_lineno);
		fprintf(stderr,"%*sd_lineno:%d\n",PRINT_RANGE,tmp->d_lineno);
		fprintf(stderr,"%*ss_comment:%s\n",PRINT_RANGE,tmp->s_comment);
		fprintf(stderr,"%*sd_comment:%s\n",PRINT_RANGE, tmp->d_comment);
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
    regex_t regex ;
	int m=1 ;
    int reti;
    char msgbuf[100];
    reti = regcomp(&regex, regx,0);
    if (reti) {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		msgbuf[sizeof(msgbuf) - 1] = '\0';
		err("regular compilation",msgbuf);
        exit(1);
    }
    /* 匹配字符串*/
    reti = regexec(&regex, str, 0, NULL,0);
    if (!reti) {
		m=0;
    } else if (reti == REG_NOMATCH) {
		m=1;
    } else {
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		msgbuf[sizeof(msgbuf) - 1] = '\0';
		err("regular match",msgbuf);
        exit(1);
    }
	regfree(&regex);
	return m;
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


int get_comment_lineno(char * c){
	struct comment_table  * tmp =&comment_tab[hash_string(c)%MAX_HASH];

	if(tmp->c){
		return tmp->c->lineno;
	}else{
	/*当c_buf中不存在传入的comment则return -1*/
	return -1;
	}
}




/*将buffer中的数据根据filter过滤*/
struct rule *  filter_rule(struct rule * rule){
		/*如果不存在filter则直接退出*/
		if(!curfilter )return rule; 
		struct filter* filter = curfilter;		
		/*合并filter中的range*/
		struct buffer *  include_range_buf=NULL ;
		struct buffer * exclude_range_buf = NULL;
		while(filter){	
			struct range * range = filter->range;
			while(range){
				if(filter->node_type == INCLUDE_NODE )
						include_range_buf = assign_join_buffer_chain(include_range_buf,"RANGE","INCLUDE",RANGE_NODE,range); 
				if(filter->node_type == EXCLUDE_NODE) 
						exclude_range_buf = assign_join_buffer_chain(exclude_range_buf,"RANGE","EXCLUDE",RANGE_NODE,range); 
				range=range->next;
			}
			filter = filter->next;
		}

		int include_match_result = 0;	
		int exist_include_filter =0;
		struct range * inc_match_range = NULL;
		/*判断rule是否符合include_filter*/
		while(include_range_buf){
				exist_include_filter = 1;
				struct range * range = include_range_buf->buffer;
				int mode = bitmap(range->regx,range->s_lineno,range->d_lineno,range->s_comment ,range->d_comment);
				
				/*regx*/
				if( mode==REGX_ONLY ){
							if(!regx_match(range->regx,rule->s)){ inc_match_range =range; include_match_result =1;break;}
				}
				/*s_lineno*/
				if(mode == S_LINENO_ONLY ){
							if(rule->lineno ==  range->s_lineno){ inc_match_range =range; include_match_result=1;break;}
				}
				/*s_comment*/
				if( mode == S_COMMENT_ONLY )
				{
					int lineno = get_comment_lineno(range->s_comment);
					if(lineno== -1){  err("get_comment_lineno","this comment does not exist"); exit(1);}
					if(rule->lineno == lineno) { inc_match_range =range; include_match_result=1; break;}	
				}	
				/*lineno*/
				if( mode == LINENO_ONLY){
					if(range->s_lineno > range->d_lineno)	swap_number(&range->s_lineno, &range->d_lineno);
					if(rule->lineno >= range->s_lineno && rule->lineno <= range->d_lineno){ inc_match_range =range; include_match_result=1; break;}
				}
				/*comment*/
				if( mode == COMMENT_ONLY){
					int s_c = get_comment_lineno( range->s_comment);
					int d_c = get_comment_lineno( range->d_comment);
					if(!s_c || !d_c){  err("get_comment_lineno","this comment does not exist"); exit(1);}
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(  rule->lineno >= s_c && rule->lineno <= d_c){ inc_match_range =range; include_match_result=1;break;}
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					
					int s_c = get_comment_lineno( range->s_comment);
					if(!s_c){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(range->s_lineno > s_c) swap_number(&range->s_lineno,&s_c);
					if(  rule->lineno >= range->s_lineno && rule->lineno <=s_c){ inc_match_range =range; include_match_result=1; break;}
				}
				include_range_buf = include_range_buf->next ;
			}

			/*判断rule是否符合exclude_filter*/
			int exclude_match_result = 0;	
			int exist_exclude_filter = 0;
			struct range * exc_match_range = NULL;
			while(exclude_range_buf){
				exist_exclude_filter = 1;
				struct range * range = exclude_range_buf->buffer;
				int mode = bitmap(range->regx,range->s_lineno,range->d_lineno,range->s_comment ,range->d_comment);
				
				/*regx*/
				if( mode==REGX_ONLY ){
							if(!regx_match(range->regx,rule->s)){ exc_match_range = range; exclude_match_result =1; break;}
				}
				/*s_lineno*/
				if(mode == S_LINENO_ONLY ){
							if(rule->lineno ==  range->s_lineno){ exc_match_range = range; exclude_match_result=1; break;}
				}
				/*s_comment*/
				if( mode == S_COMMENT_ONLY )
				{
					int lineno = get_comment_lineno(range->s_comment);
					if(lineno== -1){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(rule->lineno == lineno) { exc_match_range = range; exclude_match_result=1; break;}	
				}	
				/*lineno*/
				if( mode == LINENO_ONLY){
					if(range->s_lineno > range->d_lineno)	swap_number(&range->s_lineno, &range->d_lineno);
					if(rule->lineno >= range->s_lineno && rule->lineno <= range->d_lineno){ exc_match_range = range; exclude_match_result=1; break;}
				}
				/*comment*/
				if( mode == COMMENT_ONLY){
					int s_c = get_comment_lineno( range->s_comment);
					int d_c = get_comment_lineno( range->d_comment);
					if(!s_c || !d_c){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(  rule->lineno >= s_c && rule->lineno <= d_c){ exc_match_range = range; exclude_match_result=1; break;}
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					
					int s_c = get_comment_lineno( range->s_comment);
					if(!s_c){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(range->s_lineno > s_c) swap_number(&range->s_lineno,&s_c);
					if(  rule->lineno >= range->s_lineno && rule->lineno <=s_c){ exc_match_range = range; exclude_match_result=1; break ;}
				}
				exclude_range_buf = exclude_range_buf->next ;
			}
			/*filter 结果判断*/
			if( exist_include_filter && !exist_exclude_filter){
				if(include_match_result) return rule ;
				return NULL;
			}
			if(!exist_include_filter && exist_exclude_filter){
				if(!exclude_match_result) return rule ;
				return NULL;
			}
			if(exist_include_filter && exist_exclude_filter){	
				if(include_match_result && !exclude_match_result  )return rule;
				if(!include_match_result && exclude_match_result)return NULL;
				if(!include_match_result && !exclude_match_result) return rule ;
				if(include_match_result && exclude_match_result ){
		 		    err("rule_filter","filter rule conflict");
					err_node(inc_match_range,"INCLUDE");
					err_node(exc_match_range,"EXCLUDE");
					exit(1);
				}
			}
		
}


struct  import_rule * import_rule_reduce(char * file_name ,char * import_name , int lineno,struct filter * filter ){
	if(file_stack_count>1 && !import_state  && !transcmp(target_trans , ALL_TRANS)  ) return  NULL;
	if(file_stack_count ==  1 || transcmp(target_trans,ALL_TRANS)  || transcmp(cur_trans ,target_trans) ){
		/*被执行的import_rule添加进import_rule_chain*/
		/*目标trans*/
		char * filename ;	
		char * target_trans;
		if(import_name)target_trans=import_name;
		if(!import_name)target_trans=ALL_TRANS;
		/*使用的filter*/
		if(filter) curfilter=filter;
		if(!filter) curfilter=NULL;
		/*即将打开的文件*/
		if(file_name)filename = file_name;
		if(!file_name)filename = curfilename;
		struct import_rule * cur_import =  join_import_rule(filename  , target_trans , lineno,filter );
		/*添加到import_trans栈内*/
		newimport(filename , target_trans , curfilter);
		/*返回执行成功的import_rule*/
		return  cur_import ;
	}else{
		return NULL;
	}
}


