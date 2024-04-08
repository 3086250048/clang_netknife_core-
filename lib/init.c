#include "netknife.h"
#include <stdlib.h>
//TRANS语法树相关
struct  rule_table * rule_tab ;
struct  comment_table * comment_tab;
struct  netknife * netknife_tab ;
struct  netknife * buffer_tab;
//文件栈相关
struct bufstack * curbs=NULL;
char * curfilename;
int file_stack_count=0; 
//import相关
int import_stack_coutn=0;

//计算语法树相关
/*
1)mode决定哪种类型节点可以被添加进语法树。
2)默认值为PUB_MODE,表示所有类型节点都可以被添加进语法树。
3)在trans中import其他trans时mode会变为TRANS_MODE,表示只将TRANS类型节点添加进语法树。
 */
int mode = PUB_MODE;//unused
/*
1)只有与trans_target名称一致的trans才会被添加进语法树
2)默认值为ALL,表示所有名称的trans节点都会被添加进语法树
3)cur_trans 代表当前trans的名称。
*/
char * cur_trans=NULL ;
char * target_trans=NULL;


/*
 *状态机
 */
int cur_state = NULL;

void init(){
rule_tab = calloc(MAX_HASH,sizeof(struct rule_table));
comment_tab = calloc(MAX_HASH ,sizeof(struct comment_table) );
netknife_tab  = calloc(MAX_HASH,sizeof(struct netknife));
buffer_tab = calloc(MAX_HASH,sizeof(struct netknife));
}
