#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_builtin_echo(char *str, char **array)
{
	int	flag_bool;
	int i;

	i = 1;
	flag_bool = 1;
	if (!ft_strcmp(array[i], "-n"))
	{
		flag_bool = 0;
		i++;
	}
	while (!ft_is_p_or_r(array[i]) && array[i])
	{
		str = array[i];
		printf("%s", str);
		i++;
		if (!ft_is_p_or_r(array[i]) && array[i])
			printf(" ");
	}
	if (flag_bool)
		printf("\n");
	else
	{
		printf("\033[107m\033[1;30m%%");
		printf("\033[0m");
	}
	return (1);
}