/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 19:49:40 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../libft/include/libft.h"
# include <signal.h>
# include <curses.h>
# include <term.h>

# define NQ		0

# define DQ		34
# define DQO	1
# define DQI	2
# define DQC	3

# define SQ		39
# define SQO	4
# define SQI	5
# define SQC	6

typedef struct s_all
{
	char				*str;
	char				**array;
	char				**env;
	struct s_varlist	**var_list;
	struct s_varlist	**exported_list;
	int					i;
	int					j;
	int					p[2];
	int					size;
	int					error;
	char				*path;
	int					infile;
	int					outfile;
	int					array_pos;
	char				**commands;
	char				**where;
	int					is_infile;
	int					is_outfile;
	char				*eof_heredoc;
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
int			ft_builtin_unset(char *str, char **array, int i);
int			ft_builtin_cd(char *str, char **array, int i);
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
char		*ft_rseparator_pipe(char **str, int i);
char		*ft_rseparator_heredoc(char **str, int i);
char		*ft_rseparator_append(char **str, int i);
char		*ft_rseparator_infile_prio(char **str, int i);
char		*ft_rseparator_infile(char **str, int i);
char		*ft_rseparator_outfile(char **str, int i);
char		*ft_rseparator(int state, char **str, int i);
int			ft_squote_state(char c, int old_state);
int			ft_dquote_state(char c, int old_state);
int			ft_quote_state(char c, int old_state);
void		ft_expander_val(char *str, int i);
int			ft_rvalidator_pipe(char **str, int i);
int			ft_rvalidator_append(char **str, int i);
int			ft_rvalidator_heredoc(char **str, int i);
int			ft_rvalidator_infile(char **str, int i);
int			ft_rvalidator_outfile(char **str, int i);
int			ft_qvalidator(char **str);
int			ft_rvalidator(char **str, int i);
void		ft_sigint_handler(int signal);
void		ft_signals(void);
char		*ft_change_str(char **str, const char *str2);
char		*ft_expand(char **str);
char		*ft_reassign(char **str, char **array, int cnt);
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
int			ft_quotes_jess(char *str);
int			is_pipe(void);
int			is_builtins(char **array);
int			ft_dont_expand(char *str, int i);
int			ft_return(int status, char *str);
int			ft_get_state(char *str, int j);
int			ft_q_error_message(char **str, int i);

// execute.c

void		pipe_child(int last);
void		pipes(int last);
void		builtin_now(int j);
void		is_execve(int j);

// heredoc.c

void		write_heredoc(char *his);
int			heredoc(int j);
void		ptp_heredoc(int i);

// pipe.c

void		del_arg(int i, int h, int g, int k);
int			is_pipe(void);
void		args_fill(int i, int end, int j);
void		split_pipe(void);

// redirection.c

void		ptp_infile(int i);
void		ptp_outfile(int i);
void		ptp_append(int i);
void		redirections(int i, int end);

// start_exit.c

int			ft_exit(int status);
int			ft_return(int status, char *str);
void		free_fd(void);
int			execute(void);

// where.c

char		*ft_strj(char *s1, char *s2);
int			path(void);
int			where(void);

#endif