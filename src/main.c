/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:26:10 by jorgfern          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:55 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_all	g_all;

char	*ft_readline_str_2(char **str, int i)
{
	char	*str2;
	char	*str3;
	char	*user;

	str2 = ft_strdup(*str + i + 1);
	str3 = ft_strdup("$USER");
	str3 = ft_expand(&str3);
	if (!ft_strncmp(str2, str3, ft_strlen(str3)))
	{
		free(str2);
		str2 = ft_strdup(*str + i + ft_strlen(str3) + 1);
		user = ft_get_var_exp("USER");
		if (ft_strcmp(user, ""))
			str2 = ft_strjoin(ft_strdup("~"), str2);
		free(user);
		free(*str);
		*str = ft_strjoin(ft_strdup("\033[0;35m"), str2);
	}
	else
	{
		free(*str);
		*str = ft_strjoin(ft_strdup("\033[0;35m"), str2);
	}
	free(str3);
	return (*str);
}

void	ft_readline_str(char **str)
{
	int		i;
	char	*pwd;
	dup2(1, 0);
	*str = ft_strdup("\033[0;35m$PWD\033[0;32m@\033"
			"[0;34mminishell\033[0;32m$ \033[1;97m");
	
	pwd = ft_get_var("PWD");
	*str = ft_expand(str);
	i = 0;
	while ((*str)[i] != '@')
		i++;
	if (ft_strlen(pwd))
		while ((*str)[i] != '/')
			i--;
	if ((*str)[i + 1] != '\033')
		*str = ft_readline_str_2(str, i);
	free(pwd);
}

int	ft_readline(void)
{
	char	*str;

	ft_readline_str(&str);
	g_all.str = readline(str);
	if (!g_all.str)
	{
		free(str);
		printf("exit\n");
		exit(0);
	}
	if (g_all.str[0])
		add_history(g_all.str);
	if (ft_qvalidator(&(g_all.str)))
		g_all.array = to_double_pointer(&(g_all.str));
	else
		return (free(g_all.str), free(str), g_all.error = 258);
	execute();
	free(str);
	ft_free("no exit");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	ft_signals();
	ft_var_init();
	ft_init_env(env);
	while (1)
		ft_readline();
}
