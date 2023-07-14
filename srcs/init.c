#include "../includes/minishell.h"

extern t_all g_all;

void	ft_var_init()
{
	g_all.str = 0;
	g_all.i = 0;
	g_all.env = 0;
	g_all.array = 0;
	g_all.list_size = 0;
	g_all.commands = 0;
	g_all.path = 0;
	g_all.varlist = (t_varlist **)malloc(sizeof(t_varlist *));
	if (!g_all.varlist)
	{
		printf("ERROR, not enough memory\n");
		exit(0);
	}
	g_all.varlist[0] = 0;
}

void	ft_init_env(char **denv)
{
	int i;
	int j;

	i = 0;
	while (denv[i])
		i++;
	g_all.env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!g_all.env)
		ft_error_messages();
	j = -1;
	while (++j < i)
		g_all.env[j] = ft_strdup(denv[j]);
	j = -1;
	while (++j < i)
		ft_var_declare(g_all.env[j]);
}