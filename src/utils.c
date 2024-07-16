/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

int	ft_is_p_or_r(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "|", 2))
		return (1);
	if (!ft_strncmp(str, ">", 2))
		return (1);
	if (!ft_strncmp(str, "<", 2))
		return (1);
	if (!ft_strncmp(str, ">>", 3))
		return (1);
	if (!ft_strncmp(str, "<<", 3))
		return (1);
	return (0);
}

int	ft_is_p_or_r_between_quotes(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "\"|\"", 4))
		return (1);
	if (!ft_strncmp(str, "\">\"", 4))
		return (1);
	if (!ft_strncmp(str, "\"<\"", 4))
		return (1);
	if (!ft_strncmp(str, "\">>\"", 5))
		return (1);
	if (!ft_strncmp(str, "\"<<\"", 5))
		return (1);
	if (!ft_strncmp(str, "\'|\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'>\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'<\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'>>\'", 5))
		return (1);
	if (!ft_strncmp(str, "\'<<\'", 5))
		return (1);
	return (0);
}

int	ft_quotes_jess(char *str)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "\'\"|\"\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'\">\"\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'\"<\"\'", 4))
		return (1);
	if (!ft_strncmp(str, "\'\">>\"\'", 5))
		return (1);
	if (!ft_strncmp(str, "\'\"<<\"\'", 5))
		return (1);
	if (!ft_strncmp(str, "\"\'|\'\"", 4))
		return (1);
	if (!ft_strncmp(str, "\"\'>\'\"", 4))
		return (1);
	if (!ft_strncmp(str, "\"\'<\'\"", 4))
		return (1);
	if (!ft_strncmp(str, "\"\'>>\'\"", 5))
		return (1);
	if (!ft_strncmp(str, "\"\'<<\'\"", 5))
		return (1);
	return (0);
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		state;
	char	*str2;
	int		j;

	state = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		state = ft_quote_state(str[i], state);
		if (state == DQO || state == DQC || state == SQO || state == SQC)
			str[i] = 20;
		else
			j++;
		i++;
	}
	str2 = (char *)malloc(sizeof(char) * (j + 1));
	j = -1;
	i = -1;
	while (str[++i])
		if (str[i] != 20)
			str2[++j] = str[i];
	str2[i] = 0;
	return (str2);
}

int	ft_q_error_message(char **str, int i)
{
	printf("syntax error near unexpected token: `%c' \n", (*str)[i]);
	g_all.error = 258;
	ft_add_var(ft_strdup("?"), ft_strdup("258"));
	return (0);
}
