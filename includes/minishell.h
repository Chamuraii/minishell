#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <curses.h>
# include <term.h>

//hacer lista

# define NQ		0

# define DQ		34
# define DQO	1
# define DQI	2
# define DQC	3

# define SQ  39
# define SQO 4
# define SQI 5
# define SQC 6

// TODO
//  ------
//  When pressing TAB, do nothing.			Mirar si hacerlo
//  leaks
//  norminette


typedef struct s_all
{
	//parser
	char				*str;
	char				**array;
	char				**env; //stack
	struct s_varlist	**var_list;
	struct s_varlist	**exported_list;
	int 				array_pos;
	//pipex
	char				**commands;
	char				**recep;
	char				**where;
	char				*path;
	int					infile;
	int					is_infile;
	int					outfile;
	int					is_outfile;
	int					error;
	char				*eof_heredoc;
	int					pid;
	int					p[2];
	int					i;
	int					j;
	int					size;
	int					start_i;
	int					end_i;
}	t_all;

typedef struct s_varlist
{
	char				*key;
	char				*value;
	struct s_varlist	*next;
}	t_varlist;

int			ft_builtins(char **array, int i);
int			is_builtins(char **str);
int			ft_builtin_env(char **array);
int			ft_builtin_pwd(char **array);
int			ft_builtin_export(char *str, char **array, int i);
int			ft_builtin_unset(char *str, char **array);
int			ft_builtin_cd(char *str, char **array);
int			ft_builtin_echo(char *str, char **array);
t_varlist	*ft_create_node(char *key, char *value);
void		ft_add_var(char *key, char *value);
int			ft_var_declare(char *str);
char		*ft_get_var(char *key);
t_varlist	*ft_create_node_exp(char *key, char *value);
void		ft_add_var_exp(char *key, char *value);
int			ft_var_declare_exp(char *str);
char		*ft_get_var_exp(char *key);
void		ft_free(char *type);
void		ft_free_2(void *var1, void *var2);
void		ft_error_messages(void);
void		ft_var_init(void);
void		ft_init_env(char **denv);
int			ft_readline(void);
char		*ft_rseparator_1(char **str, int i);
char		*ft_rseparator_2(char **str, int i);
char		*ft_rseparator_3(char **str, int i);
char		*ft_rseparator_4(char **str, int i);
char		*ft_rseparator_5(char **str, int i);
char		*ft_rseparator_6(char **str, int i);
char		*ft_rseparator(int state, char **str, int i);
int			ft_squote_state(char c, int old_state);
int			ft_dquote_state(char c, int old_state);
int			ft_quote_state(char c, int old_state);
void		ft_expander_val(char *str, int i);
int			ft_rvalidator_1(char **str, int i);
int			ft_rvalidator_2(char **str, int i);
int			ft_rvalidator_3(char **str, int i);
int			ft_rvalidator_4(char **str, int i);
int			ft_rvalidator_5(char **str, int i);
int			ft_qvalidator(char **str);
int			ft_rvalidator(char **str, int i);
void		ft_sigint_handler(int signal);
void		ft_signals(void);
char		*ft_change_str(char **str, const char *str2);
char		*ft_expand(char **str);
char		*ft_reassign(char **str, char *next_str, int cnt);
char		**to_double_pointer(char **str);
void		ft_del_var(char *key);
int			ft_is_p_or_r(char *str);
int			ft_return_qstate(char *str, char *char_pos);
char		*ft_remove_quotes(char *str);
char		*ft_remove_quotes_2(char **str);
int			ft_find_var_exp(char *key);
int			ft_change_dir(char *str);
int			ft_is_p_or_r_between_quotes(char *str);
int			ft_search_var(char *key);
int			execute(void);

#endif