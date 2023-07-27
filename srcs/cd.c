#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_builtin_cd(char *str, char **array, int i)
{
	if (!i || i == 2)
	{
		if (i == 2)
			if (ft_strcmp(g_all.array[i - 2], "<"))
				return (1);
		while (ft_strcmp(g_all.array[i], "|") && g_all.array[i])
			i++;
		if (!ft_strcmp(g_all.array[i], "|"))
			return (1);
		str = array[1];
		if (!str)
				chdir(ft_get_var_exp("HOME"));
		else if (array[2])
			return (1);
		else if (chdir(str) < 0)
		{
			printf("cd: %s: %s\n", strerror(errno), str);
			return (1);
		}
		if (ft_strcmp(ft_get_var(ft_strdup("PWD")), ft_get_var(ft_strdup("OLDPWD"))))
		{
			ft_add_var(ft_strdup("OLDPWD"), ft_strdup(ft_get_var("PWD")));
			ft_add_var_exp(ft_strdup("OLDPWD"), ft_strdup(ft_get_var("PWD")));
		}
		ft_add_var(ft_strdup("PWD"), ft_strdup(getcwd(NULL, sizeof(char *))));
		ft_add_var_exp(ft_strdup("PWD"), ft_strdup(getcwd(NULL, sizeof(char *))));
	}
	return (1);
}
