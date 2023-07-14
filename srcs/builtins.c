#include "../includes/minishell.h"

extern t_all g_all;

int ft_builtins(char *str)
{
	int i;
	int j;
	char *cdstr;

	if (!ft_strncmp(str, "env", ft_strlen("env")))
	{
		i = 0;
		while (g_all.env[i])
			printf("%s\n", g_all.env[i++]);
	}
	else if (!ft_strncmp(str, "pwd", ft_strlen("pwd")))
	{
		i = 0;
		while (g_all.env[i])
		{
			if (!ft_strncmp(g_all.env[i], "PWD", ft_strlen("PWD")))
				printf("%s\n", g_all.env[i] + 4);
			i++;
		}
	}
	else if (!ft_strncmp(str, "unset ", ft_strlen("unset ")))
	{
		char aux;

		i = 6;
		while (ft_isalnum(str[i]))
			i++;
		aux = str[i];
		str[i] = 0;
		ft_del_var(ft_strdup(str + 6));
		str[i] = aux;
	}
	else if (!ft_strncmp(str, "cd ", ft_strlen("cd ")))
	{
		j = 2;
		while (ft_isspace(str[j]))
			j++;
		i = j;
		int k = j;
		while (!ft_isspace(str[j++]))
			k++;
		j = i;
		cdstr = ft_substr(str, j, j - k + 1);
		if (!ft_strcmp(str + 3, ".."))
		{
			while (g_all.env[i])
			{
				if (!ft_strncmp(g_all.env[i], "PWD", ft_strlen("PWD")))
				{
					j = ft_strlen(g_all.env[i]);
					while (g_all.env[i][j] != '/')
						j--;

					g_all.env[i] = ft_strdetach(g_all.env[i], ft_strdup(g_all.env[i] + j));
				}
				i++;
			}
		}
		else
		{
			i = 0;
			while (g_all.env[i])
			{
				if (!ft_strncmp(g_all.env[i], "PWD", ft_strlen("PWD")))
				{
					g_all.env[i] = ft_strjoin(g_all.env[i], strdup("/"));
					g_all.env[i] = ft_strjoin(g_all.env[i], cdstr);
				}
				i++;
			}
		}
	}
	return (0);
}