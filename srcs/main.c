#include "../includes/minishell.h"

t_all	g_all;

int	ft_readline(void)
{
	g_all.rl_str = ft_strdup("minishell@$USER$ ");
	g_all.rl_str = ft_expand(&(g_all.rl_str));
	g_all.str = readline(g_all.rl_str);
	if (!g_all.rl_str)
	{
		printf("exit\n");
		ft_free("exit");
		exit(0);
	}
	if (g_all.str[0])
		add_history(g_all.str);
	if (ft_qvalidator(&(g_all.str)))
		g_all.array = to_double_pointer(&(g_all.str));
	else
		return (free(g_all.str), printf("validator failed\n"));
	ft_builtins(g_all.array);
	ft_free("no exit");
	return (0);
}

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **env)
{
	atexit(ft_leaks);
	(void)argv;
	(void)argc;
	ft_signals();
	ft_var_init();
	ft_init_env(env);
	while (1)
		ft_readline();
	ft_free("exit");
}
