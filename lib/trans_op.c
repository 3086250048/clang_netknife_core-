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

		if(filter_dup){
			/*如果import存在filter*/
			while(filter_dup->next){
				filter_dup=filter_dup->next;
			}	
			filter_dup->next = plfilter ;
		}

		
		if(filter_dup){
			/*如果经过PreLevelFilterStack叠加后的filter不为空*/
			Push(&PreLevelFilterStack,curfilename,cur_trans,filter_dup->node_type ,filter_dup);	
			#ifdef OUTSTEP
			#ifdef OUTFILE 
			record_filter(OUTFILE,filter_dup,"Push");
			#endif
			record_filter(STEPOUT,filter_dup,"Push");
			#endif	
		}

		curfilter = filter_dup ;		
		target_trans = import_info->import_name ;
		if(file_stack_count ==1 ){ start_trans = cur_trans; }
		if( newfile(import_info->file_name) ){

			Pop(&import_stack);
			yyparse();	
		}
	}
}

struct trans *  trans_reduce()
{
	if(ACCEPT){
		while(Top(&rule_stack)){
			struct rule * rule = Top(&rule_stack)->buffer;	
			#ifdef OUTSTEP
			#ifdef OUTFILE 
			record_rule(OUTFILE,rule,"Top");
			#endif
			record_rule(STEPOUT,rule,"Top");
			#endif		
			rule = Filter(rule);
			if(rule){
				join_rule_table(rule);
			#ifdef OUTSTEP
			#ifdef OUTFILE 
			record_rule(OUTFILE,rule,"Join");
			#endif
			record_rule(STEPOUT,rule,"Join");
			#endif	
			}	
			Pop(&rule_stack);
			#ifdef OUTSTEP
			#ifdef OUTFILE 
			record_rule(OUTFILE,rule,"Pop");
			#endif
			record_rule(STEPOUT,rule,"Pop");
			#endif	
		}
		

		if(Top(&import_stack) && !transcmp(target_trans , ALL_TRANS )){	
			excute_import();
		}else{
			/*import_stack栈内为空时*/
			if(start_trans ){
				/*trans中包含import语句*/
				if(!transcmp(target_trans,ALL_TRANS) ) {
				/*目标trans不为ALL_TRANS*/
					 struct trans * t =join_trans(start_trans,yylineno,get_rule_table(),get_import_rule());	
					start_trans=NULL;
					 print_trans(t);
					 return NULL;
				}
			}else{
				/*trans中不包含import语句*/
				 struct trans *  t= join_trans(cur_trans,yylineno , get_rule_table(),get_import_rule());	
				 print_trans(t);
				 return NULL;
			}		
		}
	}	
	return NULL;
}










