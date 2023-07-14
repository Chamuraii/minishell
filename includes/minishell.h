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

# define DQ  39
# define DQO 1
# define DQI 2
# define DQC 3

# define SQ  34
# define SQO 4
# define SQI 5
# define SQC 6

typedef struct s_all
{
	//parser
	char **env;
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
	char				*str;
	char 				*str_cpy;
	char 				**array;
	struct	s_varlist	**varlist;
	int 				list_size;
}           t_all;

typedef struct s_varlist
{
	char				*key;
	char				*value;
	struct s_varlist	*next;
}	t_varlist;

int		ft_qvalidator(char *str);
int		ft_rvalidate(char *str);
int		ft_builtins(char *str);
char	**to_double_pointer(char *str);
void	ft_var_init();
char	*ft_get_var(char *key);
int		ft_var_declare(char *str);
void	ft_del_var(char *key);
void	ft_free();

#endif