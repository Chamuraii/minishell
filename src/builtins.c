/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:41 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (!ft_strcmp(pwd, ""))
		{
			free(pwd);
			pwd = ft_get_var_exp("OLDPWD");
		}
		printf("%s\n", pwd);
		free(pwd);
	}
	return (1);
}

int	ft_builtin_exit2(char **array, int j)
{
	if (array[1] && array[2])
	{
		g_all.error = 1;
		printf("exit: too many arguments\n");
		return (1);
	}
	else if (array[1])
	{
		while (array[1][j])
		{
			if (ft_isdigit(array[1][j]) != 1)
			{
				g_all.error = 255;
				printf("exit: %s: numeric argument required\n", array[1]);
				exit(g_all.error);
			}
			j ++;
		}
		g_all.error = ft_atoi(array[1]);
	}
	else
		g_all.error = 0;
	ft_free("exit");
	printf("exit\n");
	exit(g_all.error);
}

int	ft_builtin_exit(char **array, int i)
{
	int	j;

	j = 0;
	if (!i || i == 2)
	{
		if (i == 2)
			if (ft_strcmp(g_all.array[i - 2], "<"))
				return (1);
		while (ft_strcmp(g_all.array[i], "|") && g_all.array[i])
			i++;
		if (!ft_strcmp(g_all.array[i], "|"))
			return (1);
		else
			ft_builtin_exit2(array, j);
		return (1);
	}
	else
		return (1);
}

int	ft_builtins(char **array, int i)
{
	if (!ft_strncmp(array[0], "env", ft_strlen("env") + 1)
		|| !ft_strncmp(array[0], "ENV", ft_strlen("ENV") + 1))
		return (ft_builtin_env(array));
	if (!ft_strncmp(array[0], "pwd", ft_strlen("pwd") + 1)
		|| !ft_strncmp(array[0], "PWD", ft_strlen("PWD") + 1))
		return (ft_builtin_pwd(array));
	else if (!ft_strncmp(array[0], "export", ft_strlen("export") + 1))
		return (ft_builtin_export(array[0], array, i));
	else if (!ft_strncmp(array[0], "unset", ft_strlen("unset") + 1))
		return (ft_builtin_unset(array[0], array, i));
	else if (!ft_strncmp(array[0], "cd", ft_strlen("cd") + 1))
		return (ft_builtin_cd(array[0], array, i));
	else if (!ft_strncmp(array[0], "echo", ft_strlen("echo") + 1)
		|| !ft_strncmp(array[0], "ECHO", ft_strlen("ECHO") + 1))
		return (ft_builtin_echo(array[0], array));
	else if (!ft_strncmp(array[0], "exit", ft_strlen("exit") + 1))
		ft_builtin_exit(&array[0], i);
	return (0);
}
