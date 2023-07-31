#include "../includes/minishell.h"

extern t_all	g_all;

char	*ft_rseparator_infile(char **str, int i)
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
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}

char	*ft_rseparator_outfile(char **str, int i)
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
	(*str) = ft_strjoin(str2, str3);
	return ((*str));
}
