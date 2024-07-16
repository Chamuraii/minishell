/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:29:12 by jchamak           #+#    #+#             */
/*   Updated: 2023/08/01 19:37:11 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

/* FT_STRJ : ft_strjoin with no free */

char	*ft_strj(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	s1 = ft_strdup("");
	if (!s2)
	s2 = ft_strdup("");
	str = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

/* PATH : tests if the argument recieved is already a valid path and calls
ft_return to print if error 127 */

int	path(void)
{
	if (access(g_all.commands[0], F_OK) == 0)
	{
		g_all.path = g_all.commands[0];
		return (0);
	}
	if (g_all.commands[0])
	{
		if (!is_builtins(g_all.commands))
			ft_return(127, g_all.commands[0]);
	}
	return (1);
}

/* WHERE : creates potential paths using env's PATH variable untils it finds 
an accessible one */

int	where(void)
{
	int		i;
	char	*temp;
	char	*split;

	i = 0;
	g_all.path = NULL;
	split = ft_get_var_exp("PATH");
	g_all.where = ft_split(split, ':');
	free(split);
	while (g_all.where[i])
	{
		temp = ft_strj(g_all.where[i], "/");
		free(g_all.where[i]);
		g_all.where[i] = ft_strj(temp, g_all.commands[0]);
		free(temp);
		if (access(g_all.where[i], F_OK) == 0 && g_all.commands[0])
		{
			g_all.path = g_all.where[i];
			return (0);
		}
		i ++;
	}
	path();
	return (127);
}
