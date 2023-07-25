/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchamak <jchamak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:41:22 by jchamak           #+#    #+#             */
/*   Updated: 2023/07/25 12:22:44 by jchamak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_all	g_all;
void	split_pipe(void);
void	redirections(int i, int end);
void	args_fill(int i, int end);

int	ft_exit(int status)
{
	write(2, strerror(status), strlen(strerror(status)));
	write(2, "\n", 1);
	g_all.error = status;
	exit (status);
//	return (status);
}

int	ft_return(int status)
{
	write(2, strerror(status), strlen(strerror(status)));
	write(2, "\n", 1);
	g_all.error = status;
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

	i = 0;
	g_all.path = NULL;
	g_all.where = ft_split(ft_get_var_exp("PATH"), ':');
	if (access(g_all.commands[0], F_OK) == 0)
	{
		g_all.path = g_all.commands[0];
		return (0);
	}
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
//  if (g_all.commands[0])
	ft_return(127);
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
	printf("infile : %d, %s\n", g_all.infile, g_all.array[i + 1]);
	if (g_all.infile <= 0)
	{
	//g_all.is_infile = 0;
		g_all.infile = 0;
		ft_return(errno);
	}
	del_arg(i);
}

void	ptp_outfile(int i)
{
	g_all.is_outfile = 1;
	g_all.outfile = open (g_all.array[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	printf("outfile : %d, %s\n", g_all.outfile, g_all.array[i + 1]);
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
	printf("append : %d, %s\n", g_all.outfile, g_all.array[i + 1]);
	if (g_all.outfile <= 0)
		ft_return(errno);
	del_arg(i);
}

char *double_heredoc(void)
{
	int	i;

	i = g_all.size;
	while (g_all.array[i])
	{
		if (ft_strncmp(g_all.array[i], "<<", 2) != 0)
			i ++;
		else if (g_all.array[i + 1])
			return (g_all.array[i + 1]);
	}
	return (NULL);
}

int	heredoc(void)
{
	int		j;
	//int		other;
	char	*his;

	j = 0;
	pipe(g_all.p);
	while (j == 0)
	{
		//other = double_heredoc();
		his = readline("> ");
		if (!his)
			return (-1);
	//	printf("--- %s\n", his);
		if (strcmp (his, g_all.eof_heredoc) == 0 && his)
		{
			dup2(g_all.p[0], 0);
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
	printf("eof : %s\n", g_all.eof_heredoc);
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

void	final_pipe(void)
{
	int	i;
	int	j;

	pipe(g_all.p);
	j = fork();
	if (j == -1)
		ft_return(errno);
	else if (j == 0)
	{
		close(g_all.p[0]);
		if (g_all.infile > 0)
			dup2(g_all.infile, 0);
		if (g_all.outfile > 0)
			dup2(g_all.outfile, 1);
		i = ft_builtins(g_all.commands);
		if (i == 0)
//	  if (g_all.path)
			execve(g_all.path, (char *const *) g_all.commands, g_all.env);
		dup2(0, 1);
		if (i != 0)
			exit(0);//127
	}
	else
	{
		close(g_all.p[1]);
		dup2(g_all.p[0], 0);
/*	  if (all->path)
	free(all->path); */
		waitpid(j, NULL, 0);
	}
//  dup2(0, 1);
	free_pipe();
	dup2(1, 0);
}

void	pipes(void)
{
	int	j;

	pipe (g_all.p);
	j = fork();
	if (j == -1)
		ft_return(errno);
	else if (j == 0)
	{
		close(g_all.p[0]);
		if (g_all.infile > 0)
			dup2(g_all.infile, 0);
		dup2(g_all.p[1], 1);
		if (g_all.outfile > 0)
			dup2(g_all.outfile, 1);
		if (ft_builtins(g_all.commands) == 0)
	//  if (g_all.path)
			execve(g_all.path, (char *const *) g_all.commands, g_all.env);
		ft_exit(127);//127
	}
	else
	{
		close(g_all.p[1]);
		dup2(g_all.p[0], 0);
/*	  if (g_all.path)
	free(g_all.path); */
		waitpid(j, NULL, 0);
	}
	free_pipe();
}

int is_pipe(void)
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

void	args_fill (int i, int end)
{
	int	j;

	j = 0;
	g_all.commands = ft_calloc(1000, sizeof(char));
	while (i < end)
	{
		g_all.commands[j] = g_all.array[i];
		i ++;
		j ++;
	}
	where();
	if (((g_all.is_outfile == 0 && g_all.outfile == 0)
			|| (g_all.is_outfile == 1 && g_all.outfile > 0))
		&& ((g_all.is_infile == 0 && g_all.infile == 0)
			|| (g_all.is_infile == 1 && g_all.infile > 0)))
	{
		if (is_pipe() == 1 && g_all.path)
			pipes();
		else if (g_all.path)
			final_pipe();
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

int execute(void)
{
	if (!g_all.array[0])
		return (0);
/*  g_all.array_size = 0;
	while (g_all.array[g_all.array_size])
	g_all.array_size ++; */
	g_all.i = 0;
	g_all.j = 0;
	g_all.start_i = 0;
	g_all.end_i = 0;
	g_all.size = 0;
	dup2(0, 1);
//  g_all.commands = ft_calloc(1000, sizeof(char));
	split_pipe();
	return (1);
}
