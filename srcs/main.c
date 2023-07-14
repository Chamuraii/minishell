#include "../includes/minishell.h"

t_all	g_all;

void	ft_sigint_handler() // aiuda
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int ft_readline()
{
	g_all.str = readline("minishell > ");

	if (!g_all.str)
	{
		printf("exit\n");
		ft_free();
		exit(0);
	}
	if (g_all.str[0])
		add_history(g_all.str);
	if(ft_qvalidator(g_all.str))
	{
		if (!ft_rvalidate(g_all.str))
			printf("rvalidator failed\n");
		else
			g_all.array = to_double_pointer((&g_all)->str);
	}
	else
		printf("qvalidator failed\n");
	//ft_builtins(g_all.str);
	free(g_all.str);
	return (0);
}

int main(int argc, char **argv, char **denv)
{
	(void)argv;
	(void)argc;

	signal(SIGINT, ft_sigint_handler); 
	signal(SIGQUIT, SIG_IGN);
	ft_var_init();
	int i = 0;
	while (denv[i])
		i++;
	g_all.env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!g_all.env)
		return (0);
	int j = -1;
	while (++j < i)
		g_all.env[j] = ft_strdup(denv[j]);
	j = -1;
	while (++j < i)
		ft_var_declare(g_all.env[j]);
	while (1)
	{
		ft_readline();
	}
	return (0);
}