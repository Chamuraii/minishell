#include "../includes/minishell.h"

t_all	g_all;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_put_hexa(int c, int err)
{
	char	*base;

	base = "0123456789abcdef";
	if (c <= 0 && err == 0)
	{
		c += 256;
	}
	if (c >= 16)
	{
		ft_put_hexa(c / 16, 1);
		ft_put_hexa(c % 16, 1);
	}
	else
	{
		if (err == 0)
			ft_putchar('0');
		ft_putchar(base[c]);
	}
}

void	ft_putstr_non_printable(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] < 32 || str[i] == 127)
		{
			ft_putchar('\\');
			j = str[i];
			ft_put_hexa(j, 0);
		}
		else
		{
			ft_putchar(str[i]);
		}
		i++;
	}
}

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
	ft_putstr_non_printable(str);
	if (str[0])
		add_history(str);
	if (ft_qvalidator(&str))
		g_all.array = to_double_pointer(&str);
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
