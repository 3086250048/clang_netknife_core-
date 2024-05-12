#include <stdlib.h>
#include <string.h>
#include "netknife.h"
#include <stdio.h>

unsigned long index_string_hash(const char * index_string){
	return hash_string(index_string);
}

//添加rule到表中
struct rule_table * join_rule_table(struct rule * r){
	struct rule_table  * tmp = &rule_tab[index_string_hash(r->s)%MAX_HASH];
	    if(tmp->r != NULL){
			struct rule_table * tail = tmp;
			struct rule_table * dup = malloc(sizeof(struct rule_table));
			dup->node_type = RULE_TABLE_ENTRY_NODE;
			dup->r = r ;
			dup->dup_r  = NULL;
			
			while(tail->dup_r){
				tail=tail->dup_r;
			}
			tail->dup_r = dup; 
			
			return tmp;
		}
		if(tmp->r == NULL){
			tmp->node_type = RULE_TABLE_ENTRY_NODE;
			tmp->r = r;
		   	tmp->dup_r = NULL;
			return tmp;	
		}
}

//添加comment 到表中
struct comment_table * join_comment_table(struct comment * c){
	struct comment_table  * tmp =&comment_tab[index_string_hash(c->c)%MAX_HASH];
			if(tmp->c !=NULL ){
				struct comment_table * tail  = tmp ;
				struct comment_table * dup = malloc(sizeof(struct comment_table));
				dup->node_type = COMMENT_TABLE_ENTRY_NODE;
				dup->c = c ;
				dup->dup_c = NULL ;
				while(tail->dup_c){
					tail=tail->dup_c;
				}
				tail->dup_c = dup ;
				return tmp;
			}
			if(tmp->c == NULL){
				tmp->node_type =COMMENT_TABLE_ENTRY_NODE;
				tmp->c = c;
				tmp->dup_c = NULL;
				return tmp;	
			}

}

//获取rule_table_entry
struct rule_table *  get_rule_table_entry(struct rule_table * rule_tab,char * s){	
	struct rule_table  * tmp =&rule_tab[index_string_hash(s)%MAX_HASH];
	if(!tmp->r) return NULL;
	return tmp;
}


//获取comment_table_entry
struct comment_table * get_comment_table_entry(struct comment_table * comment_tab ,char * c){
	
	struct comment_table  * tmp =&comment_tab[index_string_hash(c)%MAX_HASH];
	if(!tmp->c) return NULL;
	return tmp;
}
//获取rule_table地址,重新分配空间给rule_tab
struct rule_table *  get_rule_table(){
	 struct rule_table * tmp = rule_tab;
	 rule_tab = calloc(MAX_HASH,sizeof(struct rule_table) );
	 return tmp ; 
}

//获取comment_table地址,重新分配空间给comment_tab
struct comment_table * get_comment_table(){
	struct comment_table * tmp = comment_tab;
	comment_tab = calloc(MAX_HASH, sizeof(struct comment_table));
	return tmp;
}

//打印rule_table表项
void  print_rule_table_entry(struct rule_table * rule_tab){
	printf("%*snode_type:RULE_TABLE_ENTRY_NODE\n",PRINT_RULE_TABLE_ENTRY);
	while(rule_tab)	{
		print_rule(rule_tab->r);
		rule_tab=rule_tab->dup_r;
	}	
}


//打印comment表项
void print_comment_table_entry(struct comment_table * comment_tab){
	printf("%*snode_type:COMMENT_TABLE_ENTRY\n",PRINT_COMMENT_TABLE_ENTRY);
	while(comment_tab)	{
		print_comment(comment_tab->c);
		comment_tab=comment_tab->dup_c;
	}	
}

void record_rule(char * filename,struct rule * rule){
 	char  * outfile  = filename  ; 
 	if(strlen(filename) == 0 ){ err("OUTSTEP状态","OUTSTEP的宏定义错误") ; exit(1);}
 	FILE * f = fopen(filename,"w");
	fprintf(f,"Push>>>\n");
 	fprintf(f,"Info| file:%s trans:%s level:%d\n",curfilename ,cur_trans,file_stack_count);
 	fprintf(f,"Rule| lineno:%d priority:%d s:%s d:%s\n",rule->lineno,rule->priority,rule->s , rule->d);
 	fprintf(f,"<<<\n");
	fclose(f);
}

struct rule_table * rule_table_reduce( char * s ,char * d ,int priority ){
	 if(ACCEPT){
		struct rule * rule = join_rule(trim(s),trim(d),yylineno , priority);
	 	Push(&token_stack,curfilename,cur_trans,RULE_NODE , rule  );
      #ifdef OUTSTEP
	   #ifdef OUTFILE 
		record_rule(OUTFILE,rule);	
	   #endif 
		record_rule(STEPOUT,rule);
		#endif 

	 }
}

void record_comment(char * filename,struct comment * comment){
	char  * outfile  = filename  ; 
	if(strlen(filename) == 0 ){ err("OUTSTEP状态","OUTSTEP的宏定义错误") ; exit(1);}
	FILE * f = fopen(filename,"w");
	fprintf(f,"Add>>>\n");
	fprintf(f,"   Info| file:%s trans:%s level:%d\n",curfilename ,cur_trans,file_stack_count);
	fprintf(f,"Comment| lineno:%d c:%s\n",comment->lineno , comment->c);
	fprintf(f,"<<<\n");
	fclose(f);
}


struct comment_table * comment_table_reduce(char * c){		
	if(ACCEPT){
		struct comment * comment = join_comment(trim(c),yylineno);
		Add(&comment_tmp_tab, curfilename , cur_trans , COMMENT_NODE , comment  );
		#ifdef OUTSTEP
			#ifdef OUTFILE
			record_comment(OUTFILE,comment);		
			#endif
			record_comment(STEPOUT,comment);		
		#endif
	 }
}



