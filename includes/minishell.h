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
#include "../libft/libft.h"
# include <signal.h>
#include <curses.h>
#include <term.h>

//hacer lista

# define NQ  0

# define DQ  34
# define DQO 1
# define DQI 2
# define DQC 3

# define SQ  39
# define SQO 4
# define SQI 5
# define SQC 6

// TODO
//  ------

typedef struct s_all
{
	//parser
	char				*str;
	char 				**array;
	char				**env;
	struct	s_varlist	**var_list;
	struct	s_varlist	**exported_list;
	//pipex
    char    			**commands;
    char    			**recep;
    char    			**where;
    char    			*path;
    int     			infile;
    int     			outfile;
    int     			pid;
    int     			p[2];
    int     			i;


}           t_all;

typedef struct s_varlist
{
	char				*key;
	char				*value;
	struct s_varlist	*next;
}	t_varlist;

int			ft_builtins(char **str);
int			ft_builtin_1(void);
int			ft_builtin_2(void);
int			ft_builtin_3(char *str, char **array, int i);
int			ft_builtin_4(char *str, char **array, int i);
t_varlist	*ft_create_node(char *key, char *value);
void		ft_add_var(char *key, char *value);
int			ft_var_declare(char *str);
char		*ft_get_var(char *key);
t_varlist	*ft_create_node_exp(char *key, char *value);
void		ft_add_var_exp(char *key, char *value);
int			ft_var_declare_exp(char *str);
char		*ft_get_var_exp(char *key);
void		ft_free();
void		ft_free_2(void *var1, void *var2);
void		ft_error_messages();
void		ft_var_init();
void		ft_init_env(char **denv);
int			ft_readline();
void		ft_rseparator_1(char **str, int i);
void		ft_rseparator_2(char **str, int i);
void		ft_rseparator_3(char **str, int i);
void		ft_rseparator_4(char **str, int i);
void		ft_rseparator_5(char **str, int i);
void		ft_rseparator_6(char **str, int i);
void		ft_rseparator(int state, char **str, int i);
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
char		*ft_reassign(char **str);
char		**to_double_pointer(char **str);
void		ft_del_var(char *key);

#endif