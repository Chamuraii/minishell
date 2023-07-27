#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_builtin_env(char **array)
{
	t_varlist	*head;

	if (!array[1])
	{
		head = g_all.exported_list[0];
		while (head)
		{
			printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
	}
	return (1);
}

int	ft_builtin_pwd(char **array)
{
	char	*pwd;

	if (array[0])
	{
		pwd = ft_get_var_exp("PWD");
		if (!pwd)
			pwd = ft_get_var_exp("OLDPWD");
		printf("%s\n", pwd);
		free(pwd);
	}
	return (1);
}

int	ft_builtin_export(char *str, char **array, int i)
{
	t_varlist	*head;

	str = array[1];
	if (!str)
	{
		if (!array[1])
		{
			head = g_all.exported_list[0];
			while (head)
			{
				printf("declare -x %s=%s\n", head->key, head->value);
				head = head->next;
			}
		}
		return (1);
	}
	if (i)
		return (1);
	if (ft_strstr(str, "="))
	{
		if (str[0] == '=')
			return (1);
		ft_var_declare(ft_strdup(str));
		ft_var_declare_exp(ft_strdup(str));
		return (1);
	}
	if (!ft_search_var(ft_strdup(str)))
		return (1);
	ft_add_var_exp(ft_strdup(str), ft_get_var(ft_strdup(str)));
	return (1);
}

int	ft_builtin_unset(char *str, char **array)
{
	str = array[1];
	if (!str)
		return (1);
	if (!ft_strncmp(str, "PWD", ft_strlen("PWD")))
		ft_add_var_exp(ft_strdup("OLDPWD"), ft_strdup(ft_get_var_exp("PWD")));
	ft_del_var(ft_strdup(str));
	return (1);
}

int	ft_builtins(char **array, int i)
{
	if (!ft_strncmp(array[0], "env", ft_strlen("env") + 1) || !ft_strncmp(array[0], "ENV", ft_strlen("ENV") + 1))
		return (ft_builtin_env(array));
	else if (!ft_strncmp(array[0], "pwd", ft_strlen("pwd") + 1))
		return (ft_builtin_pwd(array));
	else if (!ft_strncmp(array[0], "export", ft_strlen("export") + 1))
		return (ft_builtin_export(array[0], array, i));
	else if (!ft_strncmp(array[0], "unset", ft_strlen("unset") + 1))
		return (ft_builtin_unset(array[0], array));
	else if (!ft_strncmp(array[0], "cd", ft_strlen("cd") + 1))
		return (ft_builtin_cd(array[0], array));
	else if (!ft_strncmp(array[0], "echo", ft_strlen("echo") + 1))
		return (ft_builtin_echo(array[0], array));
	else if (!ft_strncmp(array[0], "exit", ft_strlen("exit") + 1))
	{
		if (!i)
		{
			ft_free("exit");
			exit(0);
		}
		else
			return (1);
	}
	return (0);
}

int	is_builtins(char **array)
{
	char	*str;

	str = array[0];
	if (!ft_strncmp(str, "env", ft_strlen("env") + 1)
		|| !ft_strncmp(str, "ENV", ft_strlen("ENV") + 1))
		return (1);
	else if (!ft_strncmp(str, "pwd", ft_strlen("pwd") + 1))
		return (1);
	else if (!ft_strncmp(str, "export", ft_strlen("export") + 1))
		return (1);
	else if (!ft_strncmp(str, "unset", ft_strlen("unset") + 1))
		return (1);
	else if (!ft_strncmp(str, "cd", ft_strlen("cd") + 1))
		return (1);
	else if (!ft_strncmp(str, "echo", ft_strlen("echo") + 1))
		return (1);
	else if (!ft_strncmp(str, "exit", ft_strlen("exit") + 1))
		exit(0);
	return (0);
}
