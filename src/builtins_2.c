/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:32:18 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 19:08:44 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

void ft_print_array(char **array)
{
	int i = 0;

	if (!array)
	{
		printf("Empty array!");
		return ;
	}
	while (array[i])
		printf("%s", array[i++]);
}

int	is_builtins(char **array)
{
	if (array[0])
	{
		if (!ft_strncmp(array[0], "env", ft_strlen("env") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "pwd", ft_strlen("pwd") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "export", ft_strlen("export") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "unset", ft_strlen("unset") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "cd", ft_strlen("cd") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "echo", ft_strlen("echo") + 1))
			return (1);
		else if (!ft_strncmp(array[0], "exit", ft_strlen("exit") + 1))
			return (1);
	}
	return (0);
}

int	ft_didnt_expand_exp(char *str)
{
	char	*str2;
	char	*str3;

	if (!str)
		return (0);
	str2 = ft_strdup(str);
	str3 = ft_strstr(str2, "=");
	*str3 = 0;
	if (!str2)
		return (0);
	if (ft_strstr(str2, "$"))
		return (free(str2), 1);
	else
		return (free(str2), 0);
}

int	ft_builtin_export_2(char *str, char **array)
{
	if (ft_strstr(array[1], "="))
	{
		if (ft_didnt_expand_exp(array[1]) || array[1][0] == '='
			|| !ft_isalpha(array[1][0]))
		{
			printf("export: `%s': not a valid identifier\n", array[1]);
			g_all.error = 1;
			return (1);
		}
		str = ft_strdup(array[1]);
		ft_var_declare(str);
		free(str);
		str = ft_strdup(array[1]);
		ft_var_declare_exp(str);
		return (free(str), 1);
	}
	if (!ft_search_var(ft_strdup(array[1])))
		return (1);
	ft_add_var_exp(ft_strdup(array[1]), ft_get_var(array[1]));
	return (1);
}

int	ft_builtin_export(char *str, char **array, int i)
{
	t_varlist	*head;

	if (!array[1])
	{
		head = g_all.exported_list[0];
		while (head)
		{
			printf("declare -x %s=%s\n", head->key, head->value);
			head = head->next;
		}
		return (1);
	}
	if (i)
		return (1);
	while (ft_strcmp(g_all.array[i], "|") && g_all.array[i])
		i++;
	if (!ft_strcmp(g_all.array[i], "|"))
		return (1);
	ft_builtin_export_2(str, array);
	return (1);
}

int	ft_builtin_unset(char *str, char **array, int i)
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
			return (1);
		if (!ft_strncmp(str, "PWD", ft_strlen("PWD")))
			ft_add_var_exp(ft_strdup("OLDPWD"),
				ft_get_var_exp("PWD"));
		ft_del_var(ft_strdup(str));
		return (1);
	}
	return (1);
}
