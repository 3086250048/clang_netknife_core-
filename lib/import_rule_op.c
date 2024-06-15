#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>
#include <regex.h>

static struct import_rule * import_rule_root = NULL;


struct range * join_range(struct range * root , char * regx ,int s_lineno ,int d_lineno ,char * s_comment,char * d_comment )
{
	if(ACCEPT || flex_state != GLOBAL_STATE ){
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
		if(ACCEPT || flex_state != GLOBAL_STATE){
		struct filter *  tmp = malloc(sizeof(struct filter));
		tmp->node_type = node_type ;
		tmp->range=range;
		tmp->next = root;
		root = tmp;
		return root;
		}
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


struct  import_rule * join_import_rule(char * file_name ,char * import_name , int lineno,struct filter * filter   ){
	struct import_rule * tmp = malloc(sizeof(struct import_rule));
	tmp->node_type = IMPORT_NODE;
	tmp->index_filename = curfilename;
	tmp->index_trans = cur_trans ;
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
	struct table  * tab  =  Get(comment_tmp_tab, curfilename , c , COMMENT_NODE  );
	if(!tab) return -1 ;
	if(tab->type){
		struct comment * comment = tab->buffer ;
		return comment->lineno ;
	}
	return -1;
}

void include_handle(struct stack * include_stack ,int * result_flag  , int * exist_flag , struct range ** match_range , int lineno ,char * str){
		/*判断rule是否符合include_filter*/
		struct stack * stack =NULL;
		while( stack = Top(&include_stack)){
				*exist_flag = 1;
				struct range * range = stack->buffer;
				int mode = bitmap(range->regx,range->s_lineno,range->d_lineno,range->s_comment ,range->d_comment);
				
				/*regx*/
				if( mode==REGX_ONLY ){
							if(!regx_match(range->regx,str)){ *match_range =range; *result_flag =1;break;}
				}
				/*s_lineno*/
				if(mode == S_LINENO_ONLY ){
							if(lineno ==  range->s_lineno){ *match_range =range; *result_flag=1;break;}
				}
				/*s_comment*/
				if( mode == S_COMMENT_ONLY )
				{
					int lineno = get_comment_lineno(range->s_comment);
					if(lineno== -1){  err("get_comment_lineno","this comment does not exist"); exit(1);}
					if(lineno == lineno) { *match_range =range; *result_flag=1; break;}	
				}	
				/*lineno*/
				if( mode == LINENO_ONLY){
					if(range->s_lineno > range->d_lineno)	swap_number(&range->s_lineno, &range->d_lineno);
					if(lineno >= range->s_lineno && lineno <= range->d_lineno){ *match_range =range; *result_flag=1; break;}
				}
				/*comment*/
				if( mode == COMMENT_ONLY){
					int s_c = get_comment_lineno( range->s_comment);
					int d_c = get_comment_lineno( range->d_comment);
					if(s_c==-1 || d_c==-1){  err("get_comment_lineno","this comment does not exist"); exit(1);}
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(  lineno >= s_c && lineno <= d_c){ *match_range =range; *result_flag=1;break;}
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					
					int s_c = get_comment_lineno( range->s_comment);
					if(s_c==-1){  err("get_comment_lineno","this comment does not exist");exit(1); }
					int s_lineno = range->s_lineno ;
					if( s_lineno > s_c) swap_number(&s_lineno,&s_c);
					if(  lineno >= s_lineno && lineno <=s_c){ *match_range =range; *result_flag=1; break;}
				}
				Pop(&include_stack);
			}
}

void  exclude_handle(struct stack * exclude_stack ,int * result_flag  , int * exist_flag , struct range ** match_range , int lineno , char * str){
			struct stack * stack ;
			while( stack = Top(&exclude_stack)){
				*exist_flag = 1;
				struct range * range = stack->buffer;
				int mode = bitmap(range->regx,range->s_lineno,range->d_lineno,range->s_comment ,range->d_comment);
				
				/*regx*/
				if( mode==REGX_ONLY ){
							if(!regx_match(range->regx,str)){ *match_range = range; *result_flag =1; break;}
				}
				/*s_lineno*/
				if(mode == S_LINENO_ONLY ){
							if(lineno ==  range->s_lineno){ *match_range = range; *result_flag=1; break;}
				}
				/*s_comment*/
				if( mode == S_COMMENT_ONLY )
				{
					int lineno = get_comment_lineno(range->s_comment);
					if(lineno== -1){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(lineno == lineno) { *match_range = range; *result_flag=1; break;}	
				}	
				/*lineno*/
				if( mode == LINENO_ONLY){
					if(range->s_lineno > range->d_lineno)	swap_number(&range->s_lineno, &range->d_lineno);
					if(lineno >= range->s_lineno && lineno <= range->d_lineno){ *match_range = range; *result_flag=1; break;}
				}
				/*comment*/
				if( mode == COMMENT_ONLY){
					int s_c = get_comment_lineno( range->s_comment);
					int d_c = get_comment_lineno( range->d_comment);
					if(s_c==-1 || d_c==-1){  err("get_comment_lineno","this comment does not exist");exit(1); }
					if(s_c > d_c) swap_number(&s_c,&d_c);
					if(  lineno >= s_c && lineno <= d_c){ *match_range = range; *result_flag=1; break;}
				}	
				/*lineno and comment */
				if( mode == LINENO_AND_COMMENT ){
					
					int s_c = get_comment_lineno( range->s_comment);
					if(s_c==-1){  err("get_comment_lineno","this comment does not exist");exit(1); }
					int s_lineno = range->s_lineno ;
					if( s_lineno > s_c) swap_number(&s_lineno,&s_c);
					if(  lineno >= s_lineno && lineno <=s_c){ *match_range = range; *result_flag=1; break ;}
				}
				Pop(&exclude_stack);
			}
}
/*将buffer中的数据根据filter过滤*/
struct rule *  filter_rule(struct stack * include_stack , struct stack * exclude_stack  , struct rule * rule){
		int include_match_result = 0;	
		int exist_include_filter =0;
		struct range * inc_match_range = NULL;
		include_handle( include_stack , &include_match_result,&exist_include_filter ,&inc_match_range , rule->lineno , rule->s);
		/*判断rule是否符合exclude_filter*/
		int exclude_match_result = 0;	
		int exist_exclude_filter = 0;
		struct range * exc_match_range = NULL;
		exclude_handle( exclude_stack , &exclude_match_result,&exist_exclude_filter ,&exc_match_range , rule->lineno, rule->s );
	
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
			if(!include_match_result && !exclude_match_result) return rule;
			if(include_match_result && exclude_match_result ){
				err("filter","filter rule conflict");
				err_node(inc_match_range,"INCLUDE");
				err_node(exc_match_range,"EXCLUDE");
				exit(1);
			}
		}
}

struct import_info * filter_import(struct stack * include_stack , struct stack * exclude_stack , struct import_info * import_info , char * cmp_pre_file){
		int include_match_result = 0;	
		int exist_include_filter =0;
		struct range * inc_match_range = NULL;
		char * import_raw = strdup("@");	
		if(strcmp(import_info->file_name , cmp_pre_file)!=0){ 
			append_string(&import_raw , import_info->file_name);
		} 
	 	append_string(&import_raw , import_info->import_name);
		include_handle( include_stack , &include_match_result,&exist_include_filter ,&inc_match_range , import_info->lineno , import_raw);
		/*判断rule是否符合exclude_filter*/
		int exclude_match_result = 0;	
		int exist_exclude_filter = 0;
		struct range * exc_match_range = NULL;
		exclude_handle( exclude_stack , &exclude_match_result,&exist_exclude_filter ,&exc_match_range , import_info->lineno, import_raw );
	
		/*filter 结果判断*/
		if( exist_include_filter && !exist_exclude_filter){
			if(include_match_result) return import_info;
			return NULL;
		}
		if(!exist_include_filter && exist_exclude_filter){
			if(!exclude_match_result) return import_info ;
			return NULL;
		}
		if(exist_include_filter && exist_exclude_filter){	
			if(include_match_result && !exclude_match_result  )return import_info ;
			if(!include_match_result && exclude_match_result)return NULL;
			if(!include_match_result && !exclude_match_result) return import_info ;
			if(include_match_result && exclude_match_result ){
				err("filter","filter rule conflict");
				err_node(inc_match_range,"INCLUDE");
				err_node(exc_match_range,"EXCLUDE");
				exit(1);
			}
		}
}

#define INIT_FILTER_PARAM \
	struct stack  * include_stack=NULL;\
	struct stack  * exclude_stack=NULL;
#define EXTRACT_FILTER\
	while(tmp_filter){\
		struct range * range = tmp_filter->range;\
		while(range){\
			has_range =1;\
			if(tmp_filter->node_type == INCLUDE_NODE ) Push(&include_stack,"RANGE","INCLUDE",RANGE_NODE,range);\
			if(tmp_filter->node_type == EXCLUDE_NODE) Push(&exclude_stack,"RANGE","EXCLUDE",RANGE_NODE,range);\
			range=range->next;\
		}\
		tmp_filter = tmp_filter->next;\
	}\



void *  Filter(void * buffer){
	if(!import_rule_root ) return buffer ;
	int has_range =0;
	struct import_rule * root = import_rule_root ;
	
	char * pre_file = curfilename ;
	char * pre_trans = cur_trans ;

	/*合并filter中的range*/
	INIT_FILTER_PARAM;
	/*给filter_import使用的参数*/
	char *  cmp_pre_file = NULL;
   		
		
	while(root){	
		if( (!strcmp(pre_trans,root->import_name ) && !strcmp(pre_file , root->file_name )) ||\
			(!strcmp(ALL_TRANS,root->import_name) && !strcmp(pre_file,root->file_name)) ) {
					if(*(int *)buffer == IMPORT_NODE){ cmp_pre_file = pre_file; }
					pre_file = root->index_filename;
					pre_trans = root->index_trans ;
					struct filter * tmp_filter = root->filter  ;	
					EXTRACT_FILTER;
					if(*(int*)buffer  == IMPORT_NODE  ) break ; 
			}
			root=root->next ;
		}

		if(!has_range){
			return buffer ;
		} 

		if( *((int *)buffer) == IMPORT_NODE ){
				return  filter_import(include_stack, exclude_stack ,buffer , cmp_pre_file );	
		}

		if( *((int*)buffer) == RULE_NODE ){
				return   filter_rule(include_stack , exclude_stack ,buffer);	
		}

} 


struct import_info * join_import_info(char * file_name , char * import_name , int  lineno , struct filter * filter ){
	struct import_info  *  tmp = malloc(sizeof(struct import_info));
	tmp->node_type = IMPORT_NODE;
	tmp->in_file_stack_count = file_stack_count; 
	tmp->in_file_name = curfilename;
	tmp->file_name = file_name;
   	tmp->import_name = import_name ; 
	tmp->lineno = lineno ;
	tmp->filter = filter ;	
	return tmp ;
}

struct filter_entry * join_filter_entry(char * file_name , char * trans_name , char * target_file ,char * target_trans , struct filter * filter  ){
	struct filter_entry * tmp = malloc(sizeof(struct filter_entry))	;
	tmp->file_name = file_name ; 
	tmp->trans_name = trans_name ; 
	tmp->target_file = target_file ;
	tmp->target_trans = target_trans ; 
	if(!filter){
		filter = malloc(sizeof(struct filter ));
		filter->node_type = SKIP_NODE;
		filter->range = NULL;
		filter->next = NULL;
	}
	tmp->filter = filter ;
	return tmp ;
}



void record_import(char * filename,struct import_info * import_info,char * action ){
	if(import_info)return;
 	char  * outfile  = filename  ; 
 	if(strlen(filename) == 0 ){ err("OUTSTEP状态","OUTSTEP的宏定义错误") ; exit(1);}
 	FILE * f = fopen(filename,"a");
	fprintf(f,"%s>>>\n",action);
	fprintf(f,"Object| import_stack\n");
 	fprintf(f,"  Info| file:%s trans:%s level:%d\n",curfilename ,cur_trans,file_stack_count);
 	fprintf(f,"Import| lineno:%d target_file:%s target_trans:%s\n",import_info->file_name,import_info->import_name);
	struct filter * filter  = import_info->filter ;
	while(filter){
		if(filter->node_type == INCLUDE_NODE){
		fprintf(f,"Filter| type:include \n");
		}else{
		fprintf(f,"Filter| type:exclude \n");
		}	
		struct range * range = filter->range ;
		while(range){
		fprintf(f," Range| regx:%s s_lineno:%d d_lineno:%s s_comment:%s d_comment:%s\n",range->regx,range->s_lineno , range->d_lineno , range->s_comment , range->d_comment);
		range=range->next;
		}
		filter=filter->next;
	}
	
 	fprintf(f,"<<<\n\n");
	fclose(f);
}

void record_filter(char * filename,struct filter  * filter ,char * action ){
	if(!filter)return ;
 	char  * outfile  = filename  ; 
 	if(strlen(filename) == 0 ){ err("OUTSTEP状态","OUTSTEP的宏定义错误") ; exit(1);}
 	FILE * f = fopen(filename,"a");
	fprintf(f,"%s>>>\n",action);
	fprintf(f,"Object|  PreLevelFilterStack\n");
 	fprintf(f,"  Info| file:%s trans:%s level:%d\n",curfilename ,cur_trans,file_stack_count);
	while(filter){
		if(filter->node_type == INCLUDE_NODE){
		fprintf(f,"Filter| type:include \n");
		}else if(filter->node_type == EXCLUDE_NODE){
		fprintf(f,"Filter| type:exclude \n");
		}else{
		fprintf(f,"Filter| type:skip \n");
		}
		struct range * range = filter->range ;
		while(range){
		fprintf(f,"Range | regx:%s s_lineno:%d d_lineno:%s s_comment:%s d_comment:%s\n",range->regx,range->s_lineno , range->d_lineno , range->s_comment , range->d_comment);
		range=range->next;
		}
		filter=filter->next;
	}
	
 	fprintf(f,"<<<\n\n");
	fclose(f);
}

#define INIT_IMPORT_PARAM\
 char * filename ,* target_trans;\
		if(!file_name){\
				filename = curfilename ;\
		}else{\
				filename = file_name;\
		}\
		if(!import_name){\
				target_trans = ALL_TRANS;\
		}else{\
			target_trans = import_name;\
		}
/*
 * INIT_FILTER :
 * 			include_stack  
 * 			exclude_stack 
 *
 */


struct  import_rule * import_rule_reduce(char * file_name ,char * import_name , int lineno,struct filter * filter  ){

	if(flex_state != GLOBAL_STATE  ){
			int has_range = 0 ;
			INIT_IMPORT_PARAM;

			flex_state = GLOBAL_STATE;
			cur_use_trans = get_netknife_node(filename, TRANS_NODE , target_trans);		
	/*全局@时根据filter过滤取得最终要使用的rule_tab*/
	for(int i=0;i<MAX_HASH;i++){
		struct filter * tmp_filter = filter;
		INIT_FILTER_PARAM;
		EXTRACT_FILTER;
		struct rule * r = (cur_use_trans->rule_tab)[i].r;
		if(r){
			if(!has_range){
				join_tmp_rule_table(r);
			}else{
				if( filter_rule(include_stack , exclude_stack ,r) )join_tmp_rule_table(r);
			}
		}
	}

	after_filter_trans = malloc(sizeof(struct trans) );
	memcpy(after_filter_trans , cur_use_trans , sizeof(struct trans));
	after_filter_trans->rule_tab = get_tmp_rule_table();
	print_trans(after_filter_trans);

	}else {	
			if(ACCEPT){	
				INIT_IMPORT_PARAM;
				struct import_info * import_info = join_import_info(filename , target_trans , lineno , filter);
				Push(&import_stack , curfilename , cur_trans , IMPORT_NODE , import_info );
				#ifdef OUTSTEP
				#ifdef OUTFILE 
					record_import(OUTFILE,import_info,"Push");
				#endif
					record_import(STEPOUT,import_info,"Push");
				#endif		
			}	
	}
}


