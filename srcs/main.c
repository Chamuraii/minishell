#include "../includes/minishell.h"

t_all	g_all;

int	ft_readline(void)
{
	char *str2;
//	dup2(1, 0);
	g_all.rl_str = ft_strdup("\033[0;35m$PWD\033[0;32m@\033"
				"[0;34mminishell\033[0;32m$ \033[1;97m");
	g_all.rl_str = ft_expand(&(g_all.rl_str));
	int i = 0;
	while (g_all.rl_str[i] != '@')
		i++;
	while (g_all.rl_str[i] != '/')
		i--;
	if (g_all.rl_str[i + 1] != '\033')
	{
		str2 = ft_strdup(g_all.rl_str + i + 1);
		free(g_all.rl_str);
		g_all.rl_str = ft_strjoin(ft_strdup("\033[0;35m"), str2);
	}
	g_all.str = readline(g_all.rl_str);
	if (!g_all.str)
	{
		printf("exit\n");
		//ft_free("exit");
		exit(0);
	}
	if (g_all.str[0])
		add_history(g_all.str);
	if (ft_qvalidator(&(g_all.str)))
		g_all.array = to_double_pointer(&(g_all.str));
	else
		return (free(g_all.str), printf("validator failed\n"));
	//execute();
	ft_builtins(g_all.array);
	ft_free("no exit");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	ft_signals();
	ft_var_init();
	ft_init_env(env);
	while (1)
		ft_readline();
	ft_free("exit");
}
