#include "netknife.h"
#include <stdlib.h>
//TRANS语法树相关
struct  rule_table * rule_tab ;
struct  comment_table * comment_tab;
struct  netknife * netknife_tab ;
//文件栈相关
struct bufstack * curbs=NULL;
char * curfilename;
int file_stack_count=0; 
//import相关
struct filter * curfilter=NULL;
char * cur_trans=NULL ;
char * target_trans=NULL;
struct import_trans *  cur_import_trans=NULL;
char * start_trans = NULL;
char * start_file = NULL;
struct stack * PreLevelFilterStack  = NULL;
/*buffer*/
struct stack  * rule_stack   = NULL;
struct stack  * import_stack = NULL;
struct table  * filter_entry_tab = NULL ;
struct table  * comment_tmp_tab   = NULL;

char * cmd_input = NULL;
int goto_global = 0 ;
int flex_state = GLOBAL_STATE ;
struct trans * cur_use_trans = NULL; 
struct rule_table * tmp_rule_tab = NULL;
struct trans *  after_filter_trans = NULL;

//初始化
void init(){
rule_tab = calloc(MAX_HASH,sizeof(struct rule_table));
tmp_rule_tab = calloc(MAX_HASH,sizeof(struct rule_table));
comment_tab = calloc(MAX_HASH ,sizeof(struct comment_table) );
netknife_tab  = calloc(MAX_HASH,sizeof(struct netknife));
//yy_cur_buf = init_yy_buf();
}
