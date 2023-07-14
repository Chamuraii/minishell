#include "../includes/minishell.h"

t_all	g_all;

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
	for(int i = 0; g_all.array[i]; i++)
		free(g_all.array[i]);
	free(g_all.array);
	return (0);
}

/*
void	ft_leaks()
{
	system("leaks -q minishell");
}
*/

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;

	ft_signals();
	ft_var_init();
	ft_init_env(env);
	while (1)
		ft_readline();
}