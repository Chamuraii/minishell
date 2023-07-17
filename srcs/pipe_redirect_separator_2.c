#include "../includes/minishell.h"

extern t_all	g_all;

void	ft_rseparator_5(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 1);
	if (i != 0)
		if ((*str)[i - 1] != 32 && (*str)[i - 1] != '<')
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup("<"));
	if ((*str)[i + 1] != 32 && (*str)[i + 1] != '<' && (*str)[i + 1] != '>')
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = 0;
	(*str) = ft_strjoin(str2, str3);
}

void	ft_rseparator_6(char **str, int i)
{
	char	*str2;
	char	*str3;

	(*str)[i] = 0;
	str2 = ft_strdup((*str));
	str3 = ft_strdup((*str) + i + 1);
	if (i != 0)
		if ((*str)[i - 1] != 32 && (*str)[i - 1] != '>' && (*str)[i - 1] != '<')
			str2 = ft_strjoin(str2, ft_strdup(" "));
	str2 = ft_strjoin(str2, ft_strdup(">"));
	if ((*str)[i + 1] != 32 && (*str)[i + 1] != '>' && (*str)[i + 1] != '|')
		str2 = ft_strjoin(str2, ft_strdup(" "));
	free((*str));
	(*str) = 0;
	(*str) = ft_strjoin(str2, str3);
}