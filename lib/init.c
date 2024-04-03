#include "netknife.h"
#include <stdlib.h>

struct  rule_table * rule_tab ;
struct  comment_table * comment_tab;
struct  trans_table  * trans_tab ;


void init(){
rule_tab = calloc(MAX_HASH,sizeof(struct rule_table));
comment_tab = calloc(MAX_HASH ,sizeof(struct comment_table) );
trans_tab = calloc(MAX_HASH , sizeof(struct trans_table) );
}
