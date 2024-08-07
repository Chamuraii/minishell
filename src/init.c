/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorgfern <jorgfern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 13:26:10 by jorgfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_all	g_all;

void	ft_var_init(void)
{
	char	*exit_code;

	g_all.str = 0;
	g_all.i = 0;
	g_all.env = 0;
	g_all.array = 0;
	g_all.commands = 0;
	g_all.path = 0;
	g_all.var_list = (t_varlist **)malloc(sizeof(t_varlist *));
	if (!g_all.var_list)
	{
		write(2, "ERROR, not enough memory\n", 25);
		exit(0);
	}
	g_all.var_list[0] = 0;
	exit_code = ft_itoa(g_all.error);
	ft_add_var(ft_strdup("?"), ft_strdup(exit_code));
	free(exit_code);
	g_all.exported_list = (t_varlist **)malloc(sizeof(t_varlist *));
	if (!g_all.exported_list)
	{
		write(2, "ERROR, not enough memory\n", 25);
		exit(0);
	}
	g_all.exported_list[0] = 0;
}

void	ft_init_env(char **env)
{
	int	i;

	g_all.env = env;
	i = 0;
	while (env[i])
		ft_var_declare(env[i++]);
	i = 0;
	while (env[i])
		ft_var_declare_exp(env[i++]);
}
