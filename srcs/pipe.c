/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:41:22 by jchamak           #+#    #+#             */
/*   Updated: 2023/07/27 16:09:34 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;
void	split_pipe(void);
void	redirections(int i, int end);
void	args_fill(int i, int end);

int	ft_exit(int status)
{
	if (status == 126 && ft_strcmp(g_all.commands[0], "") == 0)
	{
		write(2, "error 127", 9);
		status = 127;
	}
	else if (status == 126 && ft_strcmp(g_all.commands[0], ".") != 0)
		write(2, "is a directory", 15);
	else if (status == 126 && ft_strcmp(g_all.commands[0], ".") == 0)
	{
		write(2, "filename argument required", 26);
		status = 2;
	}
	else if (status != 127)
		write(2, strerror(status), strlen(strerror(status)));
	else
		write(2, "error 127", 9);
	write(2, "\n", 1);
	g_all.error = status;
	printf("status %d\n", g_all.error);
	ft_add_var(ft_strdup("?"), ft_strdup(ft_itoa(g_all.error)));
	exit (status);
//	return (status);
}

int	ft_return(int status)
{
	if (status != 127)
		write(2, strerror(status), strlen(strerror(status)));
	else
		write(2, "error 127", 9);
	write(2, "\n", 1);
	g_all.error = status;
	printf("status %d\n", g_all.error);
	ft_add_var(ft_strdup("?"), ft_strdup(ft_itoa(g_all.error)));
	return (status);
}

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

int where(void)
{
	int		i;
	char	*temp;
	char 	*jess_free_pls;

	i = 0;
	g_all.path = NULL;
	jess_free_pls = ft_get_var_exp("PATH");
	g_all.where = ft_split(jess_free_pls, ':');
	free(jess_free_pls);
	while (g_all.where[i])
	{
		temp = ft_strj(g_all.where[i], "/");
		free(g_all.where[i]);
		g_all.where[i] = ft_strj(temp, g_all.commands[0]);
		if (access(g_all.where[i], F_OK) == 0 && g_all.commands[0])
		{
			g_all.path = g_all.where[i];
			return (0);
		}
		i ++;
	}
	if (access(g_all.commands[0], F_OK) == 0)
	{
		g_all.path = g_all.commands[0];
		return (0);
	}
	if (g_all.commands[0])
	{
		if (!is_builtins(g_all.commands))
			ft_return(127);
	}
	return (127);
}

void	del_arg(int i)
{
	while (g_all.array[i])
	{
	g_all.array[i] = g_all.array[i + 2];
	i ++;
	}
	g_all.size -= 2;
}

void	ptp_infile(int i)
{
	g_all.is_infile = 1;
	g_all.infile = open (g_all.array[i + 1], O_RDONLY, 0644);
//	printf("infile : %d, %s\n", g_all.infile, g_all.array[i + 1]);
	if (g_all.infile <= 0)
	{
		g_all.infile = 0;
		ft_return(errno);
	}
	del_arg(i);
}

void	ptp_outfile(int i)
{
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
//	printf("outfile : %d, %s\n", g_all.outfile, g_all.array[i + 1]);
	if (g_all.outfile <= 0)
	{
		g_all.is_outfile = 0;
		g_all.outfile = 0;
		ft_return(errno);
	}
	del_arg(i);
}

void	ptp_append(int i)
{
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1],
			O_RDWR | O_APPEND | O_CREAT, 0644);
//	printf("append : %d, %s\n", g_all.outfile, g_all.array[i + 1]);
	if (g_all.outfile <= 0)
		ft_return(errno);
	del_arg(i);
}

int	heredoc(void)
{
	int		j;
	char	*his;
	char	*other;

	j = 0;
	pipe(g_all.p);
	while (j == 0)
	{
		other = double_heredoc();
		dup2(1, 0);
		his = readline("> ");
		if (!his)
		{
			dup2(g_all.p[0], 0);
			close(g_all.p[1]);
			return (-1);
		}
	//	printf("--- %s\n", his);
		if (strcmp (his, g_all.eof_heredoc) == 0 && his)
		{
			dup2(g_all.p[0], 0);
			//close(g_all.p[1]);
			j ++;
		}
		//if (strcmp (his, g_all.eof_heredoc) == 0 && his)
		else if (his)
		{
			if (g_all.outfile)
			{
				write(g_all.outfile, his, ft_strlen(his));
				write(g_all.outfile, "\n", 1);
			}
			else
			{
				write(g_all.p[1], his, ft_strlen(his));
				write(g_all.p[1], "\n", 1);
			}
		}
	}
	close(g_all.p[1]);
	return (0);
}

void	ptp_heredoc(int i)
{
	g_all.eof_heredoc = g_all.array[i + 1];
	//printf("eof : %s\n", g_all.eof_heredoc);
	heredoc();
	del_arg(i);
}

void	free_pipe(void)
{
	g_all.infile = 0;
	g_all.is_infile = 0;
	g_all.outfile = 0;
	g_all.is_outfile = 0;
	g_all.path = NULL;
	g_all.commands = NULL;
}

void	pipes(int last)
{
	int	i;
	int	j;

	pipe(g_all.p);
	if (!g_all.path)
		ft_exit(0);
	j = fork();
	if (j == -1)
		ft_return(errno);
	else if (j == 0)
	{
		close(g_all.p[0]);
		if (g_all.infile > 0)
			dup2(g_all.infile, 0);
		if (last == 0)
			dup2(g_all.p[1], 1);
		if (g_all.outfile > 0)
			dup2(g_all.outfile, 1);
		i = ft_builtins(g_all.commands, g_all.array_pos);
		ft_add_var(ft_strdup("?"), ft_strdup("0"));
		if (i == 0)
			execve(g_all.path, (char *const *) g_all.commands, g_all.env);
		dup2(0, 1);
		if (errno == 13 && ft_isalnum(g_all.commands[0][0]) == 0)
			ft_exit(126);
		if (errno == 13 && ft_isalnum(g_all.commands[0][0]) != 0)
			ft_exit(127);
		if (i == 0)
			ft_exit(errno);
		if (i != 0)
			exit(127);
	}
	else
	{
		close(g_all.p[1]);
		dup2(g_all.p[0], 0);
/*	  if (all->path)
	free(all->path); */
		waitpid(j, NULL, 0);
		//ft_add_var(ft_strdup("?"), ft_strdup("0"));
	}
//  dup2(0, 1);
	free_pipe();
	if (last == 1)
		dup2(1, 0);
}

int	is_pipe(void)
{
	int	i;

	i = g_all.size;
	while (g_all.array[i])
	{
		if (ft_strncmp(g_all.array[i], "|", 1) != 0)
			i ++;
		else
			return (1);
	}
	return (0);
}

void	args_fill(int i, int end)
{
	int	j;

	j = 0;
	g_all.array_pos = i;
	g_all.commands = ft_calloc(end - i + 1, sizeof(char *));
	while (i < end)
	{
		g_all.commands[j] = ft_strdup(g_all.array[i]);
		if (ft_strncmp(g_all.commands[j], "'", 1) == 0
			|| ft_strncmp(g_all.commands[j], "\"", 1) == 0)
			ft_remove_quotes(g_all.commands[j]);
		i ++;
		j ++;
	}
	g_all.commands[j] = 0;
	//remove comillas aqui (y expand $? ???)
	where();
	if (((ft_strcmp(g_all.commands[0], "exit") == 0) // justo al principio when no < > (al final no)
		|| ((ft_strcmp(g_all.commands[0], "export") == 0 && g_all.outfile == 0))// con argumentos solo al principio when no < >
		|| (ft_strcmp(g_all.commands[0], "cd") == 0) // anywhere
		|| (ft_strcmp(g_all.commands[0], "unset") == 0)))
	{
		ft_builtins(g_all.commands, g_all.array_pos);
	}
	else if (((g_all.is_outfile == 0 && g_all.outfile == 0)
			|| (g_all.is_outfile == 1 && g_all.outfile > 0))
		&& ((g_all.is_infile == 0 && g_all.infile == 0)
			|| (g_all.is_infile == 1 && g_all.infile > 0)))
	{
		if (is_pipe() == 1 && g_all.path)
			pipes(0);
		else if (g_all.path)
			pipes(1);
	}
	free_pipe();
	g_all.size ++;
	if (g_all.array[g_all.size])
		split_pipe();
//  dup2 (0, 1);
}

void	redirections(int i, int end)
{
	g_all.size = end;
	free_pipe();
	while (i < g_all.size)
	{
		if (ft_strncmp(g_all.array[i], "<<", 2) == 0)
			ptp_heredoc(i);
		else if (ft_strncmp(g_all.array[i], ">>", 2) == 0)
			ptp_append(i);
		else if (ft_strncmp(g_all.array[i], "<", 1) == 0)
			ptp_infile(i);
		else if (ft_strncmp(g_all.array[i], ">", 1) == 0)
			ptp_outfile(i);
		else
			i ++;
	}
	if (g_all.array[g_all.size + 1])
		args_fill(g_all.start_i, g_all.size);
	else if (g_all.array[0])
		args_fill(g_all.start_i, g_all.size + 1);
}

void	split_pipe(void)
{
	g_all.start_i = g_all.size;
	while (ft_strncmp(g_all.array[g_all.size], "|", 1) != 0
		&& g_all.array[g_all.size + 1])
	g_all.size ++;
	g_all.size ++;
	redirections(g_all.start_i, g_all.size - 1);
}

void change_array(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_all.array[i + 1])
	{
		if (ft_strcmp(g_all.array[i], "|") == 0 && ft_strcmp(g_all.array[i + 1], "<<") == 0)
		{
			g_all.array[i] = ">";
			while (g_all.array[i + 1])
			{
				j = i;
				g_all.array[i + 1] = g_all.array[i];
				i ++;
				pipe(g_all.p);
				g_all.outfile = g_all.p[1];
			}
		}
		i ++;
	}
}

int execute(void)
{
	if (!g_all.array[0])
		return (0);
//	change_array();
//	system("leaks minishell");
/*  g_all.array_size = 0;
	while (g_all.array[g_all.array_size])
	g_all.array_size ++; */
	g_all.i = 0;
	g_all.j = 0;
	g_all.error = 0;
	g_all.start_i = 0;
	g_all.end_i = 0;
	g_all.size = 0;
	dup2(0, 1);
	split_pipe();
	return (1);
}
