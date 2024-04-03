#ifndef _NETKNIFE_H_
#define _NETKNIFE_H_
#include <stdio.h>
extern int yylineno;
void yyerror(char * ,...);
int  yylex(void);
int yyparse(void);
void yyrestart ( FILE *input_file  );
void init();

#define PRINT_FACTOR 1

#define PRINT_TRANS_TABLE_ENTRY 0*PRINT_FACTOR,""

#define PRINT_IMPORT 5*PRINT_FACTOR," "

#define PRINT_FILTER 10*PRINT_FACTOR," "
#define PRINT_RANGE 15*PRINT_FACTOR," "

#define PRINT_RULE_TABLE_ENTRY 5*PRINT_FACTOR," "
#define PRINT_COMMENT_TABLE_ENTRY 5*PRINT_FACTOR," "

#define PRINT_RULE 10*PRINT_FACTOR," "
#define PRINT_COMMENT 10*PRINT_FACTOR," " 

#define MAX_HASH 9999


extern struct rule_table * rule_tab ;
extern struct comment_table * comment_tab ;
extern struct trans_table * trans_tab ;
extern int mode ;


struct yy_buffer_state
	{
	FILE *yy_input_file;
	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */
	int yy_buf_size;
	int yy_n_chars;
	int yy_is_our_buffer;
	int yy_is_interactive;
	int yy_at_bol;
    int yy_bs_lineno; /**< The line count. */
    int yy_bs_column; /**< The column count. */
	int yy_fill_buffer;
	int yy_buffer_status;
	#define YY_BUFFER_NEW 0	
	#define YY_BUFFER_NORMAL 1
	#define YY_BUFFER_EOF_PENDING 2
};
typedef struct yy_buffer_state *YY_BUFFER_STATE;

struct bufstack{
		//上一个文件信息
		struct bufstack * prev ;
		//保存的缓冲区
		YY_BUFFER_STATE bs;
		int lineno;	
		char * filename;
		FILE * f;//当前文件		
};

extern bufstack * curbs ;
extern char * curfilename ;


enum type {
	INDEX_STRING_NODE =1,
	RULE_NODE,
	COMMENT_NODE,
	IMPORT_NODE ,
	REGX_NODE,
	RANGE_NODE,
	INCLUDE_NODE,
	EXCLUDE_NODE,
	RULE_TABLE_ENTRY_NODE,
	COMMENT_TABLE_ENTRY_NODE,
	TRANS_NODE,
	TRANS_TABLE_NODE
	PUB_MODE,
	TRANS_MODE
};

char * trim(char * str);

struct rule {
	int node_type;
	int lineno;
	int priority;
	char  * s;
	char  * d;
};

struct comment {
	int node_type ;
	int lineno;
	char  * c;
};

//添加参数到rule中
struct rule * join_rule(char  * s , char  * d , int lineno , int priority );
//添加参数到comment中
struct comment * join_comment(char  * c , int lineno );
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
//获取rule_table_entry
struct rule_table *  get_rule_table_entry(struct rule_table * rule_tab ,char  * s);
//获取comment_table_entry
struct comment_table * get_comment_table_entry(struct comment_table * comment_tab ,char * c);
//获取rule_table地址,重新分配空间给rule_tab
struct rule_table *  get_rule_table();
//获取comment_table地址,重新分配空间给comment_tab
struct comment_table * get_comment_table();
//打印rule_table 表项
void print_rule_table_entry(struct rule_table * rule_tab);
//打印comment表项
void print_comment_table_entry(struct comment_table * comment_tab);


struct range {
	int node_type;
	char * regx;
	int s_lineno ;
	int d_lineno ;
	char  * s_comment;
	char  * d_comment;
	struct range * next ;
};


struct filter {
	int node_type;
	struct range * range ;
	struct filter * next ;
};

struct import_rule {	
	int node_type ;
	char * file_name ;
	char * import_name ;
	int lineno;
	struct filter * filter ;
	struct import_rule *  next ;
};



//添加range表达式
struct range * join_range(struct range * root ,char  * regx , int s_lineno ,int d_lineno , char  * s_comment ,char * d_comment );
//添加filter表达式
struct filter * join_filter(struct filter * root , int node_type , struct range  * range);
//添加 import_rule
struct import_rule * join_import_rule(char * file_name , char * import_name ,int lineno  ,struct filter * filter );
//获取import_rule表达式根节点
struct import_rule * get_import_rule();

//打印range
void print_range(struct range * range_root);
//打印import_rule
void print_import_rule(struct import_rule * import_rule_root);


struct trans {
	int node_type ;
	int lineno ;
	char * filename ;
	char * trans_name ;
	struct rule_table * rule_tab;
	struct comment_table * comment_tab;
	struct import_rule * import_rule_chain ;
};

struct trans_table{
	int node_type;  
	struct trans * trans;
};

//添加trans
struct trans * join_trans(
	char * filename ,
	char * trans_name , 
	int lineno , 
	struct rule_table * rule_tab ,
	struct comment_table * comment_tab ,
	struct import_rule * import_rule_chain 
);

	
//添加到trans_table
struct trans_table * join_trans_table(struct trans * trans);

//获取trans_tabele 表项
struct trans * get_trans_table_entry(struct trans_table * trans_tab,char * filename , char * trans_name);
//获取trans_table
struct trans_table * get_trans_table();
//打印trans表项
void print_trans_table_entry(struct trans * trans);


#endif


