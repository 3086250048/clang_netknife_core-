#include "netknife.h"
#include <stdlib.h>
//TRANS语法树相关
struct  rule_table * rule_tab ;
struct  comment_table * comment_tab;
struct  netknife * netknife_tab ;
struct  buf * buf_tab ;
//文件栈相关
struct bufstack * curbs=NULL;
char * curfilename;
int file_stack_count=0; 
//import相关
int import_stack_count=0;
int filter_stack_count=0;
struct filter * curfilter=NULL;
struct filterstack * curfilterstack =NULL;
//计算语法树相关
char * cur_trans=NULL ;
char * target_trans=NULL;
char * start_trans=NULL;
//状态机
int cur_state = NORMAL_STATE;
void init(){
rule_tab = calloc(MAX_HASH,sizeof(struct rule_table));
comment_tab = calloc(MAX_HASH ,sizeof(struct comment_table) );
netknife_tab  = calloc(MAX_HASH,sizeof(struct netknife));
buf_tab = calloc(MAX_HASH , sizeof(struct buf));
}
