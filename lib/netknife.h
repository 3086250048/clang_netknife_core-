#ifndef _NETKNIFE_H_
#define _NETKNIFE_H_
#include <stdio.h>
enum type {
	/*节点类型*/
	INDEX_STRING_NODE =1,
	RULE_NODE=2,
	COMMENT_NODE=3,
	IMPORT_NODE=4 ,
	REGX_NODE=5,
	RANGE_NODE=6,
	INCLUDE_NODE=7,
	EXCLUDE_NODE=8,
	RULE_TABLE_ENTRY_NODE=9,
	COMMENT_TABLE_ENTRY_NODE=10,
	TRANS_NODE=11,
	NETKNIFE_NODE=12,
	BUFFER_NODE=13,
	/*规约状态*/
	IMPORT_TRANS_STATE=14,	
	NORMAL_STATE=15,
	/*规约函数特殊参数 */
	VOID = 16,
	NORMAL =17,
	/*特殊的BUFFER类型*/
	_EOF_ = 18 ,
	/*过滤所匹配的规则*/
	REGX_ONLY = 19,
	S_LINENO_ONLY =20,
	S_COMMENT_ONLY = 21 ,
	LINENO_ONLY = 22 ,
	COMMENT_ONLY =23 ,
	LINENO_AND_COMMENT=24
};


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
#define MAX_STACK 999
#define ALL_TRANS "ALL_TRANS"

/*lex.c 中的一些定义*/
extern int yylineno;
void yyerror(char * ,...);
int  yylex(void);
int yyparse(void);
void yyrestart ( FILE *input_file  );

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
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
#endif /* !YY_STRUCT_YY_BUFFER_STATE */



#ifndef YY_BUF_SIZE
#ifdef __ia64__
#define YY_BUF_SIZE 32768
#else
#define YY_BUF_SIZE 16384
#endif /* __ia64__ */
#endif

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif


void yy_delete_buffer ( YY_BUFFER_STATE b  );
void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
YY_BUFFER_STATE yy_create_buffer ( FILE *file, int size  );
/**/


struct bufstack{
		//上一个文件信息
		struct bufstack * prev ;
		//保存的缓冲区
		YY_BUFFER_STATE bs;
		int lineno;	
		char * filename;
		FILE * f;//当前文件		
};

struct filterstack{
	//上一个import的filter信息
	struct filterstack * prev ;
	struct filter * filter ;
};

extern struct rule_table * rule_tab ;
extern struct comment_table * comment_tab ;
extern struct trans * trans_tab ;
extern struct netknife * netknife_tab;
extern int mode ;//unused
extern char * cur_trans;
extern char * target_trans;
extern char * start_trans;
extern int cur_state;
extern struct bufstack * curbs ;
extern char * curfilename ;
extern int file_stack_count;
extern int import_stack_count;
extern int filter_stack_count;
extern struct filter *  curfilter;
extern struct filterstack * curfilterstack;
extern struct buffer * buffer_root;

int newfile(char * fb);
int popfile(void);
int newfilter(struct filter *);
int popfilter(void);

void init();
char * trim(char * str);

/* 语法相关结构体和方法*/
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
//二次添加rule到rule_tab表中
struct rule_table * assign_join_rule_table(struct rule_table * root,struct rule * r);
//rule_table 规约
struct rule_table * rule_table_reduce(char *s , char * d , int priority);

//添加comment 到表中
struct comment_table * join_comment_table(struct comment * c);
//二次添加rule到rule_tab表中
struct comment_table * assign_join_comment_table(struct comment_table * root,struct comment * c);
//comment_tabele 规约
struct comment_table * comment_table_reduce(char * c); 


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
//计算import
void eval_import(struct import_rule * import_node,char * trans_name);

struct trans {
	int node_type ;
	char * name ;
	int lineno ;
	struct rule_table * rule_tab;
	struct comment_table * comment_tab;
	struct import_rule * import_rule_chain ;
};

//添加trans
struct trans * join_trans(
	char * name , 
	int lineno , 
	struct rule_table * rule_tab ,
	struct comment_table * comment_tab ,
	struct import_rule * import_rule_chain 
);

//打印trans表项
void print_trans(struct trans * trans);

//trans 规约
struct trans * trans_reduce(int isempty);


struct netknife{
	int node_type;  
	char * filename ; //文件名称
	int  child_type; // 节点类型
    char * child_name; // 节点名称
	void * child_tab ;// 节点hash表头地址
	
};
	
//添加到netknife_table 
struct netknife  * join_netknife_table(char * filename ,void * node );
//获取netknife中某个node_tab
void  * get_netknife_node(char * filename , int  node_type, char * node_name );
//netknife规约
struct netknife * netknife_reduce(int isempty , void * node);

struct buffer{
	int node_type ;
	char * filename ; //文件名称
	int  buffer_type; // 缓存类型
    char * buffer_name; // 缓存名称
	void * buffer  ;// 缓存根节点地址
	struct buffer * prev ;
	struct buffer * next ;
};


//添加到buffer 
void  join_buffer_chain(char * filename ,char * buffer_name ,int buffer_type ,void * buffer);
//获取buffer_chain 的根地址
struct buffer * get_buffer(); 
//添加到指定的buffer
struct buffer * assign_join_buffer_chain( struct buffer * root, char * filename , char * buffer_name , int buffer_type ,  void * buffer);


#endif


