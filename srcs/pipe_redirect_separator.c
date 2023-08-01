/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect_separator.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;

char	*ft_rseparator_pipe(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 1);
	if (i != 0)
		if ((*str)[i - 1] != 32 && (*str)[i - 1] != '>')
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("|"));
	if ((*str)[i + 1] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

char	*ft_rseparator_heredoc(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 2);
	if (i != 0)
		if ((*str)[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("<<"));
	if ((*str)[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

char	*ft_rseparator_append(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 2);
	if (i != 0)
		if ((*str)[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup(">>"));
	if ((*str)[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

char	*ft_rseparator_infile_prio(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 2);
	if (i != 0)
		if ((*str)[i - 1] != 32)
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("<>"));
	if ((*str)[i + 2] != 32)
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

char	*ft_rseparator(int state, char **str, int i)
{
	if (state == NQ)
	{
		if (!ft_strncmp((*str) + i, "|", 1))
			return (ft_rseparator_pipe(str, i));
		else if (!ft_strncmp((*str) + i, "<<", 2))
			return (ft_rseparator_heredoc(str, i));
		else if (!ft_strncmp((*str) + i, ">>", 2))
			return (ft_rseparator_append(str, i));
		else if (!ft_strncmp((*str) + i, "<>", 2))
			return (ft_rseparator_infile_prio(str, i));
		else if (!ft_strncmp((*str) + i, "<", 1))
			return (ft_rseparator_infile(str, i));
		else if (!ft_strncmp((*str) + i, ">", 1))
			return (ft_rseparator_outfile(str, i));
	}
	return ((*str));
}
