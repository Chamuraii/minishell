/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:04:48 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 14:05:03 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

char	*ft_remove_quotes_2_2(char **str, char *str2)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] != 20)
			str2[++j] = (*str)[i];
	free(*str);
	str2[++j] = 0;
	return (str2);
}

char	*ft_remove_quotes_2(char **str)
{
	int		i;
	int		state;
	char	*str2;
	int		j;

	state = 0;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		state = ft_quote_state((*str)[i], state);
		if (state == DQO || state == DQC || state == SQO || state == SQC)
			(*str)[i] = 20;
		else
			j++;
		i++;
	}
	str2 = (char *)malloc(sizeof(char) * (j + 1));
	return (ft_remove_quotes_2_2(str, str2));
}

int	ft_search_var(char *key)
{
	t_varlist	*head;

	head = g_all.var_list[0];
	if (!head)
		return (0);
	while (head)
	{
		if (!strcmp(key, head->key))
		{
			free(key);
			return (1);
		}
		head = head->next;
	}
	free(key);
	return (0);
}

int	ft_get_state(char *str, int j)
{
	int	i;
	int	state;

	i = 0;
	state = 0;
	if (!str)
		return (0);
	while (i <= j && str[i])
		state = ft_quote_state(str[i++], state);
	return (state);
}
