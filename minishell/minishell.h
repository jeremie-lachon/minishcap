#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE_SIZE 65336
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int				g_bigsignal;

typedef enum e_lex
{
	LEX_START = 0,
	LEX_WORD = 1,
	LEX_REDIROUT = 2,
	LEX_REDIRIN = 3,
	LEX_AND = 4,
	LEX_PIPE = 5,
	LEX_OPEN = 6,
	LEX_CLOSE = 7,
	LEX_OR = 8,
	LEX_HERE = 9,
	LEX_APPEND = 10,
	LEX_END = 11
}						t_lex;

typedef enum e_type
{
	SHELL,
	EXEC,
	REDIR,
	PIPE,
	SUB,
	AND,
	OR,
	HERE,
	EMPTY
}						t_type;

typedef enum e_filedesc
{
	FD_FILEIN,
	FD_FILEOUT,
}						t_filedesc;

// Structs

typedef struct s_cmd
{
	int					type;
}						t_cmd;

typedef struct s_sub
{
	int					type;
	t_cmd				*cmd;
}						t_sub;

typedef struct s_herepipe
{
	char				*str;
	int					stored;
	int					quote;
	struct s_herepipe	*next;
}						t_herepipe;

typedef struct s_shell
{
	int					type;
	t_cmd				*tree;
	char				**env;
	t_herepipe			*pipe;
}						t_shell;

typedef struct s_execcmd
{
	int					type;
	char				**args;
}						t_execcmd;

typedef struct s_pipecmd
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_pipecmd;

typedef struct s_redircmd
{
	int					type;
	t_cmd				*cmd;
	char				*file;
	char				*efile;
	int					mode;
	int					fd;
	int					quote;
	char				*heredoc;
}						t_redircmd;

typedef struct s_andcmd
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_andcmd;

typedef struct s_orcmd
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_orcmd;

typedef struct s_doublecmd
{
	int					type;
	t_cmd				*left;
	t_cmd				*right;
}						t_doublecmd;

typedef struct s_lexer
{
	int					type;
	char				*heredoc;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_subquote
{
	char				*str;
	int					check;
}						t_subquote;

typedef struct s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

typedef struct s_file
{
	char				*filename;
	char				*search;
}						t_file;

typedef struct s_fds
{
	int					fd;
	int					type;
}						t_fds;

typedef struct s_execs
{
	t_list				*fds;
	t_shell				*shell;
	int					ret;
	t_cmd				*cmd;
	int					stdcopies[2];
	char				*buff;
}						t_execs;

int						heredoccer(char *heredoc, int check, t_execs *exec,
							char **filename);

//	Lib and Useful Funcs
char					*ms_substr(char const *s, unsigned int start,
							size_t len);
int						nodeadder(t_list **lst, char *str1, char **str2,
							int check);
char					*ms_strjoin(char const *s1, char const *s2);
char					*ms_strtrim(char *s1, char const *set);
int						iswhite(char c);
char					*ms_strcatter(char *str1, char *str2);
char					*ms_strdup(char *str);
char					*ms_strstr(char *haystack, char *needle);
char					*ms_itoa(int num);
int						arrayfree(char ***array);
char					**ms_pathsplit(char const *s, char c, char *bonus);
char					*ms_itoul(unsigned long num);
int						ms_strncmp(const char *s1, const char *s2, size_t n);
void					*ms_memset(void *s, int c, size_t n);
int						ms_strcmp(const char *s1, const char *s2);
void					*ms_calloc(size_t nmemb, size_t size);
char					*ms_strchr(char *s, char c);
char					*ms_strchr2(char *s, char c);
char					*ms_strchrreal(char *s, char c);
// void					ms_bzero(void *s, size_t n);
int						ms_strlen(const char *s);
char					**ms_split(char const *str, char c);
void					*ms_calloc(size_t nmemb, size_t size);
int						lfsymbol(char **ptr, char *c);
int						lfsymbol2(char **ptr, char *c);
char					*ms_filecpy(char *file, char *efile);
size_t					ms_strlcpy(char *dst, const char *src, size_t size);
char					*ms_strcat(char *str1, char *str2);
int						ms_isalpha(int c);
char					*get_env(char *name, char **env);
int						ms_write(int fd, char *str, int size);
int						ms_isalphanum(char chr);

// Moded LIBFT
char					**args_malloc(int argc, char *ptr_arg, char *ptr_earg,
							char **args);
char					*empty_string(void);
void					ms_strcpy_quoteless(char **dest, char *src);
int						ms_strcmp2(const char *s1, const char *s2);
int						size_pwd(char **env);
void					print_env(char **env);

//  List Funcs
t_list					*listnew(void *data, void (*f)(void *));
t_list					*listaddback(t_list **lst, t_list *new, void (*f)(void *));
int						ms_listfree(t_list **lst, void (*f)(void *));
int						listsize(t_list *list);
t_lexer					*ms_lstlast(t_lexer *lst);
void					ms_lstadd_back(t_lexer **lst, t_lexer **new);

//	Struct Funcs
t_subquote				*subquotenew(char *data, int check);
void					subquotefree(void *data);
t_file					*filenew(char *data);
void					filefree(void *data);
t_fds					*fdsnew(int fd, int type);
void					fdsfree(void *data);
int						execfree(t_execs *exec);
void					free_array(char **s);
void					free_args(t_execcmd *ex);
void					free_exec(t_execcmd *ex);
void					free_sub(t_sub *sub);
void					free_redir(t_redircmd *re);
void					free_double(t_doublecmd *db);
void					tree_free(t_cmd **tree);
void					free_herepipe(t_shell **shell);
t_cmd					*redircmd_out(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_in(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_append(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_in2(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_out2(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_append2(t_cmd *cmd, char *file, char *efile,
							int fd);
t_cmd					*redircmd_here(t_herepipe **pipe, t_cmd *cmd);
t_cmd					*redircmd_here2(t_herepipe **pipe, t_cmd *cmd);
t_cmd					*execcmd(void);
t_cmd					*pipecmd(t_cmd *left, t_cmd *right);
t_cmd					*andcmd(t_cmd *left, t_cmd *right);
t_cmd					*orcmd(t_cmd *left, t_cmd *right);
void					ms_removefd(t_list *fds, t_execs *exec);
int						exit_execfree(t_execs *exec, int err);
int						ms_sorterfree(t_execs *exec, t_cmd *cmd);

//	Expansion
t_list					*expansion(char *str);

//	Substitution Heredoc 2
void					indexdollar(char *str, int *i, int fd, t_list **list);
char					*getdollarherehere(char *str, int *i, t_execs *exec);

// 	Substitution Heredoc
char					*getdollarhere(char **str, int final);
char					*dollarhere(char *str, int final, t_list *lst,
							char *tmp);
char					*dollarquotehere(char *str, t_list *lst, char *tmp);

// Substitution
void					substitution_error(char *str);
char					*getdollar(char **str, int final, t_execs *exec);
char					*dollar(char *str, int final, t_execs *exec,
							t_list *lst);
char					*dollarquote(char *str, t_execs *exec);

// Wildcard and Dequote
t_list					*sub_unquoted(char *str, t_list **quote, int *index,
							char *res);
t_list					*resplitter(t_list *lst, t_list *quote, t_list *final,
							int i);
t_list					*star(t_list *lst);

//  File Funcs
t_list					*filer(int check);
void					filecheck(t_list *files, t_list *node, int mode);
t_list					*filelist(t_list *files, t_list *list);

//  Printer Funcs
void					subquoteprint(void *data);
void					strprint(void *data);
void					fileprint(void *data);
void					printlist(t_list *list, void (*print)(void *));
void					intprint(void *data);
void					print_indent(int indent);
void					print_redircmd(t_redircmd *redir, int indent);
void					print_execcmd(t_execcmd *exec, int indent);
void					print_pipecmd(t_pipecmd *pipe, int indent);
void					print_andcmd(t_andcmd *and, int indent);
void					print_orcmd(t_orcmd *or, int indent);
void					print_doublecmd(t_doublecmd *dbl, int indent);
void					print_subcmd(t_sub *sub, int indent);
void					ms_printerror(char *str, char *name, char *str2);

// Signal Funcs
void					signals(void);
void					signals_heredoc(void);
int						checkerr(int err);

// Argument Func
char					**args(char **arguments, t_execs *exec, t_list *list,
							int i);
int						ms_expandcmd(t_execs *exec, t_cmd *cmd);
char					*argument_heredoc(char *arg, t_list *tmp, t_list *lst);

// fds
int						ms_setfds(t_execs *exec);
int						ms_closeallfds(t_execs *exec);

// Command and Path
char					**ms_pathsplit(char const *s, char c, char *bonus);
int						ms_command(t_execs *ex, t_execcmd *cmd, char *com);
void					miniprint(char *str, int i);

// Exec Main Func
int						executer(t_shell *shell, int err, char *buff);

// Exec Funcs
int						ms_sorter(t_execs *exec, t_cmd *cmd);
int						ms_pipe(t_execs *exec, int err, t_pipecmd *cmd);
int						ms_redir(t_execs *exec, int err, t_redircmd *cmd);
int						ms_and(t_execs *exec, int err, t_andcmd *cmd);
int						ms_or(t_execs *exec, int err, t_orcmd *cmd);
int						ms_sub(t_execs *exec, int err, t_sub *cmd);
int						ms_exec(t_execs *exec, int err, t_execcmd *cmd);
int						ms_here(t_execs *exec, int err, t_redircmd *cmd);
int						ms_exec3(int err);

// Parsing

void					parseredirs_primo(t_herepipe **pipes, t_cmd **cmd,
							char **ps, int *check);
t_cmd					*parseredirs_er(t_herepipe **pipes, t_cmd *cmd,
							char **ps);
int						gettoken(char **ptr, char **ptr_token,
							char **ptr_endtoken);
t_cmd					*parseexec(t_shell *shell, char **ps, int check,
							int argc);
t_cmd					*parse_double_node(t_shell *shell, char **ptr);
t_cmd					*parse_and(t_shell *shell, char **ptr);
t_cmd					*parse_or(t_shell *shell, char **ptr);
t_cmd					*parseline(t_shell *shell, char **ptr);
int						parsecmd(t_shell **shell, char *str, int err);
int						quote_check(char *str);
void					saver(int in);
void					saver2(int *in, char **buf);

// Lexer
int						add_lex_node(t_lexer **lex, char *str, int *i);
int						lexer(t_shell **shell, char *str);
int						sub_lexer(t_lexer **lex, char *str, int *i);
int						prev_check(t_lexer *lex, char *str);
int						next_check(t_lexer *lex, char *str);
int						first_type_check(t_lexer *lex);
char					*heredoc_filler(char *end);
int						init_heredoc(t_lexer *lex, t_shell **shell);
int						lexing_check(t_shell **shell, t_lexer *lexer);
void					free_lexer(t_lexer *lexer);
int						and_return(t_lexer **new, char *str, int *i);

int						add_quote_node(t_lexer **lex, char *str, int *i,
							char c);
void					ms_pipeaddback(t_shell **shell, t_herepipe *new);
int						skip_quotes(char *str, int *i, int *size, int check);
// Printer

void					printer(t_cmd *cmd, int s, int level);
void					print_indent(int indent);
void					print_redircmd(t_redircmd *redir, int indent);
void					print_execcmd(t_execcmd *exec, int indent);
void					print_pipecmd(t_pipecmd *pipe, int indent);
void					print_andcmd(t_andcmd *and, int indent);
void					print_doublecmd(t_doublecmd *dbl, int indent);
void					print_orcmd(t_orcmd *or, int indent);
void					print_subcmd(t_sub *sub, int indent);
void					print_cmd(void);

// Built-in

int						isbuiltin(char *cmd);
int						builtin(t_execs *exec);
int						ms_cd(t_execs *execs);
int						ms_echo(t_execs *execs);
int						ms_env(t_execs *execs);
int						ms_exit(t_execs *ex);
int						ms_export(t_execs *execs);
int						ms_pwd(t_execs *execs);
int						ms_unset(t_execs *execs);
char					**new_env(char ***env, char *cmd);
char					*minisplit(char *s, int c);
char					**new_env(char ***env, char *cmd);
char					*get_env_mine(char *name, char **env);
void					ms_getcwd(char **pwd);
int						move_back(char **env);
int						ms_move(char **cmd, char **env);
char					*ms_strjoin_free(char *s1, char const *s2);
#endif