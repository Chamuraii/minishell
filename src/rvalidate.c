/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rvalidate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

int	ft_rvalidator(char **str, int i)
{
	while (ft_isspace((*str)[i]))
		i++;
	if (!ft_strncmp(((*str) + i), "|", ft_strlen("|")))
		return (ft_rvalidator_pipe(str, i));
	if (!ft_strncmp(((*str) + i), ">>", ft_strlen(">>")))
		return (ft_rvalidator_append(str, i));
	if (!ft_strncmp(((*str) + i), "<<", ft_strlen("<<")))
		return (ft_rvalidator_heredoc(str, i));
	if (!ft_strncmp(((*str) + i), "<", ft_strlen("<")))
		return (ft_rvalidator_infile(str, i));
	if (!ft_strncmp(((*str) + i), ">", ft_strlen(">")))
		return (ft_rvalidator_outfile(str, i));
	return (1);
}
