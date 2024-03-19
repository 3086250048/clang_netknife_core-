#ifndef _NETKNIFE_H_
#define _NETKNIFE_H_

extern int yylineno;
void yyerror(char * ,...);
void init();


#define MAX_HASH 9999
extern struct rule_table * rule_tab ;
extern struct comment_table * comment_tab ;
extern struct trans * trans_tab ;

enum node_type {
	INDEX_STRING =1,
	RULE,
	COMMENT,
	IMPORT ,
	REGX,
	INCLUDE,
	EXCLUDE,
	RULE_TABLE,
	COMMENT_TABLE,
	TRANS,
};

struct index_string {
	int node_type;
	char * s;
	struct index_string * next ;
};


//添加字符到索引字符串
struct index_string * join_index_string(char * str);
//获取索引字符串的根节点地址,并让原有根节点指向NULL
struct index_string * get_index_string();
//释放索引字符串
void free_index_string(struct index_string * index_str_root);
//打印当前索引字符串
void print_index_string();
//合并index_string 
char * cat_string(struct index_string * root);


struct rule {
	int node_type;
	int lineno;
	int priority;
	struct index_string * s;
	struct index_string * d;
};

struct comment {
	int node_type ;
	int lineno;
	struct index_string * c;
};

//添加参数到rule中
struct rule * join_rule(struct index_string * s , struct index_string * d , int lineno , int priority );
//添加参数到comment中
struct comment * join_comment(struct index_string * c , int lineno );
//打印rule中的参数
void print_rule(struct rule *  r);
//打印comment中的参数
void print_comment(struct comment * c);

struct rule_table {
	int node_type ;
	struct rule * r;
	struct rule_table * dup_r;

};

struct comment_table{
	int node_type ;
	struct comment * c;
	struct comment_table * dup_c;
};

//添加rule到表中
struct rule_table * join_rule_table(struct rule * r);
//添加comment 到表中
struct comment_table * join_comment_table(struct comment * c);
//获取rule_table地址,重新分配空间给rule_tab
struct rule_table *  get_rule_table();
//获取comment_table地址,重新分配空间给comment_tab
struct comment_table * get_comment_table();




struct regx {
	int node_type;
	char * exp ;
	struct regx * next;
};

struct include {
	int node_type;
	int s_lineno ;
	int d_lineno ;
	char * s_comment;
	char * d_comment;
	struct include * next ;
};

struct exclude {
	int node_type ;
	int s_lineno;
	int d_lineno;
	char * s_comment ;
	char * d_comment ;
	struct exclude * next;
};

struct import_rule {	
	int node_type ;
	char * import_name ;
	int lineno;
	struct regx * reg;
	struct include * inc;
	struct exclude * exc;
	struct import_rule *  next ;
};


//添加正则表达式
struct regx * join_regx(char * exp);
//获取正则表达式链表根节点
struct regx * get_regx();
//添加include表达式
struct include * join_include(int s_lineno ,int d_lineno ,char * s_comment ,char *d_comment);
//获取include表达式根节点
struct include * get_include();
//添加exclude表达式
struct exclude * join_exclude(int s_lineno,int d_lineno , char * s_comment , char * d_comment);
//获取exclude表达式根节点
struct exclude * get_exclude();
//添加 import_rule
struct import_rule * join_import_rule(char * import_name ,int lineno ,struct regx * reg ,struct include *inc ,struct exclude * exc);
//获取import_rule表达式根节点
struct import_rule * get_import_rule();




struct trans {
	int node_type ;
	int lineno ;
	char * filename ;
	char * trans_name ;
	struct rule_table * rule_tab;
	struct comment_table * comment_tab;
	struct import_rule * import_rule_chain ;
};

//添加trans
struct trans * join_trans(
	int lineno , 
	char * trans_name , 
	struct rule_table * rule_tab ,
	struct comment_table * comment_tab ,
	struct import_rule * import_rule_chain 
);

	
//添加到trans_table
struct trans * join_trans_table(struct trans * trans);

//获取trans_table
struct trans * get_trans_table();

#endif

