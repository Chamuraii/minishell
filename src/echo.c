/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

int	ft_builtin_echo_2(char *str, char **array, int flag_bool, int i)
{
	while (array[i])
	{
		str = array[i];
		printf("%s", str);
		i++;
		if (!ft_is_p_or_r(array[i]) && array[i])
			printf(" ");
	}
	if (flag_bool)
		printf("\n");
	else
	{
		printf("\033[107m\033[1;30m%%");
		printf("\033[1;0m");
		printf("\033[1;97m");
	}
	return (1);
}

int	ft_builtin_echo(char *str, char **array)
{
	int	flag_bool;
	int	i;

	i = 1;
	flag_bool = 1;
	if (!ft_strcmp(array[i], "-n"))
	{
		flag_bool = 0;
		i++;
	}
	ft_builtin_echo_2(str, array, flag_bool, i);
	return (1);
}
