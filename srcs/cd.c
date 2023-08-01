/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

int	ft_builtin_cd_2(char *str)
{
	char	*str2;

	if (chdir(str) < 0)
	{
		printf("cd: %s: %s\n", strerror(errno), str);
		return (1);
	}
	str = ft_get_var("PWD");
	str2 = ft_get_var("OLDPWD");
	if (ft_strcmp(str, str2))
	{
		ft_add_var(ft_strdup("OLDPWD"), ft_get_var("PWD"));
		ft_add_var_exp(ft_strdup("OLDPWD"), ft_get_var("PWD"));
	}
	ft_add_var(ft_strdup("PWD"), getcwd(NULL, sizeof(char *)));
	ft_add_var_exp(ft_strdup("PWD"), getcwd(NULL, sizeof(char *)));
	ft_free_2(str, str2);
	return (1);
}

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
		if (!array[1])
			str = ft_get_var_exp("HOME");
		else if (!ft_strcmp(array[1], "-"))
			str = ft_get_var_exp("OLDPWD");
		else if (array[2])
			return (1);
		else
			str = array[1];
		ft_builtin_cd_2(str);
		if (!array[1] || !ft_strcmp(array[1], "-"))
			free(str);
	}
	return (1);
}
