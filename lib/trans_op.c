#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>



struct trans * join_trans(char *  name ,int lineno , struct rule_table * rule_tab  ,struct import_rule * import_rule_chain ){
	
	struct trans  * tmp = malloc(sizeof(struct trans));
		tmp->node_type = TRANS_NODE;
		tmp->name = name ;
		tmp->lineno=lineno;
		tmp->rule_tab = rule_tab ;
		tmp->comment_tab = NULL;
		tmp->import_rule_chain = import_rule_chain;
		return tmp;
}

//打印trans_table表项
void print_trans(struct trans * trans){
	printf("%*snode_type:TRANS_NODE\n",PRINT_TRANS_TABLE_ENTRY);
	printf("%*strans_name:%s\n",PRINT_TRANS_TABLE_ENTRY,trans->name);
	printf("%*slineno:%d\n",PRINT_TRANS_TABLE_ENTRY,trans->lineno);
	int i;
	if(trans->rule_tab)
	for(i=0;i<MAX_HASH;i++){
		if((trans->rule_tab)[i].r){
			print_rule_table_entry(&(trans->rule_tab)[i]);
		}
	}
/*	if(trans->comment_tab)
	for(i=0;i<MAX_HASH;i++){
		if((trans->comment_tab[i].c)){
			print_comment_table_entry(&(trans->comment_tab)[i]);
		}
	}*/
	if(trans->import_rule_chain)
	print_import_rule(trans->import_rule_chain);
}

int transcmp(char * t1 , char * t2){
	if(!t1 || !t2 )return 0;
	if(strcmp(t1,t2) == 0) return 1;
	return 0;
}


void excute_import(){
	/*import_stack栈内不为空时*/
	struct import_info * import_info = Top(&import_stack)->buffer;
	struct import_info * pre_import_info = NULL ;
	if( Top(&import_stack)->next){
		 pre_import_info =  Top(&import_stack)->next->buffer ;
	}


	#ifdef OUTSTEP
	#ifdef OUTFILE 
	record_import(OUTFILE,import_info,"Top");
	#endif
	record_import(STEPOUT,import_info,"Top");
	#endif		

	import_info = Filter(import_info);
	if(import_info){
		/*import_info 语句满足上一个import语句的过滤条件*/
		join_import_rule(import_info->file_name,import_info->import_name , import_info->lineno , import_info->filter);
		#ifdef OUTSTEP
		#ifdef OUTFILE 
		record_import(OUTFILE,import_info,"Join");
		#endif
		record_import(STEPOUT,import_info,"Join");
		#endif		
		struct filter * plfilter = NULL; 
		if(Top(&PreLevelFilterStack)){
		   plfilter = Top(&PreLevelFilterStack)->buffer; 
			#ifdef OUTSTEP
			#ifdef OUTFILE 
			record_filter(OUTFILE,plfilter,"Top");
			#endif
			record_filter(STEPOUT,plfilter,"Top");
			#endif	
		}
		
		struct filter * filter = import_info->filter ;
		struct filter * filter_dup=NULL ;
		/*复制链表*/
		while(filter){
			struct range * range = filter->range;
			struct range * range_dup=NULL ;
			while(range){
				range_dup = join_range(range_dup , range->regx,range->s_lineno,range->d_lineno,range->s_comment,range->d_comment);	
				range=range->next;
			}	
			filter_dup=join_filter(filter_dup,filter->node_type , range_dup	);
			filter=filter->next;
		}
		
		struct filter * filter_dd = filter_dup;

		if(filter_dd){
			/*如果import存在filter*/
			while(filter_dd->next){
				filter_dd=filter_dd->next;
			}	
			filter_dd->next = plfilter ;
		}


		int import_offset = 0;
		if(pre_import_info){
			import_offset = import_info->in_file_stack_count -  pre_import_info->in_file_stack_count;
		}else{
			import_offset = 1;  
		}
		if( import_offset > 0 ){	
			if(filter_dup){
				/*如果经过PreLevelFilterStack叠加后的filter不为空*/
				Push(&PreLevelFilterStack,curfilename,cur_trans,filter_dup->node_type ,filter_dup);	
				#ifdef OUTSTEP
				#ifdef OUTFILE 
				record_filter(OUTFILE,filter_dup,"Push");
				#endif
				record_filter(STEPOUT,filter_dup,"Push");
				#endif	
			}else{
				filter_dup = malloc(sizeof(struct filter *));
				filter_dup->node_type = SKIP_NODE;
				filter_dup->range = NULL;
				filter_dup->next = NULL;
				Push(&PreLevelFilterStack,curfilename,cur_trans,filter_dup->node_type ,filter_dup);	
				#ifdef OUTSTEP
				#ifdef OUTFILE 
				record_filter(OUTFILE,filter_dup,"Push");
				#endif
				record_filter(STEPOUT,filter_dup,"Push");
				#endif	   
			}
		}

		curfilter = filter_dup ;		
		target_trans = import_info->import_name ;
		if(file_stack_count ==1 ){ start_trans = cur_trans; }
		if( newfile(import_info->file_name) ){
			Pop(&import_stack);
			Pop(&PreLevelFilterStack);
			yyparse();	
		}
	}
}


int accept_state(int file_stack_count  ,  char * cur_trans , char * target_trans  ){
	
	if(file_stack_count == 1) return 1;
	if(transcmp(cur_trans,target_trans) && start_trans ) return 1;
	if(transcmp(target_trans,ALL_TRANS) && start_trans ) return 1;
}

int alltrans_state(char * target_trans ){
	if(transcmp(target_trans,ALL_TRANS)) return 1;
}

int sptrans_state(char * cur_trans , char * target_trans ){
	if(transcmp(cur_trans,target_trans) ) return 1;
}


int import_state(){
	if(Top(&import_stack)){ return 1; }
}

struct trans *  trans_reduce()
{

	if(ACCEPT){

		while(Top(&rule_stack)){
				struct rule * rule = Top(&rule_stack)->buffer;	
				rule = Filter(rule);
				if(rule) join_rule_table(rule);
				Pop(&rule_stack);
			}

		if(IMPORT_STATE ){	

			if(AL_TRANS) return NULL;

			
			struct import_info * import_info = Top(&import_stack)->buffer;
			import_info = Filter(import_info);
			if(import_info){					
				SET_START_FILE;	
				SET_START_TRANS;
				SET_TARGET_TRANS;
			
				join_import_rule(import_info->file_name,import_info->import_name , import_info->lineno , import_info->filter);
				if(newfile(import_info->file_name)){	
					Pop(&import_stack);
					yyparse();
				}
			}else{
				struct trans * t  = join_trans(start_trans , yylineno , get_rule_table(), get_import_rule()); 
				RESET_START_TRANS;
				RESET_TARGET_TRANS;
				print_trans(t);
				return t;
			}
		}else{
			
			if(file_stack_count == 1){
				struct trans * t = join_trans(cur_trans , yylineno , get_rule_table(), get_import_rule()); 
				print_trans(t);	
				return t;
			}

			if(AP_TRANS  ){

				struct trans * t = join_trans(start_trans , yylineno , get_rule_table(), get_import_rule()); 
				RESET_START_TRANS;
				print_trans(t);
				return t;
			}
			
		}
	}
}

