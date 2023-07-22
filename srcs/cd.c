#include "../includes/minishell.h"

extern t_all	g_all;

int ft_is_backwards(char *str,int j, char **pwd)
{
	int i;

	i = ft_strlen(*pwd);
	if (!ft_strncmp(str + j, "..", 2))
	{
		if (i > 0)
			i--;
		while ((*pwd)[i] != '/' && i > 0)
			i--;
		if (i != 0)
			(*pwd)[i] = 0;
		if (i == 0 && ft_strcmp(*pwd, "/"))
			(*pwd) = ft_strdup("/");
		return (1);
	}
	else
		return (0);
}

int	ft_change_dir(char *str)
{
	char	*str2;
	char 	*str3;
	char	*pwd;
	int 	i;
	int 	ward;

	pwd = ft_get_var_exp(ft_strdup("PWD"));
	if (!pwd)
		return (0);
	i = 0;
	while (str[i])
	{
		ward = i;
		if (!ft_strncmp(str, "./", 2))
		{
			i += 2;
			ward = i;
		}
		else if (!ft_strncmp(str, "/", 1))
		{
			i += 1;
			pwd = ft_strdup("/");
			ward = i;
		}
		if (str[i] == '/')
		{
			i++;
			ward = i;
		}
		if (ft_is_backwards(str, i, &pwd) && str[i])
			i += 2;
		else if (str[i])
		{
			if (str[i] == '/')
			{
				i++;
				ward = i;
			}
			while (str[i] != '/' && str[i])
				i++;
			if (str[i])
			{
				if (str[i] == '/')
				{
					i++;
					ward = i;
				}
				if (str[i + 1])
				{
					str[i] = 0;
					pwd = ft_strjoin(pwd, ft_strdup(str + ward));
					str[i] = '/';
				}
			}
			else
				if (*(str + ward))
					pwd = ft_strjoin(pwd, ft_strdup(str + ward));
		}
	}
	str2 = ft_strdup(pwd);
	str3 = ft_strdup(str2);
	ft_add_var(ft_strdup("PWD"), str2);
	ft_add_var_exp(ft_strdup("PWD"), str3);
	return (1);
}