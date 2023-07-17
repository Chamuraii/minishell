#include "../includes/minishell.h"

t_all	g_all;

int	ft_readline(void)
{
	int		i;
	char	*str;

	str = readline("minishell > ");
	if (!str)
	{
		printf("exit\n");
		ft_free();
		exit(0);
	}
	if (str[0])
		add_history(str);
	if (ft_qvalidator(&str))
		g_all.array = to_double_pointer(str);
	else
		return (free(str), printf("validator failed\n"));
	ft_builtins(g_all.array);
	free(str);
	i = 0;
	while (g_all.array[i])
		free(g_all.array[i++]);
	free(g_all.array);
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
	ft_free();
}
