#include "netknife.h"
#include <stdlib.h>

struct  rule_table * rule_tab ;
struct  comment_table * comment_tab;
struct  trans_table  * trans_tab ;

void init(){
rule_tab = malloc(sizeof(struct rule_table) * MAX_HASH);
comment_tab = malloc(sizeof(struct comment_table) *MAX_HASH);
trans_tab = malloc(sizeof(struct trans_table)*MAX_HASH);
}
