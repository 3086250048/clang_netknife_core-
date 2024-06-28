#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

unsigned long netknife_index_hash(const char * filename ,  int child_type , const char * child_name) {
    unsigned long combined_hash = hash_string(filename);
    combined_hash = combine_hashes(combined_hash, hash_string(child_name));
    combined_hash = combine_hashes(combined_hash, child_type);
    return combined_hash;
}

struct netknife * join_netknife_table( char * filename ,  void * node){
		char * child_name;
		int  child_type ;
	
		if(*((int *)node) ==TRANS_NODE){
		    child_name = ((struct trans *)node)->name;
			child_type = TRANS_NODE; 	
		}
		unsigned int hash = netknife_index_hash(filename,child_type,child_name)%MAX_HASH;
		struct netknife *  tmp = &netknife_tab[hash];

		/*全局@特殊设置*/
		if(!strcmp(child_name,"cmd") && child_type == TRANS_NODE && !strcmp(filename,"cmd") ){
			tmp->node_type = NETKNIFE_NODE;
			tmp->filename = filename ;
			tmp->child_type = child_type;
		   	tmp->child_name = child_name ;
			tmp->child_tab = node ;	
			return tmp ;

		}

		if(tmp->node_type != NETKNIFE_NODE ){
			tmp->node_type = NETKNIFE_NODE;
			tmp->filename = filename ;
			tmp->child_type = child_type;
		   	tmp->child_name = child_name ;
			tmp->child_tab = node ;	
			return tmp ;
		}else{
			err("join_netknife_table","join netknife_table hash conflict");
		}
}


void  * get_netknife_node(char * filename , int child_type , char * child_name){
		struct netknife * tmp = &netknife_tab[netknife_index_hash(filename,child_type,child_name)%MAX_HASH];	
		if(tmp->node_type == NETKNIFE_NODE){
				return tmp->child_tab;
		}else{
			return NULL;
		//	err("get_netknife_node","netknife_table no has this entry");
		}	
}


struct netknife * netknife_reduce( void  * node){
		if(!node)return NULL ;
		if(start_file){
			struct netknife * n =  join_netknife_table(start_file ,(struct trans *)node);
			RESET_START_FILE ;
			/*
			 * 作用:if中的代码只有在cmd模式下,直接@trans时会生效(不在其他trans中引用) 
			 * 原因:import_rule_reduce 中 yyparse函数执行完成后无法继续执行后续的代码 
			 */
			if(sp_yyparse){
					sp_yyparse  = 0 ;
					int has_range = 0;
					cur_use_trans = get_netknife_node(sp_yyparse_filename, TRANS_NODE , sp_yyparse_target_trans);			
					/*全局@时根据filter过滤取得最终要使用的rule_tab*/
					for(int i=0;i<MAX_HASH;i++){
						struct filter * tmp_filter = sp_yyparse_filter;
						INIT_FILTER_PARAM;
						EXTRACT_FILTER;
						struct rule * r = (cur_use_trans->rule_tab)[i].r;
						struct rule_table *  tmp =  &(cur_use_trans->rule_tab)[i];
						if(r){
							if(!has_range){
								while(tmp){ 
									join_tmp_rule_table(tmp->r);
									tmp=tmp->dup_r;
								}
							}else{
								if( filter_rule(include_stack , exclude_stack ,r,sp_yyparse_target_trans) ){
										while(tmp){
											join_tmp_rule_table(r);
											tmp=tmp->dup_r;
										}
								}
							}
						}
					}

					after_filter_trans = malloc(sizeof(struct trans) );
					memcpy(after_filter_trans , cur_use_trans , sizeof(struct trans));
					after_filter_trans->rule_tab = get_tmp_rule_table();
					print_trans(after_filter_trans);
			}
			return n;
		}else{
			struct netknife * n =  join_netknife_table(curfilename ,(struct trans *)node);
			return n;
		}
}  


